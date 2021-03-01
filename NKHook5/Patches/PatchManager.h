#ifndef NKHOOK5_PATCHES_PATCHMANAGER
#define NKHOOK5_PATCHES_PATCHMANAGER
#include <vector>

namespace NKHook5
{
    namespace Patches
    {
        class PatchManager
        {
            static inline std::vector<class IPatch*>* patches = new std::vector<class IPatch*>();
        public:
            static void ApplyAll();
            static void ApplyPatch(class IPatch* toAdd);
        };
    }
}
#endif /* NKHOOK5_PATCHES_PATCHMANAGER */
