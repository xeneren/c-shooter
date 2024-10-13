#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
typedef char BOOL;

#define true 1
#define false 0

typedef struct
{
    size_t size;
    int8_t* bytes;
} HeapData;

BOOL Util_ReadFile(const char* path, HeapData* ret, BOOL binary);

#endif