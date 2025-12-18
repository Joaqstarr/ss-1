#include "d/a/obj/d_a_obj_fortune_ring.h"
#include "d/lyt/d_lyt_mini_game.h"
#include "d/a/d_a_player.h"
#include "d/a/obj/d_a_obj_roulette_island_c.h"
#include "d/a/npc/d_a_npc_dive_game_judge.h"
#include "d/d_message.h"

dAcOfortuneRing_c *dAcOfortuneRing_c::PTR = nullptr;


SPECIAL_ACTOR_PROFILE(OBJ_FORTUNE_RING, dAcOfortuneRing_c, fProfile::OBJ_FORTUNE_RING, 0x1C6, 0, 0);

STATE_DEFINE(dAcOfortuneRing_c, Wait);
STATE_DEFINE(dAcOfortuneRing_c, Play);

dAcOfortuneRing_c::dAcOfortuneRing_c() : mStateMgr(*this, sStateID::null) {}
dAcOfortuneRing_c::~dAcOfortuneRing_c() {}

void dAcOfortuneRing_c::initializeState_Wait() {
    mShouldStart = false;
    mIsFalling = false;
}
void dAcOfortuneRing_c::executeState_Wait() {
    if(!mShouldStart) {
        return;
    }
    mStateMgr.changeState(StateID_Play);
}
void dAcOfortuneRing_c::finalizeState_Wait() {}

void dAcOfortuneRing_c::initializeState_Play() {
    mMultiplier = 1;
    mScore = 0;
    InitRings();
    dLytMiniGame_c::GetInstance()->scoreRelatedInit();
    dLytMiniGame_c::GetInstance()->setDisplayedPoints(mMultiplier);

}

u8 IsPlayerBelowRouletteIsland() {
    dAcOrouletteIslandC_c* island = dAcOrouletteIslandC_c::getPtr();
    return dAcPy_c::GetLink()->mPosition.y + 500 < island->mPosition.y;
}

void dAcOfortuneRing_c::executeState_Play() {
    dLytMiniGame_c::GetInstance()->setDisplayedPoints(mMultiplier);
    const dAcPy_c* link = dAcPy_c::GetLink();

    if(mShouldStart && link->mVelocity.y <= 0.0f) {
        mIsFalling = true;
    }
    if(mIsFalling){
        for(int i = 0; i < mRingCount; i++){
            if(mRings[i].mPos.y < link->mPosition.y + 40){
                mRings[i].updateRotation();
                mRings[i].checkPlayerCollision();
            }
        }
    }

    if(mShouldStart && IsPlayerBelowRouletteIsland()){
        dLytMiniGame_c::GetInstance()->setComplete();
        finishGame(0);
    }
}

void dAcOfortuneRing_c::finalizeState_Play() {
    dLytMiniGame_c::GetInstance()->startFinish();
}

void dAcOfortuneRing_c::InitRings(){ //INCOMPLETE
    static const f32 RING_RADII[10] = {
        1400.0f, 1000.0f, 800.0f, 800.0f, 1100.0f,
        1000.0f,    0.0f, 700.0f, 800.0f, 1000.0f
    };

    static const s16 RING_UNK_SHORTS[10] = {
        200, 100, 0, 100, 200,
        100,   0, 100, 200, 100
    };

    static const u8 RING_CONFIG_A[10] = {
        0, 1, 0, 1, 0, 1, 0, 1, 0, 1
    };

    static const u8 RING_CONFIG_B[10] = {
        0, 0, 3, 0, 4, 0, 1, 0, 4, 0
    };

    static const u8 RING_CONFIG_C[10] = {
        0, 1, 0, 1, 0, 1, 0, 1, 0, 1
    };

    mRingCount = 10;

    for(int i = 0; i < mRingCount; i++){
        SingleFortuneRing* ring = &this->mRings[i];

        // 1. Set Position
        // Rings are stacked vertically. Y increases by 2000.0f for each ring.
        // X and Z match the actor's base position.
        ring->mPos.x = mPosition.x;
        ring->mPos.y = mPosition.y + ((float)(i + 1) * 2000.0f);
        ring->mPos.z = mPosition.z;

        // 2. Apply Config Properties
        ring->field_0x34a = RING_CONFIG_A[i];
        ring->field_0x34b = RING_CONFIG_B[i];
        ring->mRadius     = RING_RADII[i];      // field_0x34c
        ring->field_0x354 = RING_UNK_SHORTS[i];
        ring->field_0x347 = RING_CONFIG_C[i];

        ring->mRotationY = (s16)(cM::rnd() * 65535.0f); // field_0x330

        //ring->initModel();     // fn_354_11A0
        //ring->initCollision(); // fn_354_12D0

        ring->field_0x346 = 0;
        ring->field_0x348 = 0;
    }

}
void dAcOfortuneRing_c::finishGame( int landingTile) {
    if (landingTile == 6) {
        this->mMultiplier = 1;
        dLytMiniGame_c::GetInstance()->setDisplayedPoints(1);
    }

    dAcNpcDiveGameJudge_c* judge = nullptr;

    while(true){
        judge = (dAcNpcDiveGameJudge_c*)fManager_c::searchBaseByProfName(
                    fProfile::NPC_DIVE_GAME_JUDGE,
                    (dBase_c*)judge
                );
        if (judge == nullptr) break;

        judge->finishMinigame(landingTile, this->mScore, this->mMultiplier, 0);
    }
    dMessage_c::getInstance()->mMinigameResultPoints = this->mMultiplier;
    mStateMgr.changeState(StateID_Wait);
}

void dAcOfortuneRing_c::updateRings(){
	for(int i = 0; i < mRingCount; i++){
    	if(mRings[0].mPos.y < dAcPy_c::GetLink()->mPosition.y + 40){
            mRings[i].updateRing();
    	}
    }
}
dAcOfortuneRing_c * getAcOfortuneRingPtr()
{
    return dAcOfortuneRing_c::PTR;
}

void SingleFortuneRing::updateRotation()
{


}
void SingleFortuneRing::checkPlayerCollision()
{


}

void SingleFortuneRing::updateRing(){

}

