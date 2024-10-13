#include "test_ent.h"

size_t TestEnt_GetSize() {
    return sizeof(test_ent_t);
}

void TestEnt_Set(ent_t* ent, BOOL setPFN) {
    test_ent_t* test_ent = (ent_t*) ent;
    if(setPFN) {
        test_ent->pfnSpawn = TestEnt_Spawn;
        test_ent->pfnActivate = TestEnt_Activate;
        test_ent->pfnTick = TestEnt_Tick;
    }
    test_ent->typeHierarchy = SA_CreateString("test_ent;");
    test_ent->test = 1;
}

void TestEnt_Spawn(ent_t* ent) {

}

void TestEnt_Activate(ent_t* ent) {

}

void TestEnt_Tick(ent_t* ent) {

}