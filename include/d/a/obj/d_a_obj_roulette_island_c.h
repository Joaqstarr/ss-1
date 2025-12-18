#ifndef D_A_OBJ_ROULETTE_ISLAND_C_H
#define D_A_OBJ_ROULETTE_ISLAND_C_H

#include "d/a/obj/d_a_obj_base.h"
#include "s/s_State.hpp"
#include "s/s_StateMgr.hpp"
#include "d/col/bg/d_bg_w.h"
#include "m/m3d/m_smdl.h"

class dAcOrouletteIslandC_c : public dAcObjBase_c {
public:
    dAcOrouletteIslandC_c();
    virtual ~dAcOrouletteIslandC_c();

    static dAcOrouletteIslandC_c* getPtr();
    bool initModels();
    int draw() override;
    int execute() override;
    int init() override;
    static void interactionWithBgCallback(dBgW * i_col, dAcObjBase_c * i_actor, dAcObjBase_c * i_other);
    int fn_358_800();

    STATE_FUNC_DECLARE(dAcOrouletteIslandC_c, Wait);
    STATE_FUNC_DECLARE(dAcOrouletteIslandC_c, Play);

    /* 0x330 */ m3d::smdl_c mModel1;
    /* 0x34C */ m3d::smdl_c mModel2;

    /* 0x368 */ nw4r::g3d::ResFile mResFile;

    /* 0x36C */ dBgW mBgCollision;


private:
    /* 0x57C */ STATE_MGR_DECLARE(dAcOrouletteIslandC_c);

    /* 0x5B8 */ bool mPlayerOnIsland;
    /* 0x5B9 */ bool mShouldStartPlay;
    /* 0x5BA */ bool mShouldEndMinigame;

    static dAcOrouletteIslandC_c* s_ptr;

};

#endif
