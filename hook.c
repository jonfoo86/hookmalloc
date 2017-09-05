#include "nbmalloc.h"

void *malloc(size_t size) { return nbmalloc(size); }
void *valloc(size_t size) { return nbmalloc(size); }
void *pvalloc(size_t size) { return nbmalloc(size); }

void free(void *ptr) { return nbfree(ptr); }

void *realloc(void *ptr, size_t size) { return nbrealloc(ptr, size); }

void *calloc(size_t nmemb, size_t size) { return nbcalloc(nmemb, size); }

void *memalign(size_t blocksize, size_t bytes) {
    return nbmemalign(blocksize, bytes);
}

void *__libc_malloc(size_t size) { return nbmalloc(size); }
void *__libc_valloc(size_t size) { return nbmalloc(size); }
void *__libc_pvalloc(size_t size) { return nbmalloc(size); }

void __libc_free(void *ptr) { return nbfree(ptr); }

void *__libc_realloc(void *ptr, size_t size) { return nbrealloc(ptr, size); }

void *__libc_calloc(size_t nmemb, size_t size) { return nbcalloc(nmemb, size); }

void *__libc_memalign(size_t blocksize, size_t bytes) {
    return nbmemalign(blocksize, bytes);
}
