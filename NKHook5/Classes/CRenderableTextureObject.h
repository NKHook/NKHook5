#pragma once

#include "CBasePositionableObject.h"

namespace NKHook5
{
    namespace Classes
    {
        class CRenderableTextureObject : public CBasePositionableObject
        {
            char pad_00A8[32]; //0x00A8
        public:
            CRenderableTextureObject() {};

            virtual ~CRenderableTextureObject() {}
            virtual void Render(bool animate) {}
            virtual void Update(class SGameTime* pSGameTime) {}
            virtual void UpdateRecursive(class SGameTime* param_1) {}
            virtual void FUN_00646120(int param_2, int param_3) {}
            virtual void AddChild(class CBasePositionableObject* param_1) {}
            virtual void AddChildAndUpdate(class CBasePositionableObject* param_1, int* param_2) {}
            virtual void FUN_009e6dc0(int* param_1, int** param_2) {}
            virtual void FUN_009e6d60() {}
            virtual void SetXYZ(class Vec3F* location) {}
            virtual void SetXY(class Vec2F* location) {}
            virtual void SetXY_1(class Vec2F* location) {}
            virtual void SetX(float x) {}
            virtual void SetY(float y) {}
            virtual void SetZ(float z) {}
            virtual void MoveXYZ(class Vec3F* location) {}
            virtual void MoveXY(class Vec2F* location) {}
            virtual void MoveX(float x) {}
            virtual void MoveY(float y) {}
            virtual void MoveZ(float z) {}
            virtual void Scale(class Vec2F* scale) {}
            virtual void ScaleXY(class Vec2F* scale) {}
            virtual void ScaleX(float x) {}
            virtual void ScaleY(float y) {}
            virtual void SetRotation(float angle) {}
            virtual void SetSize(class Vec2F* size) {}
            virtual void SetSizeX(float x) {}
            virtual void SetSizeY(float y) {}
            virtual void SetAlignX(float alignX) {}
            virtual void SetAlignY(float alignY) {}
            virtual void SetAlignXY(class Vec2F* alignment) {}
            virtual class Vec3F* GetLocation(class Vec3F* location) { return nullptr; }
            virtual float* GetLocationX() { return nullptr; }
            virtual float* GetLocationX_1() { return nullptr; }
            virtual float* GetLocationY() { return nullptr; }
            virtual float* GetLocationZ() { return nullptr; }
            virtual class Vec2F* GetScale(class Vec2F* scale) { return nullptr; }
            virtual float GetScaleX() { return 0.0f; }
            virtual float GetScaleY() { return 0.0f; }
            virtual void ResetMatrix() {}
            virtual void UpdateMatrix(bool param_1) {}
            virtual void UpdateMatrixRecursive() {}
            virtual void ForceUpdate() {}
            virtual void SetTransitionAnim(float time, bool unused) {}
            virtual void FUN_009e69d0() {}
            virtual void ForceUpdate_1() {}
            virtual void DrawChildren() {}
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
