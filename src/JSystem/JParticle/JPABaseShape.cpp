#include "JSystem/JParticle/JPAExTexShape.h"
#include "egg/core/eggHeap.h"
#include "JSystem/JParticle/JPABaseShape.h"
#include "JSystem/JParticle/JPAParticle.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JSystem/JParticle/JPAResourceManager.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "nw4r/math/math_triangular.h"
#include "rvl/MTX.h"
#include "rvl/GX.h"

void JPASetPointSize(JPAEmitterWorkData* work) {
    GXSetPointSize((u8)(25.0f * work->mGlobalPtclScl.x), GX_TO_ONE);
}

void JPASetLineWidth(JPAEmitterWorkData* work) {
    GXSetLineWidth((u8)(25.0f * work->mGlobalPtclScl.x), GX_TO_ONE);
}

void JPASetPointSize(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    GXSetPointSize((u8)(ptcl->mParticleScaleX * (25.0f * work->mGlobalPtclScl.x)), GX_TO_ONE);
}

void JPASetLineWidth(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    GXSetLineWidth((u8)(ptcl->mParticleScaleX * (25.0f * work->mGlobalPtclScl.x)), GX_TO_ONE);
}

void JPARegistPrm(JPAEmitterWorkData* work) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor prm = emtr->mPrmClr;
    prm.r = COLOR_MULTI(prm.r, emtr->mGlobalPrmClr.r);
    prm.g = COLOR_MULTI(prm.g, emtr->mGlobalPrmClr.g);
    prm.b = COLOR_MULTI(prm.b, emtr->mGlobalPrmClr.b);
    prm.a = COLOR_MULTI(prm.a, emtr->mGlobalPrmClr.a);
    GXSetTevColor(GX_TEVREG0, prm);
}

void JPARegistEnv(JPAEmitterWorkData* work) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor env = emtr->mEnvClr;
    env.r = COLOR_MULTI(env.r, emtr->mGlobalEnvClr.r);
    env.g = COLOR_MULTI(env.g, emtr->mGlobalEnvClr.g);
    env.b = COLOR_MULTI(env.b, emtr->mGlobalEnvClr.b);
    GXSetTevColor(GX_TEVREG1, env);
}

void JPARegistPrmEnv(JPAEmitterWorkData* work) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor prm = emtr->mPrmClr;
    GXColor env = emtr->mEnvClr;
    prm.r = COLOR_MULTI(prm.r, emtr->mGlobalPrmClr.r);
    prm.g = COLOR_MULTI(prm.g, emtr->mGlobalPrmClr.g);
    prm.b = COLOR_MULTI(prm.b, emtr->mGlobalPrmClr.b);
    prm.a = COLOR_MULTI(prm.a, emtr->mGlobalPrmClr.a);
    env.r = COLOR_MULTI(env.r, emtr->mGlobalEnvClr.r);
    env.g = COLOR_MULTI(env.g, emtr->mGlobalEnvClr.g);
    env.b = COLOR_MULTI(env.b, emtr->mGlobalEnvClr.b);
    GXSetTevColor(GX_TEVREG0, prm);
    GXSetTevColor(GX_TEVREG1, env);
}

void JPARegistAlpha(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor prm = emtr->mPrmClr;
    prm.r = COLOR_MULTI(prm.r, emtr->mGlobalPrmClr.r);
    prm.g = COLOR_MULTI(prm.g, emtr->mGlobalPrmClr.g);
    prm.b = COLOR_MULTI(prm.b, emtr->mGlobalPrmClr.b);
    prm.a = COLOR_MULTI(prm.a, emtr->mGlobalPrmClr.a);
    prm.a = COLOR_MULTI(prm.a, ptcl->mPrmColorAlphaAnm);
    GXSetTevColor(GX_TEVREG0, prm);
}

void JPARegistPrmAlpha(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor prm = ptcl->mPrmClr;
    prm.r = COLOR_MULTI(prm.r, emtr->mGlobalPrmClr.r);
    prm.g = COLOR_MULTI(prm.g, emtr->mGlobalPrmClr.g);
    prm.b = COLOR_MULTI(prm.b, emtr->mGlobalPrmClr.b);
    prm.a = COLOR_MULTI(prm.a, emtr->mGlobalPrmClr.a);
    prm.a = COLOR_MULTI(prm.a, ptcl->mPrmColorAlphaAnm);
    GXSetTevColor(GX_TEVREG0, prm);
}

void JPARegistPrmAlphaEnv(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor prm = ptcl->mPrmClr;
    GXColor env = ptcl->mEnvClr;
    prm.r = COLOR_MULTI(prm.r, emtr->mGlobalPrmClr.r);
    prm.g = COLOR_MULTI(prm.g, emtr->mGlobalPrmClr.g);
    prm.b = COLOR_MULTI(prm.b, emtr->mGlobalPrmClr.b);
    prm.a = COLOR_MULTI(prm.a, emtr->mGlobalPrmClr.a);
    prm.a = COLOR_MULTI(prm.a, ptcl->mPrmColorAlphaAnm);
    env.r = COLOR_MULTI(env.r, emtr->mGlobalEnvClr.r);
    env.g = COLOR_MULTI(env.g, emtr->mGlobalEnvClr.g);
    env.b = COLOR_MULTI(env.b, emtr->mGlobalEnvClr.b);
    GXSetTevColor(GX_TEVREG0, prm);
    GXSetTevColor(GX_TEVREG1, env);
}

void JPARegistAlphaEnv(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor prm = emtr->mPrmClr;
    GXColor env = ptcl->mEnvClr;
    prm.r = COLOR_MULTI(prm.r, emtr->mGlobalPrmClr.r);
    prm.g = COLOR_MULTI(prm.g, emtr->mGlobalPrmClr.g);
    prm.b = COLOR_MULTI(prm.b, emtr->mGlobalPrmClr.b);
    prm.a = COLOR_MULTI(prm.a, emtr->mGlobalPrmClr.a);
    prm.a = COLOR_MULTI(prm.a, ptcl->mPrmColorAlphaAnm);
    env.r = COLOR_MULTI(env.r, emtr->mGlobalEnvClr.r);
    env.g = COLOR_MULTI(env.g, emtr->mGlobalEnvClr.g);
    env.b = COLOR_MULTI(env.b, emtr->mGlobalEnvClr.b);
    GXSetTevColor(GX_TEVREG0, prm);
    GXSetTevColor(GX_TEVREG1, env);
}

void JPARegistEnv(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    GXColor env = ptcl->mEnvClr;
    env.r = COLOR_MULTI(env.r, emtr->mGlobalEnvClr.r);
    env.g = COLOR_MULTI(env.g, emtr->mGlobalEnvClr.g);
    env.b = COLOR_MULTI(env.b, emtr->mGlobalEnvClr.b);
    GXSetTevColor(GX_TEVREG1, env);
}

void JPACalcClrIdxNormal(JPAEmitterWorkData* work) {
    JPABaseShape* bsp = work->mpRes->getBsp();
    s16 keyFrame;
    if (work->mpEmtr->mTick < bsp->getClrAnmMaxFrm()) {
        keyFrame = work->mpEmtr->mTick;
    } else {
        keyFrame = bsp->getClrAnmMaxFrm();
    }
    work->mClrKeyFrame = keyFrame;
}

void JPACalcClrIdxNormal(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    work->mClrKeyFrame = param_1->mAge < shape->getClrAnmMaxFrm() ? param_1->mAge : shape->getClrAnmMaxFrm();
}

