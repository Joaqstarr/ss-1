#ifndef D_A_OBJ_FORTUNE_RING_H
#define D_A_OBJ_FORTUNE_RING_H

#include "d/a/obj/d_a_obj_base.h"
#include "s/s_State.hpp"
#include "s/s_StateMgr.hpp"
#include "d/a/obj/d_a_obj_ring.h"
#include "toBeSorted/d_emitter.h"

class dAcOfortuneRing_c : public dAcObjBase_c {
public:
    dAcOfortuneRing_c();
    virtual ~dAcOfortuneRing_c();

    STATE_FUNC_DECLARE(dAcOfortuneRing_c, Wait);
    STATE_FUNC_DECLARE(dAcOfortuneRing_c, Play);

    static dAcOfortuneRing_c* PTR;

    /* 0x330 */ s32 mUnknownInt;
    /* 0x334 */ dAcOring_c mRings[10];
    /* 0x24a4 */ STATE_MGR_DECLARE(dAcOfortuneRing_c);
    /* 0x24e0 */ dEmitter_c mEffects;
    /* 0x2514 */ bool mShouldStart;
    /* 0x2515 */ bool mUnknownFlag;
    /* 0x2516 */ u8 padding_2516;
    /* 0x2517 */ u8 mRingCount;
    /* 0x2518 */ s32 mMultiplier;


};

#endif
