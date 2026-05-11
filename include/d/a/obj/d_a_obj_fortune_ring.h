#ifndef D_A_OBJ_FORTUNE_RING_H
#define D_A_OBJ_FORTUNE_RING_H

#include "d/a/obj/d_a_obj_base.h"
#include "s/s_State.hpp"
#include "s/s_StateMgr.hpp"
#include "d/a/obj/d_a_obj_ring.h"
#include "toBeSorted/d_emitter.h"
#include "m/m_vec.h"
#include "include/m/m_vec.h"
#include "m/m3d/m_smdl.h"

struct SingleFortuneRing {
    /* 0x004 */ m3d::smdl_c mModels1[10];
    /* 0x11c */ m3d::smdl_c mModels2[10];
    /* 0x234 */ mVec3_c mPosition;
    /* 0x240 */ mVec3_c mPositions[10];
    /* 0x330 */ s16 mRotationY;
    /* 0x332 */ u8 mUnkArr[20];
    /* 0x346 */ bool mUnkBool1;
    /* 0x347 */ bool mUnkBool2;
    /* 0x348 */ bool mUnkBool3;
    /* 0x349 */ u8 mUnkByte1;
    /* 0x34a */ u8 mRingCount;
    /* 0x34b */ u8 mBalloonCount;
    /* 0x34c */ f32 mRadius;
    /* 0x350 */ f32 mUnkFloat2;
    /* 0x354 */ s16 mUnkShort1;




    void updateRotation();
    void checkPlayerCollision();
    void updateRing();
    bool playerDistanceCheck(mVec3_c *param_2);
    void randomizeRingPositions();

};
void setupCircularSlotPositions(SingleFortuneRing* ring);

class dAcOfortuneRing_c : public dAcObjBase_c {
public:
    dAcOfortuneRing_c();
    virtual ~dAcOfortuneRing_c();
    void initRings();
    void finishGame( int landingTile );
    void updateRings();
    STATE_FUNC_DECLARE(dAcOfortuneRing_c, Wait);
    STATE_FUNC_DECLARE(dAcOfortuneRing_c, Play);

    static dAcOfortuneRing_c* PTR;

    /* 0x330 */ s32 mUnknownInt;
    /* 0x334 */ SingleFortuneRing mRings[10];
    /* 0x24a4 */ STATE_MGR_DECLARE(dAcOfortuneRing_c);
    /* 0x24e0 */ dEmitter_c mEffects;
    /* 0x2514 */ bool mShouldStart;
    /* 0x2515 */ bool mIsFalling;
    /* 0x2516 */ u8 padding_2516;
    /* 0x2517 */ u8 mRingCount;
    /* 0x2518 */ u8 mMultiplier;
    /* 0x2519 */ u8 mScore;


};
dAcOfortuneRing_c* getAcOfortuneRingPtr();
#endif
