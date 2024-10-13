#include "string_allocator.h"

char* strings[SA_MAX_STRINGS];
uint32_t stringsAmount = 0;

string_t SA_CreateString(const char* string) {
    if(stringsAmount == SA_MAX_STRINGS) {
        return NULL;
    }
    size_t stringSize;
    char *outString;

    stringSize = strlen(string) + 1;

    for(string_t i = 0; i < SA_MAX_STRINGS; i++) {
        if(strings[i] == NULL) {
            outString = strings[i];
            outString = malloc(stringSize);
            
            if(!outString) {
                printf("3\n");
                return NULL;
            }
            
            memcpy(outString, string, stringSize);
            stringsAmount++;
            
            strings[i] = outString;
            return i + 1;
        }
    }

    return NULL;
} 

char* SA_GetString(string_t string) {

    if(string > SA_MAX_STRINGS) {
        return NULL;
    }

    return strings[string - 1];
} 

BOOL SA_ModifyString(string_t string, const char* newString) {
    if(string > SA_MAX_STRINGS) {
        return false;
    }

    size_t stringSize = strlen(newString) + 1;
    char* modString = strings[string - 1];

    if(modString != NULL) {
        modString = realloc(modString, stringSize);
        if(!modString) {
            return false;
        }

        memcpy(modString, newString, stringSize);
    } else {
        modString = malloc(stringSize);
        if(!modString) {
            return false;
        }

        memcpy(modString, newString, stringSize);
    }

    strings[string - 1] = modString;

    return true;
}

BOOL SA_DeleteString(string_t string) {
    if(string > SA_MAX_STRINGS) {
        return false;
    }

    char* delString = strings[string - 1];

    if(delString != NULL) {
        free(delString);
        strings[string - 1] = NULL;
        stringsAmount--;

        return true;
    }

    return false;
}