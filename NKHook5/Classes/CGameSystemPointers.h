#ifndef NKHOOK5_CLASSES_CGAMESYSTEMPOINTERS
#define NKHOOK5_CLASSES_CGAMESYSTEMPOINTERS

#include "IBasePointers.h"
#include "CTowerFactory.h"
#include "CPlayerProfileV1.h"

namespace NKHook5
{
	namespace Classes
	{
		class CGameSystemPointers
		{
		public:
			//char pad_0000[4]; //0x0000
			IBasePointers basePointers; //0x0004
			char pad_0070[48]; //0x0070
			CTowerFactory* pTowerFactory; //0x00A0
			char pad_00A4[32]; //0x00A4
			CPlayerProfileV1* pProfile; //0x00C4
			char pad_00C8[40]; //0x00C8
		public:
			virtual ~CGameSystemPointers() {};
		};

		static_assert(offsetof(CGameSystemPointers, pProfile) == 0xC4);
	} // namespace Classes

} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_CGAMESYSTEMPOINTERS */
