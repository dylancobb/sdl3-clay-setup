#pragma once

#include <SDL3/SDL.h>
#include "clay/renderer.h"

enum FontID {
    FONT_NORMAL,
    FONT_BOLD,
    FONT_ITALIC,
    FONT_COUNT
};

typedef struct ColorSet {
    Clay_Color background;
    Clay_Color foreground;
    Clay_Color accent;
    Clay_Color text;
} ColorSet;

typedef enum Theme {
    THEME_DARK,
    THEME_LIGHT
} Theme;

typedef struct AppState {
    SDL_Window *window;
    Clay_SDL3RendererData rendererData;
    ColorSet colors;
    Theme theme;
    bool needs_redraw;
    bool animating;
    Uint64 last_frame_ns;
} AppState;
