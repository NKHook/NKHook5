#ifndef NKHOOK5_CLASSES_MATRIX16F
#define NKHOOK5_CLASSES_MATRIX16F
namespace NKHook5
{
    namespace Classes
    {
        struct Matrix16F
        {
            union
            {
                struct
                {
                    float a;
                    float b;
                    float c;
                    float d;
                    float e;
                    float f;
                    float g;
                    float h;
                    float i;
                    float j;
                    float k;
                    float l;
                    float m;
                    float n;
                    float o;
                    float p;
                };
                float arr[16];
            };
        };
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_MATRIX16F */
