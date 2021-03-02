#ifndef NKHOOK5_CLASSES_CBASEPOSITIONABLEOBJECT
#define NKHOOK5_CLASSES_CBASEPOSITIONABLEOBJECT

#include "Matrix16F.h"
#include "Vec2F.h"
#include "Vec3F.h"
#include "Color.h"

namespace NKHook5
{
    namespace Classes
    {
        class CBasePositionableObject
        {
            char pad_0000[56]; //0x0000
            Matrix16F SpriteMatrix; //0x0038
            char pad_0078[24]; //0x0078
            Vec3F Position; //0x0090
            float Angle; //0x009C
            Vec2F Scale; //0x00A0
            char pad_00A8[96]; //0x00A8
            Color Color; //0x0108
            char pad_0114[760]; //0x0114
        public:
            virtual void* FUN_006607b0() {} //0
            virtual void* FUN_0056e460() {} //1
            virtual void* FUN_00618e30() {} //2
            virtual void* FUN_005f9ad0(float param_2, float param_3) {} //3
            virtual void* FUN_005f9b30(float param_2) {} //4
            virtual void* FUN_005f9c10() {} //5
            virtual void AddXYZ(float x, float y, float z) {} //6
            virtual void AddX(float x) {} //7
            virtual void AddZ(float z) {} //8
            virtual void SetScale(float scaleX, float scaleY) {} //9
            virtual void SetScaleY(float scaleY) {} //10
            virtual void FUN_005f9fb0(float param_2, float param_3) {} //11
            virtual void FUN_005fa030(float param_2) {} //12
            virtual void FUN_005fa080(float param_2) {} //13
            virtual void GetXYZ(class Vec3F* vector) {} //14
            virtual float* GetX() {} //15
            virtual float* GetZ() {} //16
            virtual float FUN_005fa140() {} //17
            virtual void ScaleMatrix() {} //18
            virtual void* FUN_00940990() {} //19
            virtual void FUN_00940960(float param_2, char param_3) {} //20
            virtual void* _guard_check_icall() {} //21
        }; // Size 1024 (0x400)
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_CBASEPOSITIONABLEOBJECT */
