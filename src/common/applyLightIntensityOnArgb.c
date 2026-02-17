#include <stdint.h>

uint32_t applyLightIntensistyOnArgb(uint32_t argb, float factor) {
    if(factor < 0.0f) factor = 0.0f;
    if(factor > 1.0f) factor = 1.0f;
    uint32_t a = (argb & 0xFF000000);
    uint32_t r = (argb & 0x00FF0000) * factor;
    uint32_t g = (argb & 0x0000FF00) * factor;
    uint32_t b = (argb & 0x000000FF) * factor;
    return a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}