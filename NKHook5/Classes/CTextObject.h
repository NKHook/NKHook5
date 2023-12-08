#pragma once

#include "../../Util/NewFramework.h"

#include "Macro.h"
#include "CRenderableTextureObject.h"
#include "CFont.h"
#include "Vec2F.h"

#include <boost/shared_ptr.hpp>

#include <utility>

namespace NKHook5::Classes
{
	using namespace Signatures;

	class CTextObject : public CRenderableTextureObject
	{
	public:
		/* Somehow prevented some heap corruption bug... */
		overload_allocators

	public:
		ghstl::string mText; //0x00C8
		char pad_00E0[80]{}; //0x00E0
		int32_t unknownRenderRuleSetZero{}; //0x0130
		char pad_0134[32]{}; //0x0134
	public:
		CTextObject() {
			ThisConstruct<Sigs::CTextObject_CCTOR_A>(this);
		}
		CTextObject(Vec2F position, boost::shared_ptr<CFont>& font, std::string text) {
			ThisConstruct<Sigs::CTextObject_CCTOR_B>(this, position, font, std::move(text));
		}
		CTextObject(boost::shared_ptr<CFont>& font, std::string text) {
			ThisConstruct<Sigs::CTextObject_CCTOR_C>(this, font, std::move(text));
		}

		~CTextObject() override = default;

		virtual void SetAlpha(float alpha) {}
		virtual void SetColor(Color& color, int param_2) {}
		virtual void MixWithColor(Color& color) {}
		virtual void* FUN_009ad610(uint32_t param_2) { return nullptr; }
		virtual void SetGradient(class Vec4F* firstColor, class Vec4F* secondColor, int param_3) {}
		virtual void SetString(nfw::string* text) {}
		virtual void* FUN_009abb80() { return nullptr; }
		virtual int CountLines() { return 0; }
		virtual float GetLineWidth(uint32_t param_1) { return 0.0f; }
	};

	static_assert(sizeof(CTextObject) == 0x154);
	static_assert(offsetof(CTextObject, mText) == 0xC8);
} // namespace NKHook5::Classes