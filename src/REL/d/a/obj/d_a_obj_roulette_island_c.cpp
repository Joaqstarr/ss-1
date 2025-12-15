#include "d/a/obj/d_a_obj_roulette_island_c.h"
#include "nw4r/g3d/res/g3d_resfile.h"
#include "d/d_stage.h"
#include "d/col/bg/d_bg_w.h"

SPECIAL_ACTOR_PROFILE(OBJ_ROULETTE_ISLAND_C, dAcOrouletteIslandC_c, fProfile::OBJ_ROULETTE_ISLAND_C, 0x1CA, 0, 2);

STATE_DEFINE(dAcOrouletteIslandC_c, Wait);
STATE_DEFINE(dAcOrouletteIslandC_c, Play);

dAcOrouletteIslandC_c::dAcOrouletteIslandC_c() : mStateMgr(*this, sStateID::null) {}
dAcOrouletteIslandC_c::~dAcOrouletteIslandC_c() {}

void dAcOrouletteIslandC_c::initializeState_Wait() {
    shouldStartPlay = false;
}

void dAcOrouletteIslandC_c::executeState_Wait() {
    if(shouldStartPlay) {
        mStateMgr.changeState(StateID_Play);
    }
}

void dAcOrouletteIslandC_c::finalizeState_Wait() {}
void dAcOrouletteIslandC_c::initializeState_Play() {}
void dAcOrouletteIslandC_c::executeState_Play() {}
void dAcOrouletteIslandC_c::finalizeState_Play() {}

bool dAcOrouletteIslandC_c::initModels(){
    mpResFile = nw4r::g3d::ResFile(getOarcResFile("IslRouMain"));

    dStage_c::bindStageResToFile(&mpResFile);
    dStage_c::bindSkyCmnToResFile(&mpResFile);

    nw4r::g3d::ResMdl resMdl = mpResFile.GetResMdl("IslRouMain");

    bool result = model1.create(resMdl, &mAllocator, 0x120, 1, nullptr);

    if(!result)return false;

    nw4r::g3d::ResMdl resMdl2 = mpResFile.GetResMdl("IslRouMain_s");

    result = model2.create(resMdl2, &mAllocator, 0x120, 1, nullptr);

    if(!result)return false;

    cBgD_t* dzbData = (cBgD_t*)getOarcFile("IslRouMain","dzb/IslRouMain.dzb");
    PLC* plcData = (PLC*)getOarcFile("IslRouMain","dat/IslRouMain.plc");

    updateMatrix();
    model1.setLocalMtx(mWorldMtx);
    model2.setLocalMtx(mWorldMtx);

    model1.setScale(mScale);
    model2.setScale(mScale);

    bool success = (bgCollision.Set(dzbData, plcData, 1, &mWorldMtx, &mScale) == 0);

    if (success) {
        bgCollision.Lock();
        return true;
    }

    return success;
}