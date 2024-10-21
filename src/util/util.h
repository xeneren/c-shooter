#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_BRIGHT_BLACK   "\x1b[90m"
#define ANSI_COLOR_BRIGHT_RED     "\x1b[91m"
#define ANSI_COLOR_BRIGHT_GREEN   "\x1b[92m"
#define ANSI_COLOR_BRIGHT_YELLOW  "\x1b[93m"
#define ANSI_COLOR_BRIGHT_BLUE    "\x1b[94m"
#define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_COLOR_BRIGHT_CYAN    "\x1b[96m"
#define ANSI_COLOR_BRIGHT_WHITE   "\x1b[97m"

#define ANSI_COLOR_RESET   "\x1b[0m"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
typedef char BOOL;

#define true 1
#define false 0

typedef enum {
    UTIL_MESSAGE_TYPE_LOG,
    UTIL_MESSAGE_TYPE_WARNING,
    UTIL_MESSAGE_TYPE_ERROR,
    UTIL_MESSAGE_TYPE_FATAL
} UTIL_MESSAGE_TYPE;

typedef struct
{
    size_t size;
    int8_t* bytes;
} HeapData;

BOOL Util_ReadFile(const char* path, HeapData* ret, BOOL binary);

BOOL Util_PrintMessage(const char* fmt, UTIL_MESSAGE_TYPE msgType, ...);
#endif