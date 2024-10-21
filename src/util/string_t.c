#include "string_t.h"

string_t ST_CreateString(const char* string) {

    size_t stringSize;
    string_t outString;

    stringSize = strlen(string) + 1;

    outString = malloc(stringSize);
    if (!outString) {
        printf("Failed to allocate string: %s", string);
        return NULL;
    }

    return outString;
} 

BOOL ST_ModifyString(string_t string, const char* newString) {

    size_t stringSize = strlen(newString) + 1;

    if(string != NULL) {
        string = realloc(string, stringSize);
        if(!string) {
            return false;
        }

        memcpy(string, newString, stringSize);
    } else {
        string = malloc(stringSize);
        if(!string) {
            return false;
        }

        memcpy(string, newString, stringSize);
    }

    return true;
}