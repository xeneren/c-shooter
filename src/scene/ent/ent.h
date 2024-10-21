#ifndef ENT_H
#define ENT_H

#include <cglm/struct/vec3.h>
#include <util/string_t.h>

typedef struct {
    string_t key;
    string_t value;
} keyvalue_s;

typedef keyvalue_s keyvalue_t;

typedef void(*PFN_SPAWN)(void* ent);
typedef void(*PFN_TICK)(void* tick);
typedef void(*PFN_KEYVALUE)(void* ent, keyvalue_t* keyValues, size_t keyValueCount);

#define DEFINE_BASE_ENT_VARS() \
    uint32_t index; \
    string_t typeHierarchy; \
    PFN_SPAWN pfnSpawn; \
    PFN_TICK pfnTick; \
    PFN_KEYVALUE pfnKeyValue; \
    vec3s position; \
    vec3s rotation; \
    vec3s scale;

typedef struct
{
    DEFINE_BASE_ENT_VARS()
} ent_s;

typedef ent_s ent_t;

#endif