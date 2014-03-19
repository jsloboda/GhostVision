#include "ltfat.h"
#define WITH_FFTW_MALLOC


#ifndef WITH_FFTW_MALLOC
#include <stdint.h>
#define ALIGN 32
#endif

LTFAT_EXTERN_TOO
void* ltfat_malloc (size_t n)
{
    void *outp = NULL;
    #ifdef WITH_FFTW_MALLOC
      outp = fftw_malloc(n);
      if(outp==NULL) goto memerror;
    #else
      void *mem = malloc(n+ALIGN+sizeof(void*));
      if(mem==NULL) goto memerror;
      void **ptr = (void**)((uintptr_t)(mem+ALIGN+sizeof(void*)) & ~(ALIGN-1));
      ptr[-1] = mem;
      outp = ptr;
    #endif

    return outp;
memerror:
    puts("ltfat_malloc failed.");
    exit(1);
}

LTFAT_EXTERN_TOO
void* ltfat_realloc (void *ptr, size_t n)
{
    void *outp;
    // DOES NOT PRODUCE MEMORY ALIGNED POINTER
    // outp = realloc(ptr, n);
    outp = ltfat_malloc(n);

    if(ptr!=NULL)
    {
        ltfat_free(ptr);
    }

    return outp;
}

void* ltfat_realloc_and_copy (void *ptr, size_t nold, size_t nnew)
{
    if (ptr == NULL)
    {
        puts("Null pointer.");
        exit(1);
    }

    void *outp;

    outp = ltfat_malloc(nnew);

    memcpy(outp,ptr,nold<nnew?nold:nnew);

    ltfat_free(ptr);

    return outp;
}

LTFAT_EXTERN_TOO
void* ltfat_calloc (size_t nmemb, size_t size)
{
    void *outp;
    // DOES NOT PRODUCE MEMORY ALIGNED POINTER
    // outp = calloc(nmemb, size);

    // workaround
    outp = ltfat_malloc(nmemb*size);

    // workaround
    memset(outp,0,nmemb*size);

    return outp;
}

LTFAT_EXTERN_TOO
void ltfat_free(const void *ptr)
{
   #ifdef WITH_FFTW_MALLOC
      fftw_free((void*)ptr);
   #else
      free(((void**)ptr)[-1]);
   #endif
}

void ltfat_safefree(const void *ptr)
{
    if(ptr!=NULL)
        ltfat_free((void *)ptr);
}

#undef ALIGN
