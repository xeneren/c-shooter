#include "util.h"

BOOL Util_ReadFile(const char* path, HeapData* ret, BOOL binary) {
    const char* mode = (binary ? "rb" : "r");
    FILE* file = fopen(path, mode);
    if(!file) {
        printf("Failed to open file: %s\n", path);
        return false;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    ret->bytes = malloc(size);
    if (!ret->bytes) {
        printf("Failed to allocate file: %s\n", path);
        return false;
    }
    ret->size = size;

    
    fseek(file, 0, SEEK_SET);
    if (binary) {
        if (fread(ret->bytes, 1, size, file) != size) {
            return false;
        }
    }
    else {
        char* p = ret->bytes;
        while (fgets(p, ret->size, file) != NULL) {
            p += strlen(p);
        }
    }
    fclose(file);
    return true;
}

BOOL Util_PrintMessage(const char* fmt, UTIL_MESSAGE_TYPE msgType, ...) {
    //TODO: make an actual console with ImGui

    va_list ap;
    va_start(ap, fmt);

    size_t logMsgSize = vsnprintf(NULL, 0, fmt, ap);
    char* logMsgBuff = malloc(logMsgSize + 1);
    if (!logMsgBuff) {
        printf(ANSI_COLOR_RED "[FATAL] Failed to allocate log message!\n" ANSI_COLOR_RESET);
        return false;
    }

    logMsgBuff[logMsgSize] = '\0';
    
    vsprintf(logMsgBuff, fmt, ap);

    va_end(ap);

    const char* prefix;

    switch (msgType)
    {
    case UTIL_MESSAGE_TYPE_LOG:
        prefix = "[Log]";
        break;
    case UTIL_MESSAGE_TYPE_WARNING:
        prefix = ANSI_COLOR_YELLOW "[Warning]";
        break;
    case UTIL_MESSAGE_TYPE_ERROR:
        prefix = ANSI_COLOR_BRIGHT_RED "[Error]";
        break;
    case UTIL_MESSAGE_TYPE_FATAL:
        prefix = ANSI_COLOR_RED "[FATAL]";
        break;
    default:
        prefix = "";
        break;
    }
    printf("%s %s%s", prefix, logMsgBuff, ANSI_COLOR_RESET);

    free(logMsgBuff);

    return true;
}