#include "egg/core/eggHeap.h"
#include "JSystem/JParticle/JPAResourceLoader.h"
#include "JSystem/JParticle/JPABaseShape.h"
#include "JSystem/JParticle/JPAChildShape.h"
#include "JSystem/JParticle/JPADynamicsBlock.h"
#include "JSystem/JParticle/JPAExTexShape.h"
#include "JSystem/JParticle/JPAExtraShape.h"
#include "JSystem/JParticle/JPAFieldBlock.h"
#include "JSystem/JParticle/JPAKeyBlock.h"
#include "JSystem/JParticle/JPAResource.h"
#include "JSystem/JParticle/JPAResourceManager.h"
#include "JSystem/JUtility/JUTAssert.h"

JPAResourceLoader::JPAResourceLoader(u8 const* data, JPAResourceManager* mgr) {
    if (*(u32*)(data + 4) == '2-11') {
        load_jpc(data, mgr);
    } else {
        JUT_WARN(48, "JPA : wrong version file\n");
    }
}

struct JPAResourceHeader {
    /* 0x0 */ u16 mUsrIdx;
    /* 0x2 */ u16 mBlockNum;
    /* 0x4 */ u8 mFieldBlockNum;
    /* 0x5 */ u8 mKeyBlockNum;
    /* 0x6 */ u8 mTDB1Num;
};

void JPAResourceLoader::load_jpc(u8 const* data, JPAResourceManager* p_res_mgr) {
    EGG::Heap* heap = p_res_mgr->mpHeap;
    p_res_mgr->resMaxNum = *(u16*)(data + 8);
    p_res_mgr->texMaxNum = *(u16*)(data + 0xA);
    p_res_mgr->pResAry = new (heap) JPAResource*[p_res_mgr->resMaxNum];
    p_res_mgr->pTexAry = new (heap) JPATexture*[p_res_mgr->texMaxNum];
    JUT_ASSERT(199, (p_res_mgr->pResAry != NULL) && (p_res_mgr->pTexAry != 0));

    u32 offset = 0x10;
    for (int i = 0; i < *(u16*)(data + 8); i++) {
        JPAResourceHeader* header = (JPAResourceHeader*)(data + offset);
        JPAResource* p_res = new (heap) JPAResource();
        JUT_ASSERT(211, p_res != NULL);
        p_res->fldNum = header->mFieldBlockNum;
        p_res->ppFld = p_res->fldNum != 0 ?
            new (heap) JPAFieldBlock*[p_res->fldNum] : NULL;
        JUT_ASSERT(216, (p_res->ppFld != NULL) || (p_res->fldNum == 0));
        p_res->keyNum = header->mKeyBlockNum;
        p_res->ppKey = p_res->keyNum != 0 ?
            new (heap) JPAKeyBlock*[p_res->keyNum] : NULL;
        JUT_ASSERT(221, (p_res->ppKey != NULL) || (p_res->keyNum == 0));
        p_res->texNum = header->mTDB1Num;
        p_res->mpTDB1 = NULL;
        p_res->mUsrIdx = header->mUsrIdx;

        offset += 8;
        u32 fld_no = 0;
        u32 key_no = 0;

        for (int j = 0; j < header->mBlockNum; j++) {
            u32 magic = *(u32*)(data + offset);
            u32 size = *(u32*)(data + offset + 4);
            switch (magic) {
            case 'FLD1':
                p_res->ppFld[fld_no] = new (heap) JPAFieldBlock(data + offset, heap);
                JUT_ASSERT(244, p_res->ppFld[fld_no] != NULL);
                fld_no++;
                break;
            case 'KFA1':
                p_res->ppKey[key_no] = new (heap) JPAKeyBlock(data + offset);
                JUT_ASSERT(249, p_res->ppKey[key_no] != NULL);
                key_no++;
                break;
            case 'BEM1':
                p_res->pDyn = new (heap) JPADynamicsBlock(data + offset);
                JUT_ASSERT(254, p_res->pDyn != NULL);
                break;
            case 'BSP1':
                p_res->pBsp = new (heap) JPABaseShape(data + offset, heap);
                JUT_ASSERT(258, p_res->pBsp != NULL);
                break;
            case 'ESP1':
                p_res->pEsp = new (heap) JPAExtraShape(data + offset);
                JUT_ASSERT(262, p_res->pEsp != NULL);
                break;
            case 'SSP1':
                p_res->pCsp = new (heap) JPAChildShape(data + offset);
                JUT_ASSERT(266, p_res->pCsp != NULL);
                break;
            case 'ETX1':
                p_res->pEts = new (heap) JPAExTexShape(data + offset);
                JUT_ASSERT(270, p_res->pEts != NULL);
                break;
            case 'TDB1':
                p_res->mpTDB1 = (const u16*)(data + offset + 8);
                break;
            default:
                JUT_WARN(275, "JPA : wrong type block in jpc file %d %x\n", header->mBlockNum, offset);
                break;
            }
            offset += size;
        }

        p_res->init(heap);
        p_res_mgr->registRes(p_res);
    }

    offset = *(u32*)(data + 0xC);
    for (int i = 0; i < *(u16*)(data + 0xA); i++) {
        u32 size = *(u32*)(data + offset + 4);
        JPATexture* p_tex = new (heap) JPATexture(data + offset);
        JUT_ASSERT(298, p_tex != NULL);
        p_res_mgr->registTex(p_tex);
        offset += size;
    }
}
