#ifndef SCENE_H
#define SCENE_H

#define SC_MAX_ENTITIES 16384

#include "ent/ent.h"

BOOL SC_CreateEntity(ent_t* entity);
BOOL SC_CreateEntityByClassname(const char* classname, keyvalue_t* keyvalues, uint32_t keyvalueCount);
BOOL SC_DeleteEntity(uint32_t index);
ent_t* SC_GetEntity(uint32_t index);

#endif