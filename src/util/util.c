#include "util.h"

BOOL Util_ReadFile(const char* path, HeapData* ret, BOOL binary) {
    const char* mode = (binary ? "rb" : "r");
    FILE* file = fopen(path, mode);
    if(!file) {
        return false;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    ret->bytes = malloc(size);
    ret->size = size;

    fseek(file, 0, SEEK_SET);
    if(fread(ret->bytes, 1, size, file) != size) {
        return false;
    }
    
    return true;
}