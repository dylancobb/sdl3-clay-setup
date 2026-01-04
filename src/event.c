#include <SDL3/SDL.h>
#include "state.h"
#include "theme.h"

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *state = (AppState*) appstate;

    if (event->type == SDL_EVENT_KEY_DOWN && event->key.scancode == SDL_SCANCODE_ESCAPE ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    
    if (event->type == SDL_EVENT_WINDOW_RESIZED) {
        state->needs_redraw = true;

        int width, height;
        SDL_GetWindowSize(state->window, &width, &height);
        Clay_SetLayoutDimensions((Clay_Dimensions) {(float) width, (float) height});

        return SDL_APP_CONTINUE;
    }

    if (event->type == SDL_EVENT_KEY_DOWN && event->key.scancode == SDL_SCANCODE_T) {
        toggle_theme(state);

        return SDL_APP_CONTINUE;
    }

    return SDL_APP_CONTINUE;
}
