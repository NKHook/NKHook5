#ifndef NKHOOK5_CLASSES_ISCREENDATA
#define NKHOOK5_CLASSES_ISCREENDATA
namespace NKHook5
{
    namespace Classes
    {
        class IScreenData
        {
        public:
            IScreenData() {
                //We need to set the vtable to the game's vtable
                //this is because the game uses RTDynamicCast and that fails with
                //our own vtables!
                *(void**)this = *(void**)Signatures::GetAddressOf(Sigs::IScreenData_VTable);
            }
            virtual ~IScreenData() {};
        };
    } // namespace Classes

} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_ISCREENDATA */
