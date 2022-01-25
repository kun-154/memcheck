#ifndef _MEMCHECK_H_
#define _MEMCHECK_H_
#include <unordered_map>
#include <iostream>

struct MemInfo
{
    MemInfo(const char *file, unsigned long line, unsigned long size) : file(file), line(line), size(size) {}
    const char * file;
    unsigned long line, size;  
};



void *operator new(size_t size, const char *file, unsigned long line);
void *operator new[](size_t size, const char *file, unsigned long line);

void operator delete(void *ptr);
void operator delete[](void *ptr);

class MemCheck
{
private:
    /* data */
    bool ISEND;
    static MemCheck memcheck;
    unsigned long totalsize;
    std::unordered_map<void *, MemInfo*> MemPool;
public:
    MemCheck(/* args */);
    ~MemCheck();

    static void SetMemInfo(void *ptr, const char *file, unsigned long line, unsigned long size);
    static void DeletMemInfo(void *ptr);
};



#ifndef _MEM_OVERLOAD_
#define new new(__FILE__, __LINE__)
#endif


#endif