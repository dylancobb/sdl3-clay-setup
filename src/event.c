#include <SDL3/SDL.h>
#include "state.h"
#include "theme.h"

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *state = (AppState*) appstate;

    switch (event->type) {
    case SDL_EVENT_KEY_DOWN:
        switch (event->key.scancode) {
        case SDL_SCANCODE_ESCAPE:
            return SDL_APP_SUCCESS;
        case SDL_SCANCODE_APOSTROPHE:
            state->needs_redraw = true;
            state->debug_open = !state->debug_open;
            Clay_SetDebugModeEnabled(state->debug_open);
            break;
        default:
            break;
        }

    case SDL_EVENT_MOUSE_MOTION:
        state->needs_redraw = true; 
        Clay_SetPointerState((Clay_Vector2) { event->motion.x, event->motion.y }, event->button.down);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        state->needs_redraw = true;
        Clay_SetPointerState((Clay_Vector2) { event->motion.x, event->motion.y }, true);
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        state->needs_redraw = true;
        Clay_SetPointerState((Clay_Vector2) { event->motion.x, event->motion.y }, false);
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        state->needs_redraw = true;
        float deltaTime = ((float) SDL_GetTicksNS() - state->last_frame_ns) / 1e9; 
        Clay_UpdateScrollContainers(true, (Clay_Vector2) { event->wheel.x, event->wheel.y }, deltaTime);
        break;

    case SDL_EVENT_WINDOW_RESIZED:
        state->needs_redraw = true;
        int width, height;
        SDL_GetWindowSize(state->window, &width, &height);
        Clay_SetLayoutDimensions((Clay_Dimensions) {(float) width, (float) height});
        break;

    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}
