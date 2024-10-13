#ifndef TEST_ENT_H
#define TEST_ENT_H

#include "../ent.h"

#define DEFINE_TEST_ENT_VARS() \
    DEFINE_BASE_ENT_VARS() \
    string_t test;

typedef struct
{
    DEFINE_TEST_ENT_VARS()
} test_ent_s;

typedef test_ent_s test_ent_t;

size_t TestEnt_GetSize();
void TestEnt_Set(ent_t* ent);

void TestEnt_Spawn(ent_t* ent);
void TestEnt_Activate(ent_t* ent);
void TestEnt_Tick(ent_t* ent);

#endif