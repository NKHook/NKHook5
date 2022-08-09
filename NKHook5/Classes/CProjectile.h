#pragma once

#include "CWeaponTask.h"
#include "CBasePositionableObject.h"
#include <stdint.h>

namespace NKHook5 {
	namespace Classes {
		enum DrawLayer {
			ABOVE_TOWERS,
			BELOW_TOWERS
		};

		enum CollisionType {
			NONE,
			ONCE,
			CONTINUAL
		};

#pragma pack(push, 1)
#pragma pack(show)
		class CProjectile : public CWeaponTask, public CBasePositionableObject {
		public:
			char pad_00A8[44]; //0x00A8
			DrawLayer N0000147B; //0x00D4
			char pad_00D8[84]; //0x00D8
			float angleIncrement; //0x012C
			char pad_0130[60]; //0x0130
			CollisionType collisionType; //0x016C
			bool ignoreStatusEffect; //0x0170
			char pad_0171[3]; //0x0171
			bool terminateOnZeroPersists; //0x0174
			bool removeOnRoundEnd; //0x0175
			bool growsOnRoundEnd; //0x0176
			bool terminateOnTowerRemoved; //0x0177
			bool onlyFireTerminateTasksOnZeroPersists; //0x0178
			char pad_0179[3]; //0x0179
			int32_t amountToGrow; //0x017C
			int32_t maxGrowth; //0x0180
			float radius; //0x0184
			bool noSpread; //0x0188
			char pad_0189[3]; //0x0189
			float spreadAngle; //0x018C
			float spinRate; //0x0190
			bool hasLimitedDuration; //0x0194
			bool hasRandomOrientation; //0x0195
			char pad_0196[2]; //0x0196
			bool limitedDuration; //0x0198
			char pad_0199[3]; //0x0199
			float N000014AD; //0x019C
			bool hasFixedAngle; //0x01A0
			char pad_01A1[27]; //0x01A1
			bool forcePersists; //0x01BC
			bool collidesOnlyWithTarget; //0x01BD
			bool onlyCollidePastCutOff; //0x01BE
			char pad_01BF[1]; //0x01BF
			bool loopAnimation; //0x01C0
			char pad_01C1[15]; //0x01C1
		public:
			/* Virtual destructor */
			virtual ~CProjectile() {};

			/* CBasePositionableObject VT funcs */
			virtual void Render(bool animate) {}
			virtual void Update(class SGameTime* pSGameTime) {}
			virtual void UpdateRecursive(class SGameTime* param_1) {}
			virtual bool HitTest(Vec2F location, float param_2) { return false; }
			virtual void AddChild(class CBasePositionableObject* param_1) {}
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

			/* CProjectile VT funcs */
			virtual CProjectile* Clone() { return nullptr; };
			virtual void* FUN_006ffed0(uint32_t param_2) { return nullptr; };
			virtual void* FUN_006fff50() { return nullptr; };
			virtual void* FUN_007096b0(uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5) { return nullptr; };
			virtual void FUN_OPTIMIZEDOUT(class SGameTime* pSGameTime) {};
			virtual void Kill() {};
		};
#pragma pack(pop, 1)

		static_assert(offsetof(CProjectile, pad_00A8) == 0xA8);
		static_assert(sizeof(CProjectile) == 0x1D0);
	}
}