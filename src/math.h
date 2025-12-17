#pragma once

#define PI 3.14159265358979323846f

struct Vec2 {
    float x;
    float y;
};

float dist(struct Vec2 a, struct Vec2 b);
float dist_sqr(struct Vec2 a, struct Vec2 b);
