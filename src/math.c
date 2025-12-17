#include <math.h>
#include "math.h"

float dist(struct Vec2 a, struct Vec2 b) {
    return sqrtf(dist_sqr(a, b));
}

float dist_sqr(struct Vec2 a, struct Vec2 b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
