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
            ghstl::string text; //0x00C8
            char pad_00E0[136]; //0x00E0
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
            virtual ~CTextObject() {};
        };
    } // namespace Classes

} // namespace NKHook5