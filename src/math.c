#include <math.h>
#include "math.h"

float vec2_magnitude(struct Vec2 v) {
    return sqrtf(vec2_mag_sqr(v));
}

float vec2_mag_sqr(struct Vec2 v) {
    return v.x * v.x + v.y * v.y;
}

float vec2_distance(struct Vec2 a, struct Vec2 b) {
    return sqrtf(vec2_dist_sqr(a, b));
}

float vec2_dist_sqr(struct Vec2 a, struct Vec2 b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Vec2 vec2_normalize(struct Vec2 v) {
    const float length = vec2_magnitude(v);

    if(length == 0.0f) {
        return (struct Vec2){0};
    }

    return (struct Vec2){
        v.x / length,
        v.y / length
    };
}

struct Vec2 vec2_set_magnitude(struct Vec2 v, float magnitude) {
    const float length = vec2_magnitude(v);

    if(length == 0.0f) {
        return (struct Vec2){0};
    }

    float scale = magnitude / length;
    return (struct Vec2){
        v.x * scale,
        v.y * scale
    };
}

struct Vec2 vec2_limit(struct Vec2 v, float max) {
    const float length_sqr = vec2_mag_sqr(v);
    if(length_sqr > max * max) {
        return vec2_set_magnitude(v, max);
    }

    return v;
}

struct Vec2 vec2_add(struct Vec2 a, struct Vec2 b) {
    return (struct Vec2){
        a.x + b.x,
        a.y + b.y
    };
}

struct Vec2 vec2_sub(struct Vec2 a, struct Vec2 b) {
    return (struct Vec2){
        a.x - b.x,
        a.y - b.y
    };
}

struct Vec2 vec2_mul(struct Vec2 a, float scalar) {
    return (struct Vec2){
        a.x * scalar,
        a.y * scalar
    };
}

struct Vec2 vec2_div(struct Vec2 a, float scalar) {
    if(scalar == 0.0f) {
        return (struct Vec2){0};
    }

    return (struct Vec2){
        a.x / scalar,
        a.y / scalar
    };
}