void JPACalcClrIdxRepeat(JPAEmitterWorkData* work) {
    JPABaseShape* shape = work->mpRes->getBsp();
    work->mClrKeyFrame = work->mpEmtr->mTick % (shape->getClrAnmMaxFrm() + 1);
}

void JPACalcClrIdxRepeat(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    s32 r28 = shape->getClrAnmMaxFrm() + 1;
    work->mClrKeyFrame = (param_1->mAge + shape->getClrLoopOfst(param_1->mAnmRandom)) % r28;
}

void JPACalcClrIdxReverse(JPAEmitterWorkData* work) {
    JPABaseShape* shape = work->mpRes->getBsp();
    int maxFrm = shape->getClrAnmMaxFrm();
    u32 div = (work->mpEmtr->mTick / maxFrm) & 1;
    u32 rem = work->mpEmtr->mTick % maxFrm;
    work->mClrKeyFrame = rem + (div) * (maxFrm - rem * 2);
}

void JPACalcClrIdxReverse(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    s32 r29 = param_1->mAge + shape->getClrLoopOfst(param_1->mAnmRandom);
    s32 maxFrm = shape->getClrAnmMaxFrm();
    s32 div = (r29 / maxFrm) & 1;
    s32 rem = r29 % maxFrm;
    work->mClrKeyFrame = rem + (div) * (maxFrm - rem * 2);
}

void JPACalcClrIdxMerge(JPAEmitterWorkData* work) {
    work->mClrKeyFrame = 0;
}

void JPACalcClrIdxMerge(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    s32 maxFrm = shape->getClrAnmMaxFrm() + 1;
    work->mClrKeyFrame = (s32(param_1->mTime * maxFrm) + shape->getClrLoopOfst(param_1->mAnmRandom)) % maxFrm;
}

void JPACalcClrIdxRandom(JPAEmitterWorkData* work) {
    work->mClrKeyFrame = 0;
}

void JPACalcClrIdxRandom(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    work->mClrKeyFrame = shape->getClrLoopOfst(param_1->mAnmRandom) % (shape->getClrAnmMaxFrm() + 1);
}

void JPACalcPrm(JPAEmitterWorkData* work) {
    work->mpRes->getBsp()->getPrmClr(work->mClrKeyFrame, &work->mpEmtr->mPrmClr);
}

void JPACalcPrm(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    work->mpRes->getBsp()->getPrmClr(work->mClrKeyFrame, &ptcl->mPrmClr);
}

void JPACalcEnv(JPAEmitterWorkData* work) {
    work->mpRes->getBsp()->getEnvClr(work->mClrKeyFrame, &work->mpEmtr->mEnvClr);
}

void JPACalcEnv(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    work->mpRes->getBsp()->getEnvClr(work->mClrKeyFrame, &ptcl->mEnvClr);
}

void JPACalcColorCopy(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    ptcl->mPrmClr = emtr->mPrmClr;
    ptcl->mEnvClr = emtr->mEnvClr;
}

void JPAGenTexCrdMtxIdt(JPAEmitterWorkData* param_0) {
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
}

void JPAGenTexCrdMtxAnm(JPAEmitterWorkData* param_0) {
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
}

void JPAGenTexCrdMtxPrj(JPAEmitterWorkData* param_0) {
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
}

void JPAGenCalcTexCrdMtxAnm(JPAEmitterWorkData* work) {
    JPABaseShape* shape = work->mpRes->getBsp();
    f32 dVar16 = work->mpEmtr->mTick;
    f32 dVar15 = 0.5f * (1.0f + shape->getTilingS());
    f32 dVar14 = 0.5f * (1.0f + shape->getTilingT());
    f32 dVar11 = (dVar16 * shape->getIncTransX()) + shape->getInitTransX();
    f32 dVar10 = (dVar16 * shape->getIncTransY()) + shape->getInitTransY();
    f32 dVar13 = (dVar16 * shape->getIncScaleX()) + shape->getInitScaleX();
    f32 dVar12 = (dVar16 * shape->getIncScaleY()) + shape->getInitScaleY();
    s32 local_c0 = (dVar16 * shape->getIncRot()) + shape->getInitRot();
    f32 dVar8 = nw4r::math::SinIdx(local_c0);
    f32 dVar9 = nw4r::math::CosIdx(local_c0);
    Mtx local_108;
    local_108[0][0] = dVar13 * dVar9;
    local_108[0][1] = -dVar13 * dVar8;
    local_108[0][2] = 0.0f;
    local_108[0][3] =
        (dVar15 + (dVar13 * ((dVar8 * (dVar14 + dVar10)) - (dVar9 * (dVar15 + dVar11)))));
    local_108[1][0] = dVar12 * dVar8;
    local_108[1][1] = dVar12 * dVar9;
    local_108[1][2] = 0.0f;
    local_108[1][3] =
        (dVar14 + (-dVar12 * ((dVar8 * (dVar15 + dVar11)) + (dVar9 * (dVar14 + dVar10)))));
    local_108[2][0] = 0.0f;
    local_108[2][1] = 0.0f;
    local_108[2][2] = 1.0f;
    local_108[2][3] = 0.0f;
    GXLoadTexMtxImm(local_108, 0x1e, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1e, false, 0x7d);
}

void JPALoadCalcTexCrdMtxAnm(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    f32 dVar16 = param_1->mAge;
    f32 dVar15 = 0.5f * (1.0f + shape->getTilingS());
    f32 dVar14 = 0.5f * (1.0f + shape->getTilingT());
    f32 dVar11 = (dVar16 * shape->getIncTransX()) + shape->getInitTransX();
    f32 dVar10 = (dVar16 * shape->getIncTransY()) + shape->getInitTransY();
    f32 dVar13 = (dVar16 * shape->getIncScaleX()) + shape->getInitScaleX();
    f32 dVar12 = (dVar16 * shape->getIncScaleY()) + shape->getInitScaleY();
    s32 local_c0 = (dVar16 * shape->getIncRot()) + shape->getInitRot();
    f32 dVar8 = nw4r::math::SinIdx(local_c0);
    f32 dVar9 = nw4r::math::CosIdx(local_c0);
    Mtx local_108;
    local_108[0][0] = dVar13 * dVar9;
    local_108[0][1] = -dVar13 * dVar8;
    local_108[0][2] = 0.0f;
    local_108[0][3] =
        (dVar15 + (dVar13 * ((dVar8 * (dVar14 + dVar10)) - (dVar9 * (dVar15 + dVar11)))));
    local_108[1][0] = dVar12 * dVar8;
    local_108[1][1] = dVar12 * dVar9;
    local_108[1][2] = 0.0f;
    local_108[1][3] =
        (dVar14 + (-dVar12 * ((dVar8 * (dVar15 + dVar11)) + (dVar9 * (dVar14 + dVar10)))));
    local_108[2][0] = 0.0f;
    local_108[2][1] = 0.0f;
    local_108[2][2] = 1.0f;
    local_108[2][3] = 0.0f;
    GXLoadTexMtxImm(local_108, 0x1e, GX_MTX2x4);
}

void fn_8031A8C0(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    work->mpRes->getEts()->fn_8031DE80(work->mpRes->getBsp(), ptcl->getAge());
}

void JPALoadTex(JPAEmitterWorkData* work) {
    work->mpResMgr->load(work->mpRes->getTexIdx(work->mpRes->getBsp()->getTexIdx()), GX_TEXMAP0);
}

