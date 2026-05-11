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

dAcOfortuneRing_c::dAcOfortuneRing_c() : mStateMgr(*this) {}
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
    initRings();
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
            if(mRings[i].mPosition.y < link->mPosition.y + 40){
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

void dAcOfortuneRing_c::initRings(){ //INCOMPLETE
    static const u8 ring_count[10] = {
        0, 1, 0, 1, 0, 1, 0, 1, 0, 1
    };
    static const u8 balloon_count[10] = {
        0, 0, 3, 0, 4, 0, 1, 0, 4, 0
    };
    static const f32 RING_RADII[10] = {
        1400.0f, 1000.0f, 800.0f, 800.0f, 1100.0f,
        1000.0f,    0.0f, 700.0f, 800.0f, 1000.0f
    };

    static const s16 RING_UNK_SHORTS[10] = {
        200, 100, 0, 100, 200,
        100,   0, 100, 200, 100
    };

    static const bool ring_bools[10] = {
        false, true, false, true, false, true, false, true, false, true
    };





    mRingCount = 10;

    for(int i = 0; i < mRingCount; i++){
        SingleFortuneRing* ring = &this->mRings[i];

        ring->mPosition.x = mPosition.x;
        ring->mPosition.y = mPosition.y + ((i + 1) * 2000.0f);
        ring->mPosition.z = mPosition.z;

        ring->mRingCount = ring_count[i];
        ring->mBalloonCount = balloon_count[i];
        ring->mRadius = RING_RADII[i];
        ring->mUnkShort1 = RING_UNK_SHORTS[i];
        ring->mUnkBool2 = ring_bools[i];

        ring->mRotationY = (s16)(cM::rnd() * 65535.0f);

        setupCircularSlotPositions(ring);
        ring->randomizeRingPositions();

        ring->mUnkBool1 = 0;
        ring->mUnkBool3 = false;
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
    	if(mRings[0].mPosition.y < dAcPy_c::GetLink()->mPosition.y + 40){
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

bool SingleFortuneRing::playerDistanceCheck(mVec3_c *param_2){
return true;

}

void setupCircularSlotPositions(SingleFortuneRing* ring){
    int totalItems = (ring->mRingCount + ring->mBalloonCount) & 0xFF;

    if (totalItems == 0) return;

    s16 angleStep = (s16)(0xFFFF / totalItems);

    for (int i = 0; i < totalItems; i++) {
        s16 currentAngle = ring->mRotationY + (s16)(i * angleStep);

        f32 sinVal = nw4r::math::SinFIdx((f32)currentAngle * (1.0f / 256.0f));
        f32 cosVal = nw4r::math::CosFIdx((f32)currentAngle * (1.0f / 256.0f));

        mVec3_c localPos;
        localPos.x = ring->mPosition.x + (ring->mRadius * sinVal);
        localPos.y = ring->mPosition.y;
        localPos.z = ring->mPosition.z + (ring->mRadius * cosVal);

        ring->mPositions[i] = localPos;
    }
}

void SingleFortuneRing::randomizeRingPositions(){
    int totalItems = mRingCount + mBalloonCount;

    if (totalItems == 0) return;

    for (int i = 0; i < totalItems; i++) {
        mUnkArr[i] = 0;
    }

    u8 rings_placed = 0;
    while (rings_placed < mRingCount) {

        f32 rnd = cM::rnd();
        int randIndex = (int)((float)totalItems * rnd);

        if (randIndex >= totalItems) randIndex = 0;

        if (mUnkArr[randIndex] == 0) {
            mUnkArr[randIndex] = 1;
            rings_placed++;
        }
    }
}
