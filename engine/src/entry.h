#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "core/cmemory.h"
#include "game_types.h"

// Externall-defined function
extern b8 create_game(game* out_game);

/**
 * The main entry point of the application.
 */
int main() {
    
    intialize_memory();

    game game_inst;
    if (!create_game(&game_inst)) {
        CFATAL("Could not create game!");
        return -1;
    }

    if (!game_inst.render || !game_inst.update || !game_inst.intialize || !game_inst.on_resize) {
        CFATAL("The game's function pointers must be assigned!");
        return -2;
    }

    // Initialization
    if (!application_create(&game_inst)) {
        CINFO("Application failed to create!");
        return 1;
    }

    // Begin the game loop.
    if (!application_run()) {
        CINFO("Application did not shutdown gracefully");
        return 2;
    }

    shutdown_memory();

    return 0;
}