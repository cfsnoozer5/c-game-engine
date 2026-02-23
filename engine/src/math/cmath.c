#include "cmath.h"

#include "platform/platform.h"

#include <stdlib.h>
#include <math.h>

static b8 rand_seeded = FALSE;

f32 c_sin(f32 x) {
    return sinf(x);
}

f32 c_cos(f32 x) {
    return cosf(x);
}

f32 c_tan(f32 x) {
    return tanf(x);
}

f32 c_acos(f32 x) {
    return acosf(x);
}

f32 c_sqrt(f32 x) {
    return sqrtf(x);
}

f32 c_abs(f32 x) {
    return fabsf(x);
}

i32 c_random() {
    if (!rand_seeded) {
        srand((u32)platform_get_absolute_time());
        rand_seeded = TRUE;
    }
    return rand();
}

i32 c_random_in_range(i32 min, i32 max) {
    if (!rand_seeded) {
        srand((u32)platform_get_absolute_time());
        rand_seeded = TRUE;
    }
    return (rand() % (max - min + 1)) + min;
}

f32 c_frandom() {
    return (float)c_random() / (f32)RAND_MAX;
}

f32 c_frandom_in_range(f32 min, f32 max) {
    return min + ((float)c_random() / ((f32)RAND_MAX / (max - min)));
}