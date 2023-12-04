#pragma once

#include "../../Util/NewFramework.h"
#include "Macro.h"
#include "Matrix16F.h"
#include "Vec2F.h"
#include "Vec3F.h"
#include "CBloonEscapedEvent.h"
#include "CObserver.h"
#include "Color.h"
#include "CTowerRemovedEvent.h"

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/list_hook.hpp>

namespace NKHook5::Classes
{
	using namespace Signatures;

	namespace _BasePositionableObjectDetail
	{
		struct SBasePositionableObjectListTag
		{
		};
	}

	using base_tag = boost::intrusive::tag<_BasePositionableObjectDetail::SBasePositionableObjectListTag>;
	using member_tag = boost::intrusive::tag<_BasePositionableObjectDetail::SBasePositionableObjectListTag>;
	using link_mode = boost::intrusive::link_mode<boost::intrusive::link_mode_type::auto_unlink>;

	class CBasePositionableObject
		: public boost::intrusive::list_base_hook<base_tag, link_mode, void>
	{
	public:
		/* Somehow prevented some heap corruption bug... */
		overload_allocators

	public:
		bool visible = false;
		CBasePositionableObject* parent = nullptr;
		boost::intrusive::list_member_hook<member_tag, link_mode, void> children;
		char pad_001C[4]{};
		Vec2F size; //0x0020
		Vec2F sizeHalf; //0x0028
		char pad_0030[8]{}; //0x0030
		Matrix16F transform{}; //0x0038
		bool complete{}; //0x0078
		bool incompleteChildren{}; //0x0079
		char pad_007A[2]{}; //0x007A
		Vec2F alignment; //0x007C
		char pad_0084[12]{}; //0x0084
		Vec3F location{}; //0x0090
		float rotAngle{}; //0x009C
		Vec2F scale; //0x00A0
	public:
		CBasePositionableObject() = default;

		void AssignParent(CBasePositionableObject* parent) {
			return ThisCall<void, CBasePositionableObject*, CBasePositionableObject*>(Sigs::CBasePositionableObject_AssignParent, this, parent);
		}
		void SetComplete() {
			return ThisCall<void, CBasePositionableObject*>(Signatures::Sigs::CBasePositionableObject_SetComplete, this);
		}

		virtual ~CBasePositionableObject() = default;

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
		virtual void SetAlignY(float y) {}
		virtual void SetAlignXY(Vec2F alignment) {}
		virtual const class Vec3F& GetLocation(class Vec3F& location) const { return location; };
		virtual const class Vec3F& GetLocation() const { Vec3F a; return a; };
		virtual const float& GetLocationX() const { float a; return a; };
		virtual const float& GetLocationY() const { float a; return a; };
		virtual const float& GetLocationZ() const { float a; return a; };
		virtual const class Vec2F& GetScale(class Vec2F& scale) const { return scale; }
		virtual float GetScaleX() { return 0.0f; }
		virtual float GetScaleY() { return 0.0f; }
		virtual void ResetMatrix() {}
		virtual void UpdateMatrix(bool param_1) {}
		virtual void UpdateMatrixRecursive() {}
		virtual void ForceUpdate() {}
		virtual void SetTransitionAnim(float time, bool permitNegative) {}
		virtual void ResetDirtyFlag() {}
		virtual void DeleteChildren_2() {}
		virtual void DrawChildren() {}
	};

	static_assert(sizeof(CBasePositionableObject) == 0xA8);
	static_assert(offsetof(CBasePositionableObject, visible) == 0xC);
	static_assert(offsetof(CBasePositionableObject, size) == 0x20);
	static_assert(offsetof(CBasePositionableObject, location) == 0x90);
} // namespace NKHook5::Classes