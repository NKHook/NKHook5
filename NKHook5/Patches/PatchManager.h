#ifndef PATCHMANAGER
#define PATCHMANAGER
#include "IPatch.h"
#include <vector>

namespace NKHook5
{
    namespace Patches
    {
        class PatchManager
        {
            static inline std::vector<IPatch*>* patches = new std::vector<IPatch*>();
        public:
            static void ApplyAll();
            static void ApplyPatch(IPatch* toAdd);
        };
    }
}
#endif /* PATCHMANAGER */
