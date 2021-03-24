#ifndef MANAGED_CLASSES_IBASEPOINTERS
#define MANAGED_CLASSES_IBASEPOINTERS

#include <Classes/IBasePointers.h>

#include "ClassWrapper.h"
#include "CBloonsTD5Game.h"

namespace NKHook5
{
	namespace Managed
	{
		namespace Classes
		{
			public ref class IBasePointers : public ClassWrapper
			{
			public:
				property CBloonsTD5Game^ gameInstance
				{
					CBloonsTD5Game^ get()
					{
						System::IntPtr self = this->native;
						NKHook5::Classes::IBasePointers* nativeInstance = (NKHook5::Classes::IBasePointers*)(void*)self;
						NKHook5::Classes::CBloonsTD5Game* gamePtr = nativeInstance->CBloonsTD5Game;
						NKHook5::Managed::Classes::CBloonsTD5Game^ managedInstance = gcnew NKHook5::Managed::Classes::CBloonsTD5Game((System::IntPtr)(void*)gamePtr);
						return managedInstance;
					}
				};
				IBasePointers(System::IntPtr nativePtr) : ClassWrapper(nativePtr)
				{};
			};
		} // namespace Classes
		
	} // namespace Managed

} // namespace NKHook5

#endif /* MANAGED_CLASSES_IBASEPOINTERS */
