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
private:

public:
    bool initModels();
    STATE_FUNC_DECLARE(dAcOrouletteIslandC_c, Wait);
    STATE_FUNC_DECLARE(dAcOrouletteIslandC_c, Play);

    /* 0x330 */ m3d::smdl_c model1;
    /* 0x34C */ m3d::smdl_c model2;

    /* 0x368 */ nw4r::g3d::ResFile mpResFile;

    /* 0x36C */ dBgW bgCollision;

private:
    /* 0x??? */ STATE_MGR_DECLARE(dAcOrouletteIslandC_c);

    /* 0x5B8 */ bool playerOnIsland;
    /* 0x5B9 */ bool shouldStartPlay;
    /* 0x5BA */ u8 padding_5BA;
    /* 0x5BB */ u8 padding_5BB;

};

#endif