void JPALoadTexAnm(JPAEmitterWorkData* work) {
    work->mpResMgr->load(work->mpRes->getTexIdx(work->mpEmtr->mTexAnmIdx), GX_TEXMAP0);
}

void JPALoadTexAnm(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    work->mpResMgr->load(work->mpRes->getTexIdx(ptcl->mTexAnmIdx), GX_TEXMAP0);
}

void JPACalcTexIdxNormal(JPAEmitterWorkData* work) {
    JPABaseShape* shape = work->mpRes->getBsp();
    work->mpEmtr->mTexAnmIdx = shape->getTexIdx(shape->getTexAnmKeyNum() - 1 < work->mpEmtr->mTick ? shape->getTexAnmKeyNum() - 1 : work->mpEmtr->mTick);
}

void JPACalcTexIdxNormal(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    param_1->mTexAnmIdx = shape->getTexIdx(shape->getTexAnmKeyNum() - 1 < param_1->mAge ? shape->getTexAnmKeyNum() - 1 : param_1->mAge);
}

void JPACalcTexIdxRepeat(JPAEmitterWorkData* work) {
    JPABaseShape* shape = work->mpRes->getBsp();
    work->mpEmtr->mTexAnmIdx = shape->getTexIdx(work->mpEmtr->mTick % shape->getTexAnmKeyNum());
}

void JPACalcTexIdxRepeat(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    param_1->mTexAnmIdx = shape->getTexIdx(
        ((int)shape->getTexLoopOfst(param_1->mAnmRandom) + param_1->mAge)
            % shape->getTexAnmKeyNum());
}

void JPACalcTexIdxReverse(JPAEmitterWorkData* work) {
    JPABaseShape* shape = work->mpRes->getBsp();
    int tick = work->mpEmtr->mTick;
    int keyNum = (int)shape->getTexAnmKeyNum() - 1;
    int div = tick / keyNum & 1;
    int rem = tick % keyNum;
    work->mpEmtr->mTexAnmIdx = shape->getTexIdx(rem + div * (keyNum - rem * 2));
}

void JPACalcTexIdxReverse(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    s32 tick = shape->getTexLoopOfst(param_1->mAnmRandom) + param_1->mAge;
    int keyNum = (int)shape->getTexAnmKeyNum() - 1;
    int div = tick / keyNum & 1;
    int rem = tick % keyNum;
    param_1->mTexAnmIdx = shape->getTexIdx(rem + div * (keyNum - rem * 2));
}

void JPACalcTexIdxMerge(JPAEmitterWorkData* work) {
    work->mpEmtr->mTexAnmIdx = work->mpRes->getBsp()->getTexIdx();
}

void JPACalcTexIdxMerge(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    s32 maxFrm = shape->getTexAnmKeyNum();
    param_1->mTexAnmIdx = shape->getTexIdx((s32(maxFrm * param_1->mTime) + shape->getTexLoopOfst(param_1->mAnmRandom)) % maxFrm);
}

void JPACalcTexIdxRandom(JPAEmitterWorkData* work) {
    work->mpEmtr->mTexAnmIdx = work->mpRes->getBsp()->getTexIdx();
}

void JPACalcTexIdxRandom(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    JPABaseShape* shape = work->mpRes->getBsp();
    param_1->mTexAnmIdx = shape->getTexIdx(((int)shape->getTexLoopOfst(param_1->mAnmRandom))
        % shape->getTexAnmKeyNum());
}

void JPALoadPosMtxCam(JPAEmitterWorkData* work) {
    GXLoadPosMtxImm(work->mPosCamMtx, GX_PNMTX0);
}

static void noLoadPrj(JPAEmitterWorkData const* work, const Mtx srt) {
    /* empty function */
}

void loadPrj(JPAEmitterWorkData const* work, const Mtx srt) {
    Mtx mtx;
    MTXConcat(work->mPrjMtx, srt, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX3x4);
}

static void loadPrjAnm(JPAEmitterWorkData const* work, const Mtx srt) {
    JPABaseShape* shape = work->mpRes->getBsp();
    f32 dVar16 = work->mpEmtr->getAge();
    f32 dVar15 = 0.5f * (1.0f + shape->getTilingS());
    f32 dVar14 = 0.5f * (1.0f + shape->getTilingT());
    f32 dVar11 = (dVar16 * shape->getIncTransX()) + shape->getInitTransX();
    f32 dVar10 = (dVar16 * shape->getIncTransY()) + shape->getInitTransY();
    f32 dVar13 = (dVar16 * shape->getIncScaleX()) + shape->getInitScaleX();
    f32 dVar12 = (dVar16 * shape->getIncScaleY()) + shape->getInitScaleY();
    s32 local_c0 = (dVar16 * shape->getIncRot()) + shape->getInitRot();
    f32 dVar8 = nw4r::math::SinIdx(local_c0);
    f32 dVar9 = nw4r::math::CosIdx(local_c0);
    Mtx local_108;
    local_108[0][0] = dVar13 * dVar9;
    local_108[0][1] = -dVar13 * dVar8;
    local_108[0][2] =
        (dVar15 + (dVar13 * ((dVar8 * (dVar14 + dVar10)) - (dVar9 * (dVar15 + dVar11)))));
    local_108[0][3] = 0.0f;
    local_108[1][0] = dVar12 * dVar8;
    local_108[1][1] = dVar12 * dVar9;
    local_108[1][2] =
        (dVar14 + (-dVar12 * ((dVar8 * (dVar15 + dVar11)) + (dVar9 * (dVar14 + dVar10)))));
    local_108[1][3] = 0.0f;
    local_108[2][0] = 0.0f;
    local_108[2][1] = 0.0f;
    local_108[2][2] = 1.0f;
    local_108[2][3] = 0.0f;
    MTXConcat(local_108, work->mPrjMtx, local_108);
    MTXConcat(local_108, srt, local_108);
    GXLoadTexMtxImm(local_108, 0x1e, GX_MTX3x4);
}

