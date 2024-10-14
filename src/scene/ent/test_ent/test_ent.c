#include "test_ent.h"

size_t TestEnt_GetSize() {
    return sizeof(test_ent_t);
}

void TestEnt_Set(test_ent_t* test_ent, BOOL setPFN) {
    if(setPFN) {
        test_ent->pfnSpawn = (PFN_SPAWN)TestEnt_Spawn;
        test_ent->pfnActivate = (PFN_ACTIVATE)TestEnt_Activate;
        test_ent->pfnTick = (PFN_TICK)TestEnt_Tick;
        test_ent->pfnKeyValue = (PFN_KEYVALUE)TestEnt_KeyValue;
    }
    test_ent->typeHierarchy = SA_CreateString("test_ent;");
    test_ent->test = 1;
}

void TestEnt_Spawn(test_ent_t* ent) {

}

void TestEnt_Activate(test_ent_t* ent) {

}

void TestEnt_Tick(test_ent_t* ent) {

}

void TestEnt_KeyValue(test_ent_t* ent, keyvalue_t* keyValues, size_t keyValueCount) {

}