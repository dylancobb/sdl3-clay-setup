#include <SDL3/SDL.h>

#include "layout/layout.h"
#include "state.h"

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *state = (AppState*) appstate;

    SDL_SetRenderDrawColor(state->rendererData.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->rendererData.renderer);
    Clay_RenderCommandArray render_commands = create_app_layout(state);
    SDL_Clay_RenderClayCommands(&state->rendererData, &render_commands);
    SDL_RenderPresent(state->rendererData.renderer);

    return SDL_APP_CONTINUE;
}
