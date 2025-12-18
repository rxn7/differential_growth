#pragma once

#define PI 3.14159265358979323846f

struct Vec2 {
    float x;
    float y;
};

float vec2_magnitude(struct Vec2 v);
float vec2_mag_sqr(struct Vec2 v);
float vec2_distance(struct Vec2 a, struct Vec2 b);
float vec2_dist_sqr(struct Vec2 a, struct Vec2 b);

struct Vec2 vec2_normalize(struct Vec2 v);
struct Vec2 vec2_set_magnitude(struct Vec2 v, float magnitude); 
struct Vec2 vec2_limit(struct Vec2 v, float max);
struct Vec2 vec2_add(struct Vec2 a, struct Vec2 b);
struct Vec2 vec2_sub(struct Vec2 a, struct Vec2 b);
struct Vec2 vec2_mul(struct Vec2 a, float scalar);
struct Vec2 vec2_div(struct Vec2 a, float scalar);
