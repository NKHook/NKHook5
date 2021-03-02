#ifndef NKHOOK5_CLASSES_VEC2F
#define NKHOOK5_CLASSES_VEC2F
namespace NKHook5
{
    namespace Classes
    {
        class Vec2F
        {
            union
            {
                struct
                {
                    float x;
                    float y;
                };
                float arr[2];
            };
        };
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_VEC2F */
