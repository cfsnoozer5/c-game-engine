#pragma once

#include "core/application.h"

/** 
 * Represents the basic game state.
 * Called for creation by the application.
*/
typedef struct game {
    application_config app_config;

    // Function pointer to game's intialize function
    b8 (*intialize)(struct game* game_inst);

    // Function pointer to the game's update function.
    b8 (*update)(struct game* game_inst, f32 delta_time);

    // Function pointer to the game's render function
    b8 (*render)(struct game* game_inst, f32 delta_time);

    // Function pointer to the game's on_resize function
    void (*on_resize)(struct game* game_inst, u32 width, u32 height);

    // Game-specifc game state. Created an managed by the game.
    void* state;

    // Application state
    void* application_state;
} game;