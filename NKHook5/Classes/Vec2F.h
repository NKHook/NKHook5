#ifndef NKHOOK5_CLASSES_VEC2F
#define NKHOOK5_CLASSES_VEC2F
namespace NKHook5
{
    namespace Classes
    {
        struct Vec2F
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
        public:
            Vec2F() {
                this->x = 0;
                this->y = 0;
            }
            Vec2F(float x, float y) {
                this->x = x;
                this->y = y;
            }
        };
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_VEC2F */
