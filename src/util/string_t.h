#ifndef STRING_T_H
#define STRING_T_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/defs.h>

typedef char* string_t;

//will return NULL if allocation failed
string_t ST_CreateString(const char* string); 

//will return false if allocaton failed
//if string isn't allocated SA_ModString will create the string at location instead
BOOL ST_ModifyString(string_t string, const char* newString);

//will return false if string isnt allocated
BOOL ST_DeleteString(string_t string);

#endif