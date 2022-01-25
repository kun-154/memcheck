#include <iostream>
#include "memcheck.h"

class A{};

int main() {
    A *p = new A(); 
    for (int i = 0; i < 10; i++) {
        int *t = new int();
        delete t;
    }

    return 0;
}