static u8 ALIGN_DECL(32) jpa_dl[32] = {
    0x80, 0x00, 0x04, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static u8 ALIGN_DECL(32) jpa_dl_x[32] = {
    0x80, 0x00, 0x08, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x48, 0x00, 0x49, 0x01, 0x4A,
    0x02, 0x4B, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

typedef void (*projectionFunc)(JPAEmitterWorkData const*, const Mtx);

static projectionFunc p_prj[3] = {
    noLoadPrj,
    loadPrj,
    loadPrjAnm,
};

void JPADrawBillboard(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_48;
    MTXMultVec(work->mPosCamMtx, param_1->mPosition, local_48);
    Mtx local_38;
    local_38[0][0] = work->mGlobalPtclScl.x * param_1->mParticleScaleX;
    local_38[0][3] = local_48.x;
    local_38[1][1] = work->mGlobalPtclScl.y * param_1->mParticleScaleY;
    local_38[1][3] = local_48.y;
    local_38[2][2] = 1.0f;
    local_38[2][3] = local_48.z;
    local_38[0][1] = local_38[0][2] = local_38[1][0] = local_38[1][2] = local_38[2][0] = local_38[2][1] = 0.0f;
    GXLoadPosMtxImm(local_38, 0);
    p_prj[work->mPrjType](work, local_38);
    GXCallDisplayList(jpa_dl, sizeof(jpa_dl));
}

void JPADrawRotBillboard(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_48;
    MTXMultVec(work->mPosCamMtx, param_1->mPosition, local_48);
    f32 sinRot = nw4r::math::SinIdx((s16)param_1->mRotateAngle);
    f32 cosRot = nw4r::math::CosIdx((s16)param_1->mRotateAngle);
    f32 particleX = work->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 particleY = work->mGlobalPtclScl.y * param_1->mParticleScaleY;

    Mtx local_38;
    local_38[0][0] = cosRot * particleX;
    local_38[0][1] = -sinRot * particleY;
    local_38[0][3] = local_48.x;
    local_38[1][0] = sinRot * particleX;
    local_38[1][1] = cosRot * particleY;
    local_38[1][3] = local_48.y;
    local_38[2][2] = 1.0f;
    local_38[2][3] = local_48.z;
    local_38[0][2] = local_38[1][2] = local_38[2][0] = local_38[2][1] = 0.0f;
    GXLoadPosMtxImm(local_38, 0);
    p_prj[work->mPrjType](work, local_38);
    GXCallDisplayList(jpa_dl, sizeof(jpa_dl));
}

void JPADrawYBillboard(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_48;
    MTXMultVec(work->mPosCamMtx, param_1->mPosition, local_48);
    Mtx local_38;
    f32 particleX = work->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 particleY = work->mGlobalPtclScl.y * param_1->mParticleScaleY;
    local_38[0][0] = particleX;
    local_38[0][3] = local_48.x;
    local_38[1][1] = work->mYBBCamMtx[1][1] * particleY;
    local_38[1][2] = work->mYBBCamMtx[1][2];
    local_38[1][3] = local_48.y;
    local_38[2][1] = work->mYBBCamMtx[2][1] * particleY;
    local_38[2][2] = work->mYBBCamMtx[2][2];
    local_38[2][3] = local_48.z;
    local_38[0][1] = local_38[0][2] = local_38[1][0] = local_38[2][0] = 0.0f;
    GXLoadPosMtxImm(local_38, 0);
    p_prj[work->mPrjType](work, local_38);
    GXCallDisplayList(jpa_dl, sizeof(jpa_dl));
}

void JPADrawRotYBillboard(JPAEmitterWorkData* work, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_48;
    MTXMultVec(work->mPosCamMtx, param_1->mPosition, local_48);
    f32 sinRot = nw4r::math::SinIdx((s16)param_1->mRotateAngle);
    f32 cosRot = nw4r::math::CosIdx((s16)param_1->mRotateAngle);
    Mtx local_38;
    f32 particleX = work->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 particleY = work->mGlobalPtclScl.y * param_1->mParticleScaleY;
    f32 local_98 = (float)(sinRot * particleX);
    f32 local_94 = (float)(cosRot * particleY);
    f32 local_90 = work->mYBBCamMtx[1][1];
    f32 fVar1 = work->mYBBCamMtx[2][1];
    local_38[0][0] = (float)(cosRot * particleX);
    local_38[0][1] = (float)(-sinRot * particleY);
    local_38[0][2] = 0.0f;
    local_38[0][3] = local_48.x;
    local_38[1][0] = local_98 * local_90;
    local_38[1][1] = local_94 * local_90;
    local_38[1][2] = -fVar1;
    local_38[1][3] = local_48.y;
    local_38[2][0] = local_98 * fVar1;
    local_38[2][1] = local_94 * fVar1;
    local_38[2][2] = local_90;
    local_38[2][3] = local_48.z;
    GXLoadPosMtxImm(local_38, 0);
    p_prj[work->mPrjType](work, local_38);
    GXCallDisplayList(jpa_dl, sizeof(jpa_dl));
}

void dirTypeVel(JPAEmitterWorkData const* work, JPABaseParticle const* param_1,
                    EGG::Vector3f* param_2) {
    param_1->getVelVec(param_2);
}

void dirTypePos(JPAEmitterWorkData const* work, JPABaseParticle const* param_1,
                    EGG::Vector3f* param_2) {
    param_1->getLocalPosition(param_2);
}

void dirTypePosInv(JPAEmitterWorkData const* work, JPABaseParticle const* param_1,
                    EGG::Vector3f* param_2) {
    param_1->getLocalPosition(param_2);
    *param_2 = param_2->negated();
}

void dirTypeEmtrDir(JPAEmitterWorkData const* work, JPABaseParticle const* param_1,
                    EGG::Vector3f* param_2) {
    param_2->set(work->mGlobalEmtrDir);
}

void dirTypePrevPtcl(JPAEmitterWorkData const* work, JPABaseParticle const* param_1,
                    EGG::Vector3f* param_2) {
    EGG::Vector3f aTStack_24;
    param_1->getGlobalPosition(&aTStack_24);

    if (work->mpCurNode->getPrev() != work->mpAlivePtcl->getEnd()) {
        work->mpCurNode->getPrev()->getObject()->getGlobalPosition(param_2);
    } else {
        work->mpEmtr->calcEmitterGlobalPosition(param_2);
    }
    *param_2 -= aTStack_24;
}

static void rotTypeY(f32 param_0, f32 param_1, Mtx& param_2) {
    param_2[0][0] = param_1;
    param_2[0][1] = 0.0f;
    param_2[0][2] = -param_0;
    param_2[0][3] = 0.0f;
    param_2[1][0] = 0.0f;
    param_2[1][1] = 1.0f;
    param_2[1][2] = 0.0f;
    param_2[1][3] = 0.0f;
    param_2[2][0] = param_0;
    param_2[2][1] = 0.0f;
    param_2[2][2] = param_1;
    param_2[2][3] = 0.0f;
}

static void rotTypeX(f32 param_0, f32 param_1, Mtx& param_2) {
    param_2[0][0] = 1.0f;
    param_2[0][1] = 0.0f;
    param_2[0][2] = 0.0f;
    param_2[0][3] = 0.0f;
    param_2[1][0] = 0.0f;
    param_2[1][1] = param_1;
    param_2[1][2] = -param_0;
    param_2[1][3] = 0.0f;
    param_2[2][0] = 0.0f;
    param_2[2][1] = param_0;
    param_2[2][2] = param_1;
    param_2[2][3] = 0.0f;
}

static void rotTypeZ(f32 param_0, f32 param_1, Mtx& param_2) {
    param_2[0][0] = param_1;
    param_2[0][1] = -param_0;
    param_2[0][2] = 0.0f;
    param_2[0][3] = 0.0f;
    param_2[1][0] = param_0;
    param_2[1][1] = param_1;
    param_2[1][2] = 0.0f;
    param_2[1][3] = 0.0f;
    param_2[2][0] = 0.0f;
    param_2[2][1] = 0.0f;
    param_2[2][2] = 1.0f;
    param_2[2][3] = 0.0f;
}

static void rotTypeXYZ(f32 param_0, f32 param_1, Mtx& param_2) {
    f32 f3;
    f32 fVar1;
    f32 fVar2;
    f32 f4;
    f32 tmp;

    
    f3 = 0.33333298563957214f * (1.0f - param_1);
    tmp = 0.5773500204086304f * param_0;
    f4 = f3 + tmp;
    fVar1 =  f3 - tmp;
    fVar2 = f3 + param_1;
    param_2[0][0] = fVar2;
    param_2[0][1] = fVar1;
    param_2[0][2] = f4;
    param_2[0][3] = 0.0f;
    param_2[1][0] = f4;
    param_2[1][1] = fVar2;
    param_2[1][2] = fVar1;
    param_2[1][3] = 0.0f;
    param_2[2][0] = fVar1;
    param_2[2][1] = f4;
    param_2[2][2] = fVar2;
    param_2[2][3] = 0.0f;
}

static void basePlaneTypeXY(MtxP param_0, f32 param_1, f32 param_2) {
    param_0[0][0] *= param_1;
    param_0[1][0] *= param_1;
    param_0[2][0] *= param_1;
    param_0[0][1] *= param_2;
    param_0[1][1] *= param_2;
    param_0[2][1] *= param_2;
}

static void basePlaneTypeXZ(MtxP param_0, f32 param_1, f32 param_2) {
    param_0[0][0] *= param_1;
    param_0[1][0] *= param_1;
    param_0[2][0] *= param_1;
    param_0[0][2] *= param_2;
    param_0[1][2] *= param_2;
    param_0[2][2] *= param_2;
}

static void basePlaneTypeX(MtxP param_0, f32 param_1, f32 param_2) {
    param_0[0][0] *= param_1;
    param_0[1][0] *= param_1;
    param_0[2][0] *= param_1;
    param_0[0][1] *= param_2;
    param_0[1][1] *= param_2;
    param_0[2][1] *= param_2;
    param_0[0][2] *= param_1;
    param_0[1][2] *= param_1;
    param_0[2][2] *= param_1;
}

typedef void (*dirTypeFunc)(JPAEmitterWorkData const*, JPABaseParticle const*,
                            EGG::Vector3f*);
static dirTypeFunc p_direction[5] = {
    dirTypeVel, dirTypePos, dirTypePosInv,
    dirTypeEmtrDir, dirTypePrevPtcl,
};

typedef void (*rotTypeFunc)(f32, f32, Mtx&);
#pragma push
#pragma force_active on
static rotTypeFunc p_rot[5] = {
    rotTypeY,   rotTypeX, rotTypeZ,
    rotTypeXYZ, rotTypeY,
};
#pragma pop


typedef void (*planeFunc)(MtxP, f32, f32);

static planeFunc p_plane[3] = {
    basePlaneTypeXY,
    basePlaneTypeXZ,
    basePlaneTypeX,
};

static u8* p_dl[2] = {
    jpa_dl,
    jpa_dl_x,
};

void JPADrawDirection(JPAEmitterWorkData* param_0, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_6c;
    EGG::Vector3f local_78;
    p_direction[param_0->mDirType](param_0, param_1, &local_6c);

    if (local_6c.isZero()) {
        return;
    }

    local_6c.normalise();
    local_78 = param_1->mBaseAxis.cross(local_6c);

    if (local_78.isZero()) {
        return;
    }

    local_78.normalise();
    param_1->mBaseAxis = local_6c.cross(local_78);
    param_1->mBaseAxis.normalise();
    Mtx local_60;
    f32 fVar1 = param_0->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 fVar2 = param_0->mGlobalPtclScl.y * param_1->mParticleScaleY;
    local_60[0][0] = param_1->mBaseAxis.x;
    local_60[0][1] = local_6c.x;
    local_60[0][2] = local_78.x;
    local_60[0][3] = param_1->mPosition.x;
    local_60[1][0] = param_1->mBaseAxis.y;
    local_60[1][1] = local_6c.y;
    local_60[1][2] = local_78.y;
    local_60[1][3] = param_1->mPosition.y;
    local_60[2][0] = param_1->mBaseAxis.z;
    local_60[2][1] = local_6c.z;
    local_60[2][2] = local_78.z;
    local_60[2][3] = param_1->mPosition.z;
    p_plane[param_0->mPlaneType](local_60, fVar1, fVar2);
    MTXConcat(param_0->mPosCamMtx, local_60, local_60);
    GXLoadPosMtxImm(local_60, 0);
    p_prj[param_0->mPrjType](param_0, local_60);
    GXCallDisplayList(p_dl[param_0->mDLType], sizeof(jpa_dl));
}

void JPADrawRotDirection(JPAEmitterWorkData* param_0, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    f32 sinRot = nw4r::math::SinIdx((s16)param_1->mRotateAngle);
    f32 cosRot = nw4r::math::CosIdx((s16)param_1->mRotateAngle);
    EGG::Vector3f local_6c;
    EGG::Vector3f local_78;
    p_direction[param_0->mDirType](param_0, param_1, &local_6c);

    if (local_6c.isZero()) {
        return;
    }

    local_6c.normalise();
    local_78 = param_1->mBaseAxis.cross(local_6c);

    if (local_78.isZero()) {
        return;
    }

    local_78.normalise();
    param_1->mBaseAxis = local_6c.cross(local_78);
    param_1->mBaseAxis.normalise();
    f32 particleX = param_0->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 particleY = param_0->mGlobalPtclScl.y * param_1->mParticleScaleY;
    Mtx auStack_80;
    Mtx local_60;
    p_rot[param_0->mRotType](sinRot, cosRot, auStack_80);
    p_plane[param_0->mPlaneType](auStack_80, particleX, particleY);
    local_60[0][0] = param_1->mBaseAxis.x;
    local_60[0][1] = local_6c.x;
    local_60[0][2] = local_78.x;
    local_60[0][3] = param_1->mPosition.x;
    local_60[1][0] = param_1->mBaseAxis.y;
    local_60[1][1] = local_6c.y;
    local_60[1][2] = local_78.y;
    local_60[1][3] = param_1->mPosition.y;
    local_60[2][0] = param_1->mBaseAxis.z;
    local_60[2][1] = local_6c.z;
    local_60[2][2] = local_78.z;
    local_60[2][3] = param_1->mPosition.z;
    MTXConcat(local_60, auStack_80, auStack_80);
    MTXConcat(param_0->mPosCamMtx, auStack_80, local_60);
    GXLoadPosMtxImm(local_60, 0);
    p_prj[param_0->mPrjType](param_0, local_60);
    GXCallDisplayList(p_dl[param_0->mDLType], sizeof(jpa_dl));
}

void JPADrawDBillboard(JPAEmitterWorkData* param_0, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_70;
    p_direction[param_0->mDirType](param_0, param_1, &local_70);
    EGG::Vector3f aTStack_7c(param_0->mPosCamMtx[2][0], param_0->mPosCamMtx[2][1], param_0->mPosCamMtx[2][2]);
    local_70 = local_70.cross(aTStack_7c);

    if (local_70.isZero()) {
        return;
    }

    local_70.normalise();
    MTXMultVecSR(param_0->mPosCamMtx, local_70, local_70);
    EGG::Vector3f local_88;
    MTXMultVec(param_0->mPosCamMtx, param_1->mPosition, local_88);
    f32 particleX = param_0->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 particleY = param_0->mGlobalPtclScl.y * param_1->mParticleScaleY;
    Mtx local_60;
    local_60[0][0] = local_70.x * particleX;
    local_60[0][1] = -local_70.y * particleY;
    local_60[0][3] = local_88.x;
    local_60[1][0] = local_70.y * particleX;
    local_60[1][1] = local_70.x * particleY;
    local_60[1][3] = local_88.y;
    local_60[2][2] = 1.0f;
    local_60[2][3] = local_88.z;
    local_60[0][2] = local_60[1][2] = local_60[2][0] = local_60[2][1] = 0.0f;
    GXLoadPosMtxImm(local_60, 0);
    p_prj[param_0->mPrjType](param_0, local_60);
    GXCallDisplayList(jpa_dl, sizeof(jpa_dl));
}

void JPADrawRotation(JPAEmitterWorkData* param_0, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    f32 sinRot = nw4r::math::SinIdx((s16)param_1->mRotateAngle);
    f32 cosRot = nw4r::math::CosIdx((s16)param_1->mRotateAngle);
    f32 particleX = param_0->mGlobalPtclScl.x * param_1->mParticleScaleX;
    f32 particleY = param_0->mGlobalPtclScl.y * param_1->mParticleScaleY;
    Mtx auStack_88;
    p_rot[param_0->mRotType](sinRot, cosRot, auStack_88);
    p_plane[param_0->mPlaneType](auStack_88, particleX, particleY);
    auStack_88[0][3] = param_1->mPosition.x;
    auStack_88[1][3] = param_1->mPosition.y;
    auStack_88[2][3] = param_1->mPosition.z;
    MTXConcat(param_0->mPosCamMtx, auStack_88, auStack_88);
    GXLoadPosMtxImm(auStack_88, 0);
    p_prj[param_0->mPrjType](param_0, auStack_88);
    GXCallDisplayList(p_dl[param_0->mDLType], sizeof(jpa_dl));
}

void JPADrawPoint(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    if (ptcl->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXBegin(GX_POINTS, GX_VTXFMT1, 1);
    GXPosition3f32(ptcl->mPosition.x, ptcl->mPosition.y, ptcl->mPosition.z);
    GXTexCoord2f32(0.0f, 0.0f);
    GXEnd();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
}

void JPADrawLine(JPAEmitterWorkData* param_0, JPABaseParticle* param_1) {
    if (param_1->checkStatus(JPAPtclStts_Invisible)) {
        return;
    }

    EGG::Vector3f local_1c(param_1->mPosition);
    EGG::Vector3f local_28;
    param_1->getVelVec(&local_28);

    if (local_28.isZero()) {
        return;
    }

    local_28.setLength(param_0->mGlobalPtclScl.y * (25.0f * param_1->mParticleScaleY));
    local_28 = local_1c - local_28;
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXBegin(GX_LINES, GX_VTXFMT1, 2);
    GXPosition3f32(local_1c.x, local_1c.y, local_1c.z);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(local_28.x, local_28.y, local_28.z);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
}

JPANode<JPABaseParticle>* getNext(JPANode<JPABaseParticle>* param_0) {
    return param_0->getNext();
}

JPANode<JPABaseParticle>* getPrev(JPANode<JPABaseParticle>* param_0) {
    return param_0->getPrev();
}

typedef JPANode<JPABaseParticle>* (*getNodeFunc)(JPANode<JPABaseParticle>*);

void fn_8031C2C0(JPAEmitterWorkData* work) {
    work->mpRes->getEts()->fn_8031DE80(work->mpRes->getBsp(), work->mpEmtr->getAge());
}

void JPADrawStripe(JPAEmitterWorkData* param_0) {
    JPABaseShape* shape = param_0->mpRes->getBsp();
    u32 ptcl_num = param_0->mpAlivePtcl->getNum();
    if (ptcl_num < 2) {
        return;
    }

    f32 coord = 0.0f;
    f32 step = 1.0f / (ptcl_num - 1.0f);
    f32 dVar14 = (1.0f + param_0->mPivot.x) * (25.0f * param_0->mGlobalPtclScl.x);
    f32 dVar13 = (1.0f - param_0->mPivot.x) * (25.0f * param_0->mGlobalPtclScl.x);
    Mtx local_c8;
    f32 dVar11;
    f32 dVar12;
    EGG::Vector3f local_ec;
    EGG::Vector3f local_e0[2];
    EGG::Vector3f local_f8;
    EGG::Vector3f local_104;
    JPANode<JPABaseParticle>* startNode = NULL;
    getNodeFunc node_func = NULL;
    if (shape->isDrawFwdAhead()) {
        startNode = param_0->mpAlivePtcl->getLast();
        node_func = getPrev;
        coord = 1.0f;
        step = -step;
    } else {
        startNode = param_0->mpAlivePtcl->getFirst();
        node_func = getNext;
    }

    GXLoadPosMtxImm(param_0->mPosCamMtx, 0);
    p_prj[param_0->mPrjType](param_0, param_0->mPosCamMtx);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT1, ptcl_num << 1);
    for (JPANode<JPABaseParticle>* node = startNode; node != param_0->mpAlivePtcl->getEnd(); 
                                                     node = node_func(node), coord += step) {
        param_0->mpCurNode = node;
        JPABaseParticle* particle = node->getObject();
        local_ec.set(particle->mPosition);
        dVar11 = nw4r::math::SinIdx((s16)particle->mRotateAngle);
        dVar12 = nw4r::math::CosIdx((s16)particle->mRotateAngle);
        local_e0[0].set(-particle->mParticleScaleX * dVar14, 0.0f, 0.0f);
        local_e0[0].set(local_e0[0].x * dVar12, 0.0f, local_e0[0].x * dVar11);
        local_e0[1].set(particle->mParticleScaleX * dVar13, 0.0f, 0.0f);
        local_e0[1].set(local_e0[1].x * dVar12, 0.0f, local_e0[1].x * dVar11);
        p_direction[param_0->mDirType](param_0, particle, &local_f8);
        if (local_f8.isZero()) {
            local_f8.set(0.0f, 1.0f, 0.0f);
        } else {
            local_f8.normalise();
        }
        local_104 = particle->mBaseAxis.cross(local_f8);
        if (local_104.isZero()) {
            local_104.set(1.0f, 0.0f, 0.0f);
        } else {
            local_104.normalise();
        }
        particle->mBaseAxis = local_f8.cross( local_104);
        particle->mBaseAxis.normalise();
        
        local_c8[0][0] = local_104.x;
        local_c8[0][1] = local_f8.x;
        local_c8[0][2] = particle->mBaseAxis.x;
        local_c8[0][3] = 0.0f;
        local_c8[1][0] = local_104.y;
        local_c8[1][1] = local_f8.y;
        local_c8[1][2] = particle->mBaseAxis.y;
        local_c8[1][3] = 0.0f;
        local_c8[2][0] = local_104.z;
        local_c8[2][1] = local_f8.z;
        local_c8[2][2] = particle->mBaseAxis.z;
        local_c8[2][3] = 0.0f;
        MTXMultVecArraySR(local_c8, (Vec*)local_e0, (Vec*)local_e0, 2);
        GXPosition3f32(local_e0[0].x + local_ec.x, local_e0[0].y + local_ec.y,
                       local_e0[0].z + local_ec.z);
        GXTexCoord2f32(0.0f, coord);
        GXPosition3f32(local_e0[1].x + local_ec.x, local_e0[1].y + local_ec.y,
                       local_e0[1].z + local_ec.z);
        GXTexCoord2f32(1.0f, coord);
    }
    GXEnd();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
}

void JPADrawStripeX(JPAEmitterWorkData* param_0) {
    JPABaseShape* shape = param_0->mpRes->getBsp();
    u32 ptcl_num = param_0->mpAlivePtcl->getNum();
    if (ptcl_num < 2) {
        return;
    }

    f32 start_coord = 0.0f;
    f32 coord = 0.0f;
    f32 step = 1.0f / (ptcl_num - 1.0f);
    f32 local_154 = (1.0f + param_0->mPivot.x) * (25.0f * param_0->mGlobalPtclScl.x);
    f32 local_158 = (1.0f - param_0->mPivot.x) * (25.0f * param_0->mGlobalPtclScl.x);
    f32 local_15c = (1.0f + param_0->mPivot.y) * (25.0f * param_0->mGlobalPtclScl.y);
    f32 local_160 = (1.0f - param_0->mPivot.y) * (25.0f * param_0->mGlobalPtclScl.y);
    Mtx local_90;
    f32 dVar11;
    f32 dVar12;
    EGG::Vector3f local_b4;
    EGG::Vector3f local_a8[2];
    EGG::Vector3f local_c0;
    EGG::Vector3f local_cc;
    JPANode<JPABaseParticle>* startNode = NULL;
    getNodeFunc node_func = NULL;
    if (shape->isDrawFwdAhead()) {
        startNode = param_0->mpAlivePtcl->getLast();
        node_func = getPrev;
        start_coord = coord = 1.0f;
        step = -step;
    } else {
        startNode = param_0->mpAlivePtcl->getFirst();
        node_func = getNext;
    }

    GXLoadPosMtxImm(param_0->mPosCamMtx, 0);
    p_prj[param_0->mPrjType](param_0, param_0->mPosCamMtx);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT1, ptcl_num << 1);
    for (JPANode<JPABaseParticle>* node = startNode; node != param_0->mpAlivePtcl->getEnd(); 
                                                     node = node_func(node), coord += step) {
        param_0->mpCurNode = node;
        JPABaseParticle* particle = node->getObject();
        local_b4.set(particle->mPosition);
        dVar11 = nw4r::math::SinIdx((s16)particle->mRotateAngle);
        dVar12 = nw4r::math::CosIdx((s16)particle->mRotateAngle);
        local_a8[0].set(-particle->mParticleScaleX * local_154, 0.0f, 0.0f);
        local_a8[0].set(local_a8[0].x * dVar12, 0.0f, local_a8[0].x * dVar11);
        local_a8[1].set(particle->mParticleScaleX * local_158, 0.0f, 0.0f);
        local_a8[1].set(local_a8[1].x * dVar12, 0.0f, local_a8[1].x * dVar11);
        p_direction[param_0->mDirType](param_0, particle, &local_c0);
        if (local_c0.isZero()) {
            local_c0.set(0.0f, 1.0f, 0.0f);
        } else {
            local_c0.normalise();
        }
        local_cc = particle->mBaseAxis.cross(local_c0);
        if (local_cc.isZero()) {
            local_cc.set(1.0f, 0.0f, 0.0f);
        } else {
            local_cc.normalise();
        }
        particle->mBaseAxis = local_c0.cross( local_cc);
        particle->mBaseAxis.normalise();
        
        local_90[0][0] = local_cc.x;
        local_90[0][1] = local_c0.x;
        local_90[0][2] = particle->mBaseAxis.x;
        local_90[0][3] = 0.0f;
        local_90[1][0] = local_cc.y;
        local_90[1][1] = local_c0.y;
        local_90[1][2] = particle->mBaseAxis.y;
        local_90[1][3] = 0.0f;
        local_90[2][0] = local_cc.z;
        local_90[2][1] = local_c0.z;
        local_90[2][2] = particle->mBaseAxis.z;
        local_90[2][3] = 0.0f;
        MTXMultVecArraySR(local_90, (Vec*)local_a8, (Vec*)local_a8, 2);
        GXPosition3f32(local_a8[0].x + local_b4.x, local_a8[0].y + local_b4.y,
                       local_a8[0].z + local_b4.z);
        GXTexCoord2f32(0.0f, coord);
        GXPosition3f32(local_a8[1].x + local_b4.x, local_a8[1].y + local_b4.y,
                       local_a8[1].z + local_b4.z);
        GXTexCoord2f32(1.0f, coord);
    }
    GXEnd();

    coord = start_coord;
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT1, ptcl_num << 1);
    for (JPANode<JPABaseParticle>* node = startNode; node != param_0->mpAlivePtcl->getEnd(); 
                                                     node = node_func(node), coord += step) {
        param_0->mpCurNode = node;
        JPABaseParticle* particle = node->getObject();
        local_b4.set(particle->mPosition);
        dVar11 = nw4r::math::CosIdx((s16)particle->mRotateAngle);
        dVar12 = -nw4r::math::SinIdx((s16)particle->mRotateAngle);
        local_a8[0].set(-particle->mParticleScaleY * local_15c, 0.0f, 0.0f);
        local_a8[0].set(local_a8[0].x * dVar12, 0.0f, local_a8[0].x * dVar11);
        local_a8[1].set(particle->mParticleScaleY * local_160, 0.0f, 0.0f);
        local_a8[1].set(local_a8[1].x * dVar12, 0.0f, local_a8[1].x * dVar11);
        p_direction[param_0->mDirType](param_0, particle, &local_c0);
        if (local_c0.isZero()) {
            local_c0.set(0.0f, 1.0f, 0.0f);
        } else {
            local_c0.normalise();
        }
        local_cc = particle->mBaseAxis.cross(local_c0);
        if (local_cc.isZero()) {
            local_cc.set(1.0f, 0.0f, 0.0f);
        } else {
            local_cc.normalise();
        }
        particle->mBaseAxis = local_c0.cross( local_cc);
        particle->mBaseAxis.normalise();
        
        local_90[0][0] = local_cc.x;
        local_90[0][1] = local_c0.x;
        local_90[0][2] = particle->mBaseAxis.x;
        local_90[0][3] = 0.0f;
        local_90[1][0] = local_cc.y;
        local_90[1][1] = local_c0.y;
        local_90[1][2] = particle->mBaseAxis.y;
        local_90[1][3] = 0.0f;
        local_90[2][0] = local_cc.z;
        local_90[2][1] = local_c0.z;
        local_90[2][2] = particle->mBaseAxis.z;
        local_90[2][3] = 0.0f;
        MTXMultVecArraySR(local_90, (Vec*)local_a8, (Vec*)local_a8, 2);
        GXPosition3f32(local_a8[0].x + local_b4.x, local_a8[0].y + local_b4.y,
                       local_a8[0].z + local_b4.z);
        GXTexCoord2f32(0.0f, coord);
        GXPosition3f32(local_a8[1].x + local_b4.x, local_a8[1].y + local_b4.y,
                       local_a8[1].z + local_b4.z);
        GXTexCoord2f32(1.0f, coord);
    }
    GXEnd();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
}

