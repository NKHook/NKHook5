#ifndef MANAGED_CLASSES_CLASSWRAPPER
#define MANAGED_CLASSES_CLASSWRAPPER
namespace NKHook5
{
	namespace Managed
	{
		namespace Classes
		{
			public ref class ClassWrapper
			{
			private:
				System::IntPtr nativePtr;
			public:
				property System::IntPtr native {
					System::IntPtr get()
					{
						return nativePtr;
					}
				};
				ClassWrapper::ClassWrapper(System::IntPtr nativePtr)
				{
					this->nativePtr = nativePtr;
				};
			};
		} // namespace Classes
	} // namespace Managed
} // namespace NKHook5


#endif /* MANAGED_CLASSES_CLASSWRAPPER */
