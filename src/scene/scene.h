#ifndef SCENE_H
#define SCENE_H

#define MAX_ENTITIES 16384

#include "ent/ent.h"

BOOL SC_CreateEntity(ent_t* entity);
BOOL SC_CreateEntityByClassname(const char* classname, keyvalue_t* keyvalues);
BOOL SC_DeleteEntity();
ent_t* SC_GetEntity();

#endif