#include "d/a/obj/d_a_obj_roulette_island_c.h"
#include "nw4r/g3d/res/g3d_resfile.h"
#include "d/d_stage.h"
#include "d/col/bg/d_bg_w.h"
#include "d/d_rumble.h"
#include "d/lyt/d_lyt_mini_game.h"
#include "d/a/obj/d_a_obj_fortune_ring.h"
#include "d/col/bg/d_bg_s.h"
#include "d/flag/storyflag_manager.h"

dAcOrouletteIslandC_c *dAcOrouletteIslandC_c::s_ptr = nullptr;

SPECIAL_ACTOR_PROFILE(OBJ_ROULETTE_ISLAND_C, dAcOrouletteIslandC_c, fProfile::OBJ_ROULETTE_ISLAND_C, 0x1CA, 0, 2);

STATE_DEFINE(dAcOrouletteIslandC_c, Wait);
STATE_DEFINE(dAcOrouletteIslandC_c, Play);

dAcOrouletteIslandC_c::dAcOrouletteIslandC_c() : mStateMgr(*this, sStateID::null)
{
    s_ptr = this;
}
dAcOrouletteIslandC_c::~dAcOrouletteIslandC_c() {
    s_ptr = nullptr;
}

void dAcOrouletteIslandC_c::initializeState_Wait() {
    mShouldStartPlay = false;
}

void dAcOrouletteIslandC_c::executeState_Wait() {
    if (!mShouldStartPlay) return;

    mStateMgr.changeState(StateID_Play);
    return;
}

void dAcOrouletteIslandC_c::finalizeState_Wait() {}

void dAcOrouletteIslandC_c::initializeState_Play() {
    mShouldEndMinigame = false;
    mPlayerOnIsland = false;
}


void dAcOrouletteIslandC_c::executeState_Play() {
    if(mPlayerOnIsland) {
        dRumble_c::start(dRumble_c::sRumblePreset3, 0x11);
        dLytMiniGame_c::GetInstance()->fn_80295900(0);

        dAcOfortuneRing_c *fortune_ring = getAcOfortuneRingPtr();
        fortune_ring->finishGame(0);
        mStateMgr.changeState(StateID_Wait);
    } else if(mShouldEndMinigame) {
        mStateMgr.changeState(StateID_Wait);
    }
}


void dAcOrouletteIslandC_c::finalizeState_Play() {}

bool dAcOrouletteIslandC_c::initModels(){
    mResFile = nw4r::g3d::ResFile(getOarcResFile("IslRouMain"));

    dStage_c::bindStageResToFile(&mResFile);
    dStage_c::bindSkyCmnToResFile(&mResFile);

    nw4r::g3d::ResMdl res_mdl = mResFile.GetResMdl("IslRouMain");

    bool result = mModel1.create(res_mdl, &mAllocator, 0x120, 1, nullptr);

    if(!result)return result;

    nw4r::g3d::ResMdl res_mdl_2 = mResFile.GetResMdl("IslRouMain_s");

    result = mModel2.create(res_mdl_2, &mAllocator, 0x120, 1, nullptr);

    if(!result)return result;

    cBgD_t* dzb_data = (cBgD_t*)getOarcFile("IslRouMain","dzb/IslRouMain.dzb");
    PLC* plc_data = (PLC*)getOarcFile("IslRouMain","dat/IslRouMain.plc");

    updateMatrix();
    mModel1.setLocalMtx(mWorldMtx);
    mModel2.setLocalMtx(mWorldMtx);

    mModel1.setScale(mScale);
    mModel2.setScale(mScale);

    bool success = (mBgCollision.Set(dzb_data, plc_data, 1, &mWorldMtx, &mScale) == 0);

	if (!success) {
        return success;
    } else {
        mBgCollision.Lock();
        return true;
    }
}

dAcOrouletteIslandC_c* dAcOrouletteIslandC_c::getPtr() {
    return s_ptr;
}


int dAcOrouletteIslandC_c::draw(){
    drawModelType1(&mModel1);
    drawModelType1(&mModel2);
	return 1;
}
int dAcOrouletteIslandC_c::execute(){
	mStateMgr.executeState();
    return 1;
}

int dAcOrouletteIslandC_c::init(){
    CREATE_ALLOCATOR(dAcOrouletteIslandC_c);

    dBgS::GetInstance()->Regist(&mBgCollision, this);
    mStateMgr.changeState(StateID_Wait);
    mModel1.setPriorityDraw(0x1c, 9);
    mModel2.setPriorityDraw(0x22, 9);

    mVec3_c min;
    mVec3_c max;
    mModel1.getBounds(&min, &max);

    mBoundingBox.Set(min, max);

    mCullingDistance = 500000.0;

    mBgCollision.SetRideCallback(&dAcOrouletteIslandC_c::interactionWithBgCallback);

    return SUCCEEDED;
}

void dAcOrouletteIslandC_c::interactionWithBgCallback(dBgW * i_col, dAcObjBase_c * i_actor, dAcObjBase_c * i_other)
{
	if(i_other->isActorPlayer() && i_actor != nullptr)
	{
        dAcOrouletteIslandC_c* island = static_cast<dAcOrouletteIslandC_c*>(i_actor);
        island->mPlayerOnIsland = true;

        /* Land on Island First Time -> map text appears */
        if(StoryflagManager::sInstance->getCounterOrFlag(STORYFLAG_FUN_FUN_ISLAND_DISCOVERED) == false) {
            StoryflagManager::sInstance->setFlag(STORYFLAG_FUN_FUN_ISLAND_DISCOVERED);
        }
    }
}

int dAcOrouletteIslandC_c::fn_358_800(){
	return 1;
}
