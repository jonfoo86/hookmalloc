#include "nbmalloc.h"
void my_init()
    __attribute__((constructor));  //告诉gcc把这个函数扔到init section
void my_init() {
  Init();
}
