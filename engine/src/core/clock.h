#pragma once
#include "defines.h"

typedef struct clock {
    f64 start_time;
    f64 elapsed;
} clock;

void clock_update(clock* clock);

// Starts the provided clock. Reset elapsed time
void clock_start(clock* clock);

// Stops the provided clock. Does not reset elapsed time
void clock_stop(clock* clock);