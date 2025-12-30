#pragma once

#include <SDL3/SDL.h>
#include "clay/renderer.h"

enum FontID {
    FONT_NORMAL,
    FONT_BOLD,
    FONT_ITALIC,
    FONT_COUNT
};

typedef struct AppState {
    SDL_Window *window;
    Clay_SDL3RendererData rendererData;
    bool needs_redraw;
    bool animating;
    Uint64 last_frame_ns;
} AppState;
