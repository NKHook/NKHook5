#ifndef NKHOOK5_CLASSES_CBLOONSTD5GAME
#define NKHOOK5_CLASSES_CBLOONSTD5GAME

#include "CApp.h"

namespace NKHook5
{
	namespace Classes
	{
		class CBloonsTD5Game : public CApp
		{
		private:
			char pad_01C4[4]; //0x01C4
		public:
			virtual ~CBloonsTD5Game() {};
		};
	} // namespace Classes
	
} // namespace NKHook5


#endif /* NKHOOK5_CLASSES_CBLOONSTD5GAME */
