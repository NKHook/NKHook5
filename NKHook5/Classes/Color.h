#ifndef NKHOOK5_CLASSES_COLOR
#define NKHOOK5_CLASSES_COLOR
namespace NKHook5
{
    namespace Classes
    {
        class Color
        {
            union{
                struct{
                    char Red,Green,Blue,Alpha;
                };
                char arr[4];
            };
        };
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_COLOR */
