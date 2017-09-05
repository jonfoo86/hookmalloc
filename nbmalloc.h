#include <string.h>

void *nbmalloc(size_t size) ;
void nbfree(void *ptr); 
void *nbrealloc(void *ptr, size_t size) ;
void *nbcalloc(size_t nmemb, size_t size); 
void *nbmemalign(size_t blocksize, size_t bytes); 

void Init(); 
