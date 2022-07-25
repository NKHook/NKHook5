#pragma once

#include "Macro.h"
#include "CRenderableTextureObject.h"
#include "CFont.h"
#include "boost/shared_ptr"
#include "Vec2F.h"

namespace NKHook5
{
    namespace Signatures {
        namespace CTextObject {
            static const char* SIG_CCTOR_A = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 51 56 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 ?? 75 ?? E8 ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? 8D";
            static const char* SIG_CCTOR_B = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B D9 ?? 5D ?? 8B ?? ?? 8B ?? ?? ?? 5D ?? ?? 45 ?? E8";
            static const char* SIG_CCTOR_C = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B D9 ?? 5D ?? ?? 5D ?? 8B";
        }
    };

    namespace Classes
    {
        class CTextObject : public CRenderableTextureObject
        {
        public:
            ghstl::string text; //0x00C8
            char pad_00E0[80]; //0x00E0
            int32_t unknownRenderRuleSetZero; //0x0130
            char pad_0134[52]; //0x0134
        public:
            CTextObject() {
                ThisCall<CTextObject*, CTextObject*>(Signatures::CTextObject::SIG_CCTOR_A, this);
            }
            CTextObject(Vec2F* position, boost::shared_ptr<CFont>* font, ghstl::string* text) {
                ThisCall<CTextObject*, CTextObject*, Vec2F*, boost::shared_ptr<CFont>*, ghstl::string*>(Signatures::CTextObject::SIG_CCTOR_B, this, position, font, text);
            }
            CTextObject(boost::shared_ptr<CFont>* font, ghstl::string* text) {
                ThisCall<CTextObject*, CTextObject*, boost::shared_ptr<CFont>*, ghstl::string*>(Signatures::CTextObject::SIG_CCTOR_C, this, font, text);
            }

            virtual ~CTextObject() {}
            virtual void Draw(bool param_1) {}
            virtual void Update(class SGameTime* pSGameTime) {}
            virtual void UpdateRecursive(class SGameTime* param_1) {}
            virtual void* FUN_00646120(uint32_t param_2, uint32_t param_3) { return nullptr; }
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
            virtual void SetAlignX(float x) {}
            virtual void SetAlignY(float x) {}
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
            virtual void* FUN_006a8100() { return nullptr; }
            virtual void* FUN_006a8160() { return nullptr; }
            virtual void* FUN_006a81c0() { return nullptr; }
            virtual void* FUN_006a8220() { return nullptr; }
            virtual void* FUN_006a8280() { return nullptr; }
            virtual void* FUN_006a82c0() { return nullptr; }
            virtual void SetShader(uint32_t shaderId) {}
            virtual void SetTexture(class CTexture* pCTexture) {}
            virtual void SetAlpha(float alpha) {}
            virtual void SetColor(class Vec4F* color, int param_2) {}
            virtual void MixWithColor(class Vec4F* color) {}
            virtual void* FUN_009ad610(uint32_t param_2) { return nullptr; }
            virtual void SetGradient(class Vec4F* firstColor, class Vec4F* secondColor, int param_3) {}
            virtual void SetString(ghstl::string* text) {}
            virtual void* FUN_009abb80() { return nullptr; }
            virtual int CountLines() { return 0; }
            virtual float GetLineWidth(uint32_t param_1) { return 0.0f; }
        };
    } // namespace Classes

} // namespace NKHook5