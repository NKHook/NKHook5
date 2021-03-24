#ifndef MANAGED_CLASSES_CBLOONSTD5GAME
#define MANAGED_CLASSES_CBLOONSTD5GAME

#include "IBasePointers.h"

namespace NKHook5
{
	namespace Managed
	{
		namespace Classes
		{
			public ref class CBloonsTD5Game : public IBasePointers
			{
			private:
				static CBloonsTD5Game^ instance;
			public:
				CBloonsTD5Game(System::IntPtr nativePtr) : IBasePointers(nativePtr)
				{
					if(instance == nullptr)
						instance = this;
				};
				static CBloonsTD5Game^ getInstance()
				{
					if(instance == nullptr)
					{
						System::Console::WriteLine("CBloonsTD5Game is null? something has gone terribly wrong!");
					}
					return instance;
				};
			};
		} // namespace Classes
		
	} // namespace Managed

} // namespace NKHook5


#endif /* MANAGED_CLASSES_CBLOONSTD5GAME */