void JPADrawEmitterCallBackB(JPAEmitterWorkData* work) {
    JPABaseEmitter* emtr = work->mpEmtr;
    if (emtr->mpEmtrCallBack == NULL) {
        return;
    }

    emtr->mpEmtrCallBack->draw(emtr);
}

void JPADrawParticleCallBack(JPAEmitterWorkData* work, JPABaseParticle* ptcl) {
    JPABaseEmitter* emtr = work->mpEmtr;
    if (emtr->mpPtclCallBack == NULL) {
        return;
    }

    emtr->mpPtclCallBack->draw(emtr, ptcl);
}

static void makeColorTable(GXColor** o_color_table, JPAClrAnmKeyData const* i_data, u8 param_2,
                           s16 i_size, EGG::Heap* i_heap) {
    // The TP code didn't match, the MKDD version helps here
    void* p_clr_tbl = i_heap->alloc((i_size + 1) * 4, 4);
#define color_table ((GXColor *)p_clr_tbl)
    f32 r_step, g_step, b_step, a_step;
    r_step = g_step = b_step = a_step = 0.0f;

    f32 diff_r, diff_g, diff_b, diff_a;
    f32 r, g, b, a;
    diff_r = r = i_data[0].color.r;
    diff_g = g = i_data[0].color.g;
    diff_b = b = i_data[0].color.b;
    diff_a = a = i_data[0].color.a;
    f32 base_step = 0.0f;
    int j = 0;
    for (s16 i = 0; i < i_size + 1; i++) {
        if (i == i_data[j].index) {
            color_table[i] = i_data[j].color;
            r = i_data[j].color.r;
            g = i_data[j].color.g;
            b = i_data[j].color.b;
            a = i_data[j].color.a;
            j++;
            if (j < param_2) {
                diff_r = i_data[j].color.r;
                diff_g = i_data[j].color.g;
                diff_b = i_data[j].color.b;
                diff_a = i_data[j].color.a;
                base_step = 1.0f / (i_data[j].index - i_data[j - 1].index);

                r_step = base_step * (diff_r - r);
                g_step = base_step * (diff_g - g);
                b_step = base_step * (diff_b - b);
                a_step = base_step * (diff_a - a);
            } else {
                r_step = g_step = b_step = a_step = 0.0f;
            }
        } else {
            r += r_step;
            color_table[i].r = r;
            g += g_step;
            color_table[i].g = g;
            b += b_step;
            color_table[i].b = b;
            a += a_step;
            color_table[i].a = a;
        }
    }
    *o_color_table = color_table;
}

