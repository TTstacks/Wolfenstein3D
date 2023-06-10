#ifndef TEXTURESETTINGS_H_
#define TEXTURESETTINGS_H_
#include "game_settings.h"
#include "ray_cast_settings.h"

constexpr int texture_size = 64;
constexpr int texture_scale = texture_size / (window_width / ray_number);
constexpr int wall_width = window_width / ray_number;
constexpr int texture_wall_size = texture_size / wall_width;
#endif