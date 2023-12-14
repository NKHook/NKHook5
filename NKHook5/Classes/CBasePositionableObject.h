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

	class CBasePositionableObject;
	namespace _BasePositionableObjectDetail
	{
		struct SBasePositionableObjectListTag
		{
		};
	}

	using base_tag = boost::intrusive::tag<_BasePositionableObjectDetail::SBasePositionableObjectListTag>;
	using base_link_mode = boost::intrusive::link_mode<boost::intrusive::link_mode_type::auto_unlink>;
	using member_link_mode = boost::intrusive::link_mode<boost::intrusive::link_mode_type::safe_link>;
	using container_ptr = void;
	using member_hook = boost::intrusive::list_member_hook<member_link_mode, container_ptr>;

	class CBasePositionableObject
		: public boost::intrusive::list_base_hook<base_tag, base_link_mode, container_ptr>
	{
	public:
		/* Somehow prevented some heap corruption bug... */
		overload_allocators

	public:
		bool mVisible = false;
		CBasePositionableObject* mParent = nullptr;
		member_hook mChildren;
		char pad_001C[4]{};
		Vec2F mSize; //0x0020
		Vec2F mSizeHalf; //0x0028
		char pad_0030[8]{}; //0x0030
		Matrix16F mTransform{}; //0x0038
		bool mDirty{}; //0x0078
		bool mDefaultDirtyState{}; //0x0079
		char pad_007A[2]{}; //0x007A
		Vec2F mAlignment; //0x007C
		char pad_0084[12]{}; //0x0084
		Vec3F mLocation{}; //0x0090 //1266DC98
		float mRotAngle{}; //0x009C
		Vec2F mScale; //0x00A0
	public:
		CBasePositionableObject() = default;

		void AssignParent(CBasePositionableObject* parent);
		void RemoveParent();
		void AppendChild(CBasePositionableObject* child);
		void MakeDirty();

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
		[[nodiscard]] virtual const class Vec3F& GetLocation() const { return this->mLocation; };
		[[nodiscard]] virtual const float& GetLocationX() const { return this->mLocation.x; };
		[[nodiscard]] virtual const float& GetLocationY() const { return this->mLocation.y; };
		[[nodiscard]] virtual const float& GetLocationZ() const { return this->mLocation.z; };
		virtual const class Vec2F& GetScale(class Vec2F& scale) const { return scale; }
		virtual float GetScaleX() { return 0.0f; }
		virtual float GetScaleY() { return 0.0f; }
		virtual void ResetMatrix() {}
		virtual void UpdateMatrix(bool param_1) {}
		virtual void UpdateMatrixRecursive() {}
		virtual void ForceUpdate() {}
		virtual void SetTransitionAnim(float time, bool permitNegative) {}
		virtual void SetDefaultDirtyState(bool) {}
		virtual void DeleteChildren_2() {}
		virtual void DrawChildren() {}
	};

	using member_list = boost::intrusive::list<CBasePositionableObject, boost::intrusive::member_hook<CBasePositionableObject, member_hook, &CBasePositionableObject::mChildren>>;

	static_assert(sizeof(CBasePositionableObject) == 0xA8);
	static_assert(offsetof(CBasePositionableObject, mVisible) == 0xC);
	static_assert(offsetof(CBasePositionableObject, mSize) == 0x20);
	static_assert(offsetof(CBasePositionableObject, mLocation) == 0x90);
} // namespace NKHook5::Classes