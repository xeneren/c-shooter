#ifndef TEST_ENT_H
#define TEST_ENT_H

#include <cglm/struct/vec3.h>
#include "../ent.h"

#define DEFINE_TEST_ENT_VARS() \
    DEFINE_BASE_ENT_VARS() \
    int test;

typedef struct
{
    DEFINE_TEST_ENT_VARS()
} test_ent_s;

typedef test_ent_s test_ent_t;

size_t TestEnt_GetSize();
void TestEnt_Set(test_ent_t* ent, BOOL setPFN);

void TestEnt_Spawn(test_ent_t* ent);
void TestEnt_Tick(test_ent_t* ent);
void TestEnt_KeyValue(test_ent_t* ent, keyvalue_t* keyValues, size_t keyValueCount);

#endif