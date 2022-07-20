#ifndef NKHOOK5_CLASSES_CBASESCREEN
#define NKHOOK5_CLASSES_CBASESCREEN

#include "IBasePointers.h"

namespace NKHook5
{
	namespace Classes
	{
		enum class Device {
			PHONE = 0,
			TABLET = 1,
			UNKNOWN = 2
		};

		class CBaseScreen : public IBasePointers
		{
		public:
		public:
			virtual ~CBaseScreen() {};
		};
	} // namespace Classes

} // namespace NKHook5

#endif /* NKHOOK5_CLASSES_CBASESCREEN */
