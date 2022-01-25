#define _MEM_OVERLOAD_

#include "memcheck.h"



MemCheck MemCheck::memcheck;

MemCheck::MemCheck(/* args */) :totalsize(0)
{
    memcheck.ISEND = false;
}

MemCheck::~MemCheck()
{
    memcheck.ISEND = true;
    std::cout << "=======================MemCheck Destructot===================" << std::endl;
    if (memcheck.totalsize > 0) {
        std::cout << "==========leak memory info===============" << std::endl;
        for (auto it : memcheck.MemPool) {
            std::cout << "leak Memory Address [" << it.first;
            std::cout << "  leak Memory file [" << it.second->file;
            std::cout << "  leak Memory line [" << it.second->line;
            std::cout << "  leak Memory size [" << it.second->size << std::endl;
            delete it.second;
        }
    }
    std::cout << "=======================MemCheck Destructot===================" << std::endl;

}

void MemCheck::SetMemInfo(void *ptr, const char *file, unsigned long line, unsigned long size) {
    if (memcheck.ISEND) return ;
    std::cout << "MALLOC ADDRESS[" << ptr << "]";
    std::cout << "  SIZE =[" << size << "]";
    std::cout << std::endl;

    memcheck.MemPool[ptr] = new MemInfo(file, line, size);
    memcheck.totalsize += size;
    std::cout <<"totalsize " << memcheck.totalsize << std::endl;
    return;
}

void MemCheck::DeletMemInfo(void *ptr) {
    if (memcheck.ISEND) return ;
    std::cout << "FREE ADDRESS [" << ptr << "]" << std::endl;
    auto PInfo = memcheck.MemPool.find(ptr);
    if (PInfo != memcheck.MemPool.end()) {
        memcheck.totalsize -= PInfo->second->size;
        std::cout << "map" << std::endl;
        memcheck.MemPool.erase(ptr); 
    }
    std::cout <<"totalsize " << memcheck.totalsize << std::endl;
    return;
}


void *operator new(size_t size, const char *file, unsigned long line){
    if (size == 0){
        size = 1;
    }
    void *ptr = malloc(sizeof(size));
    if (ptr == nullptr) {
        std::cout << "NEW ERR" << std::endl;
        return ptr;
    }
    MemCheck::SetMemInfo(ptr, file, line, size);
    return ptr;
    
}
void *operator new[](size_t size, const char *file, unsigned long line){
    if (size == 0){
        size = 1;
    }
    void *ptr = malloc(sizeof(size));
    if (ptr == nullptr) {
        std::cout << "NEW ERR[]" << std::endl;
    }
    MemCheck::SetMemInfo(ptr, file, line, size);
    return ptr;
}

void operator delete(void *ptr){
    if (ptr == nullptr) return ;
    MemCheck::DeletMemInfo(ptr);
    free(ptr);
    return ;
}

void operator delete[](void *ptr){
    if (ptr == nullptr) return ;
    MemCheck::DeletMemInfo(ptr);
    free(ptr);
    return ;
}

