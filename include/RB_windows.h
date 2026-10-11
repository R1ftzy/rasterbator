#ifndef RB_WINDOWS_H
#define RB_WINDOWS_H
#include <stdbool.h>
#include <stdint.h>

bool RB_is_running();

void RB_create_window();

void RB_set_title(const char *title);

uint64_t RB_get_delta_time();

void RB_draw_frame();

#endif