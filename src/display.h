#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdbool.h>

bool init_window();
void destroy_window();

// color buffer
void clearColorBuffer(uint32_t color);
void updateColorBuffer();
void renderColorBuffer();

#endif