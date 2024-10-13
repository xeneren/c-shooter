#ifndef STRING_ALLOCATOR_H
#define STRING_ALLOCATOR_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/defs.h>

#define SA_MAX_STRINGS 16384

typedef uint32_t string_t;

//will return NULL if allocation failed or SA_MAX_STRINGS was at its limit
string_t SA_CreateString(const char* string); 

//will return NULL if string isn't allocated
char* SA_GetString(string_t string); 

//will return false if allocaton failed
//if string isn't allocated SA_ModString will create the string at location instead
BOOL SA_ModifyString(string_t string, const char* newString);

//will return false if string isnt allocated
BOOL SA_DeleteString(string_t string);

#endif