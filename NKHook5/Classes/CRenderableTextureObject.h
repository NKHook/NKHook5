#pragma once

#include "CBasePositionableObject.h"

namespace NKHook5
{
    namespace Classes
    {
        class CRenderableTextureObject : public CBasePositionableObject
        {
            char pad_00AC[28]; //0x00AC
        public:
            CRenderableTextureObject() {};

            virtual ~CRenderableTextureObject() {}

            virtual void FUN_0069f510() {}
            virtual void FUN_0069f570() {}
            virtual void FUN_0069f5d0() {}
            virtual void FUN_0069f630() {}
            virtual void FUN_0069f690() {}
            virtual void FUN_0069f770() {}
            virtual void SetShader(int shaderId) {}
            virtual void SetTexture(class CTexture* pCTexture) {}
        };
    } // namespace Classes
    
} // namespace NKHook5
