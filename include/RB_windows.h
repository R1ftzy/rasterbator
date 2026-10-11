#ifndef RB_WINDOWS_H
#define RB_WINDOWS_H
#include <stdbool.h>
#include <stdint.h>

// Returns true if program is running
bool RB_is_running();

// Creates a window (SDL or Win32)
void RB_create_window();

// Sets title for a window
void RB_set_title(const char *title);

// Returns delta time
uint64_t RB_get_delta_time();

// Draws framebuffer to window
void RB_draw_frame();

#endif