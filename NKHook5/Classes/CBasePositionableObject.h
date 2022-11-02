#ifndef NKHOOK5_CLASSES_CBASEPOSITIONABLEOBJECT
#define NKHOOK5_CLASSES_CBASEPOSITIONABLEOBJECT

#include "../../Util/NewFramework.h"
#include "Macro.h"
#include "Matrix16F.h"
#include "Vec2F.h"
#include "Vec3F.h"
#include "Color.h"
#include <ghstl/string>
#include <ghstl/list>

namespace NKHook5
{
    namespace Classes
    {
        using namespace Signatures;

        class CBasePositionableObject
        {
        public:
            /* Somehow prevented some heap corruption bug... */
            overload_new

        public:
            char pad_0000[16]; //0x0000
            CBasePositionableObject* parent; //0x0010
            nfw::list<CBasePositionableObject*> children; //0x0014
            Vec2F size; //0x0020
            Vec2F sizeHalf; //0x0028
            char pad_0030[8]; //0x0030
            Matrix16F spriteMatrix; //0x0038
            bool complete; //0x0078
            bool incompleteChildren; //0x0079
            char pad_007A[2]; //0x007A
            Vec2F alignment; //0x007C
            char pad_0084[12]; //0x0084
            Vec3F location; //0x0090
            float rotAngle; //0x009C
            Vec2F scale; //0x00A0
        public:
            CBasePositionableObject() {}

            void AssignParent(CBasePositionableObject* parent) {
                return ThisCall<void, CBasePositionableObject*, CBasePositionableObject*>(Sigs::CBasePositionableObject_AssignParent, this, parent);
            }
            void SetComplete() {
                return ThisCall<void, CBasePositionableObject*>(Signatures::Sigs::CBasePositionableObject_SetComplete, this);
            }

            virtual ~CBasePositionableObject() {}

            virtual void Render(bool animate) {}
            virtual void Update(class SGameTime* pSGameTime) {}
            virtual void UpdateRecursive(class SGameTime* param_1) {}
            virtual bool HitTest(Vec2F location, float param_2) { return false;  }
            virtual void AddChild(CBasePositionableObject* child) {}
            virtual void AddChildAndUpdate(class CBasePositionableObject* param_1, int* param_2) {}
            virtual void FUN_009e6dc0(int* param_1, int** param_2) {}
            virtual void DeleteChildren() {}
            virtual void SetXYZ(Vec3F location) {}
            virtual void SetXY(Vec2F location) {}
            virtual void SetXY_1(Vec2F location) {}
            virtual void SetX(float x) {}
            virtual void SetY(float y) {}
            virtual void SetZ(float z) {}
            virtual void MoveXYZ(Vec3F location) {}
            virtual void MoveXY(Vec2F location) {}
            virtual void MoveX(float x) {}
            virtual void MoveY(float y) {}
            virtual void MoveZ(float z) {}
            virtual void Scale(Vec2F scale) {}
            virtual void ScaleXY(Vec2F scale) {}
            virtual void ScaleX(float x) {}
            virtual void ScaleY(float y) {}
            virtual void SetRotation(float angle) {}
            virtual void SetSize(Vec2F size) {}
            virtual void SetSizeX(float x) {}
            virtual void SetSizeY(float y) {}
            virtual void SetAlignX(float x) {}
            virtual void SetAlignY(float param_1) {}
            virtual void SetAlignXY(Vec2F alignment) {}
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
        }; // Size 1024 (0x400)

        static_assert(sizeof(CBasePositionableObject) == 0xA8);
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_CBASEPOSITIONABLEOBJECT */
