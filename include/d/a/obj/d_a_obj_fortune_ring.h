#ifndef D_A_OBJ_FORTUNE_RING_H
#define D_A_OBJ_FORTUNE_RING_H

#include "d/a/obj/d_a_obj_base.h"
#include "s/s_State.hpp"
#include "s/s_StateMgr.hpp"
#include "d/a/obj/d_a_obj_ring.h"
#include "toBeSorted/d_emitter.h"
#include "m/m_vec.h"

struct SingleFortuneRing {
    /* 0x000 */ // ... other members ...

    /* 0x234 */ mVec3_c mPos;

    /* 0x330 */ s16 mRotationY;

    /* 0x346 */ u8 field_0x346;
    /* 0x347 */ u8 field_0x347;
    /* 0x348 */ u8 field_0x348;
    /* 0x349 */ u8 padding_349;

    /* 0x34A */ u8 field_0x34a;
    /* 0x34B */ u8 field_0x34b;
    /* 0x34C */ f32 mRadius;

    /* 0x354 */ s16 field_0x354;



    void updateRotation();
    void checkPlayerCollision();
    void updateRing();
};

class dAcOfortuneRing_c : public dAcObjBase_c {
public:
    dAcOfortuneRing_c();
    virtual ~dAcOfortuneRing_c();
    void InitRings();
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
