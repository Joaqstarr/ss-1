#include "JSystem/JParticle/JPATexture.h"

JPATexture::JPATexture(u8 const* pData) {
    mpData = (const JPATextureData*)pData;
    mTexture.store(&mpData->mResTIMG);
}

JPATexture::~JPATexture() {}
