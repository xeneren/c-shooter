#include "scene.h"

ent_t* entities[SC_MAX_ENTITIES] = { 0 };
uint32_t entityCount = 0;

BOOL initialized = false;

BOOL SC_CreateEntity(ent_t* entity) {
    if (entityCount == SC_MAX_ENTITIES) {
        return false;
    }
    
    for (uint32_t i = 0; i < SC_MAX_ENTITIES; i++) {
        if (entities[i] == NULL) {
            entities[i] = entity;
            entity->index = i;
            entity->pfnSpawn(entity);
            return true;
        }
    }
    return false;
}
BOOL SC_CreateEntityByClassname(const char* classname, keyvalue_t* keyvalueCount) {
    printf("SC_CreateEntityByClassname isnt implemented yet!\n");
    return false;
}
BOOL SC_DeleteEntity(uint32_t index) {
    if (index >= SC_MAX_ENTITIES) {
        return false;
    }

    if (entities[index] == NULL) {
        return false;
    }

    free(entities[index]);
    entities[index] = NULL;

    return true;
}
ent_t* SC_GetEntity(uint32_t index) {
    if (index >= SC_MAX_ENTITIES) {
        return NULL;
    }

    return entities[index];
}