GXBlendMode JPABaseShape::st_bm[4] = {
    GX_BM_NONE,
    GX_BM_BLEND,
    GX_BM_LOGIC,
    GX_BM_SUBTRACT,
};

GXBlendFactor JPABaseShape::st_bf[10] = {
    GX_BL_ZERO,      GX_BL_ONE,           GX_BL_SRCCLR, GX_BL_INVSRCCLR,
    GX_BL_DSTCLR, GX_BL_INVDSTCLR, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
    GX_BL_DSTALPHA, GX_BL_INVDSTALPHA,
};

GXLogicOp JPABaseShape::st_lo[16] = {
    GX_LO_CLEAR,   GX_LO_SET,     GX_LO_COPY,   GX_LO_INVCOPY, GX_LO_NOOP, GX_LO_INV,
    GX_LO_AND,     GX_LO_NAND,    GX_LO_OR,     GX_LO_NOR,      GX_LO_XOR,  GX_LO_EQUIV,
    GX_LO_REVAND, GX_LO_INVAND, GX_LO_REVOR, GX_LO_INVOR,
};

GXCompare JPABaseShape::st_c[8] = {
    GX_NEVER, GX_LESS, GX_LEQUAL, GX_EQUAL, GX_NEQUAL, GX_GEQUAL, GX_GREATER, GX_ALWAYS,
};

