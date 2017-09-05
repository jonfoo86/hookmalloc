#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include "nbmalloc.h"

typedef __uint32_t uint32_t;

#define PrintFunctionName printf("Call %s, Line %d\n", __FUNCTION__, __LINE__);
#define EndFunction printf("End %s, Line %d\n", __FUNCTION__, __LINE__);
#define HookFunction

typedef void *(*MallocFunc)(size_t size);
typedef void (*FreeFunc)(void *);
typedef void *(*ReallocFunc)(void *ptr, size_t size);
typedef void *(*MemalignFunc)(size_t blocksize, size_t bytes);

MallocFunc _ogr_malloc = NULL;
FreeFunc _ogr_free = NULL;
ReallocFunc _ogr_realloc = NULL;
MemalignFunc _ogr_memalign = NULL;

int g_init = 0;
void Init() {
    if(g_init) return ; 
    g_init = 1;
    _ogr_malloc = (MallocFunc)dlsym(RTLD_NEXT, "malloc");
    _ogr_free = (FreeFunc)dlsym(RTLD_NEXT, "free");
    _ogr_realloc = (ReallocFunc)dlsym(RTLD_NEXT, "realloc");
    _ogr_memalign = (MemalignFunc)dlsym(RTLD_NEXT, "memalign");
    g_init = 2;
}

#define tmplen 20 * 1024
char tmpbuf[tmplen];
size_t tmppos = 0;
void *mallocFromTmp(size_t size) {
    tmppos += size;
    //printf("tmpos : %ld  \n", tmppos);
    if (size >= tmplen) {
       // printf("too mutch malloc temp  \n");
        return NULL;
    }
    return tmpbuf + tmppos;
}

int nbistmp(void *ptr) { return (ptr >= tmpbuf) && (ptr <= (tmpbuf + tmplen)); }

#define ExtLen 4
void *nbtoRealPtr(void *vptr) {
    void *ptr = vptr - 4;
    return ptr;
}

size_t nbgetRealSize(void *ptr) { return *((uint32_t *)ptr); }

void *nbtoVitrulPtr(void *ptr, size_t size) {
    void *vptr = ptr + 4;
    *((uint32_t *)ptr) = size;
    return vptr;
}

void *nbmalloc(size_t size) {
    Init();
    if (g_init == 1 || size ==0 ) {
        return mallocFromTmp(size);
    }
    void *ptr = _ogr_malloc(size + ExtLen);
    if (ptr != NULL) {
        ptr = nbtoVitrulPtr(ptr, size);
    }

    return ptr;
}

void nbfree(void *ptr) {
    Init();
    if (_ogr_free == NULL) return;
    if (ptr == NULL) return;
    if (nbistmp(ptr)) return;

    if (ptr != NULL) {
        ptr = nbtoRealPtr(ptr);
    }
    _ogr_free(ptr);
}

void *nbrealloc(void *ptr, size_t size) {
    void *nptr = nbmalloc(size);

    if (ptr != NULL) {
        void *orgptr = nbtoRealPtr(ptr);
        size_t rsize = nbgetRealSize(orgptr);
        memcpy(nptr, ptr, rsize > size ? size : rsize);

        nbfree(ptr);
    }

    return nptr;
}

void *nbcalloc(size_t nmemb, size_t size) {
    size_t realsize = nmemb * size;
    void *ptr = nbmalloc(realsize);
    memset(ptr, 0, realsize);

    return ptr;
}

void *nbmemalign(size_t blocksize, size_t bytes) {
    size_t realsize = blocksize * bytes;
    void *ptr = nbmalloc(realsize);
    return ptr;
}
