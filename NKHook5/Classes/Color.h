#ifndef NKHOOK5_CLASSES_COLOR
#define NKHOOK5_CLASSES_COLOR

#include <stdint.h>

namespace NKHook5
{
    namespace Classes
    {
        struct Color
        {
            union{
                struct{
                    uint8_t Red,Green,Blue,Alpha;
                };
                uint8_t arr[4];
            };

            Color() {
                this->Red = 0xFF;
                this->Green = 0xFF;
                this->Blue = 0xFF;
                this->Alpha = 0xFF;
            }
            Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : Color() {
                this->Red = r;
                this->Green = g;
                this->Blue = b;
                this->Alpha = a;
            }
        };
    } // namespace Classes
    
} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_COLOR */