GXAlphaOp JPABaseShape::st_ao[4] = {
    GX_AOP_AND,
    GX_AOP_OR,
    GX_AOP_XOR,
    GX_AOP_XNOR,
};

GXTevColorArg JPABaseShape::st_ca[6][4] = {
    {
        GX_CC_ZERO,
        GX_CC_TEXC,
        GX_CC_ONE,
        GX_CC_ZERO,
    },
    {
        GX_CC_ZERO,
        GX_CC_C0,
        GX_CC_TEXC,
        GX_CC_ZERO,
    },
    {
        GX_CC_C0,
        GX_CC_ONE,
        GX_CC_TEXC,
        GX_CC_ZERO,
    },
    {
        GX_CC_C1,
        GX_CC_C0,
        GX_CC_TEXC,
        GX_CC_ZERO,
    },
    {
        GX_CC_ZERO,
        GX_CC_TEXC,
        GX_CC_C0,
        GX_CC_C1,
    },
    {
        GX_CC_ZERO,
        GX_CC_ZERO,
        GX_CC_ZERO,
        GX_CC_C0,
    },
};

JPABaseShapeAlphaArg JPABaseShape::st_aa[5] = {
    {
        GX_CA_ZERO,
        GX_CA_TEXA,
        GX_CA_A0,
        GX_CA_ZERO,
        GX_TEV_ADD,
        GX_CS_SCALE_1,
    },
    {
        GX_CA_ZERO,
        GX_CA_ZERO,
        GX_CA_ZERO,
        GX_CA_A0,
        GX_TEV_ADD,
        GX_CS_SCALE_1,
    },
    {
        GX_CA_A0,
        GX_CA_ZERO,
        GX_CA_ZERO,
        GX_CA_TEXA,
        GX_TEV_SUB,
        GX_CS_SCALE_1,
    },
    {
        GX_CA_A0,
        GX_CA_ZERO,
        GX_CA_ZERO,
        GX_CA_TEXA,
        GX_TEV_SUB,
        GX_CS_SCALE_2,
    },
    {
        GX_CA_ZERO,
        GX_CA_TEXA,
        GX_CA_A0,
        GX_CA_ZERO,
        GX_TEV_ADD,
        GX_CS_SCALE_2,
    },
};
JPABaseShape::JPABaseShape(u8 const* pData, EGG::Heap* pHeap) {
    pBsd = (const JPABaseShapeData*)pData;

    if (isTexCrdAnm()) {
        mpTexCrdMtxAnmTbl = (const void*)(pData + sizeof(JPABaseShapeData));
    } else {
        mpTexCrdMtxAnmTbl = NULL;
    }

    if (isTexAnm()) {
        JUT_ASSERT(1698, pBsd->texAnmKeyNum != 0);
        u32 offs = sizeof(JPABaseShapeData);
        if (isTexCrdAnm()) {
            offs += 0x28;
        }
        mpTexIdxAnimTbl = (const u8*)(pData + offs);
    } else {
        mpTexIdxAnimTbl = NULL;
    }

    if (isPrmAnm()) {
        JUT_ASSERT(1707, pBsd->prmAnmKeyNum != 0);
        JPAClrAnmKeyData* anmKeyData = (JPAClrAnmKeyData*)(pData + pBsd->mClrPrmAnmOffset);
        makeColorTable(&mpPrmClrAnmTbl, anmKeyData,
                       pBsd->prmAnmKeyNum, pBsd->mClrAnmFrmMax, pHeap);
    } else {
        mpPrmClrAnmTbl = NULL;
    }

    if (isEnvAnm()) {
        JUT_ASSERT(1716, pBsd->envAnmKeyNum != 0);
        JPAClrAnmKeyData* anmKeyData = (JPAClrAnmKeyData*)(pData + pBsd->mClrEnvAnmOffset);
        makeColorTable(&mpEnvClrAnmTbl, anmKeyData,
                       pBsd->envAnmKeyNum, pBsd->mClrAnmFrmMax, pHeap);
    } else {
        mpEnvClrAnmTbl = NULL;
    }
}

void JPABaseShape::setGX(JPAEmitterWorkData* work) const {
    const GXTevColorArg* colorArg = getTevColorArg();
    const JPABaseShapeAlphaArg* alphaArg = getTevAlphaArg();
    GXSetBlendMode(getBlendMode(), getBlendSrc(), getBlendDst(), getLogicOp());
    GXSetZMode(getZEnable(), getZCmp(), getZUpd());
    GXSetAlphaCompare(getAlphaCmp0(), getAlphaRef0(), getAlphaOp(), getAlphaCmp1(), getAlphaRef1());
    GXSetTevColorIn(GX_TEVSTAGE0, colorArg[0], colorArg[1], colorArg[2], colorArg[3]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, alphaArg->mArg[0], alphaArg->mArg[1], alphaArg->mArg[2], alphaArg->mArg[3]);
    GXSetTevAlphaOp(GX_TEVSTAGE0, alphaArg->mOp, GX_TB_ZERO, alphaArg->mScale, true, GX_TEVPREV);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetZCompLoc(getZCompLoc());
}
