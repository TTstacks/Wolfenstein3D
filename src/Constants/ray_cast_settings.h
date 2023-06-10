#ifndef RAYCASTSETTINGS_H_
#define RAYCASTSETTINGS_H_
#include <numbers>

constexpr float pi = std::numbers::pi_v<float>;
constexpr float fov = pi / 3;
constexpr float half_fov = fov / 2;
constexpr unsigned ray_number = 350;
constexpr unsigned half_ray_number = ray_number / 2 - 1;
constexpr float projection_coefficient = static_cast<float>(ray_number) / (2.f * 0.5773502691896f);
constexpr float delta_angle = fov / ray_number;
#endif