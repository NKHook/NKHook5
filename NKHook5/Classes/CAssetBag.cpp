#include "CAssetBag.h"

#include "Macro.h"

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::Signatures;

void CAssetBag::StartUsing(const CAssetBag::eAssetType& type, const nfw::string& asset) {
	return ThisCall<Sigs::CAssetBag_StartUsing, &CAssetBag::StartUsing>(this, type, asset);
}