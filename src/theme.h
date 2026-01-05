#include "state.h"

static inline void set_theme_dark(AppState *state) {
    state->colors.background = (Clay_Color){ 30, 30, 46, 255 };
    state->colors.foreground = (Clay_Color){ 24, 24, 37, 255 };
    state->colors.bar = (Clay_Color){ 17, 17, 27, 255 };
    state->colors.text = (Clay_Color){ 205, 214, 244, 255 };
    state->colors.textFaded = (Clay_Color){ 88, 91, 112, 255 };

    state->theme = THEME_DARK;
    state->needs_redraw = true;
}

static inline void set_theme_light(AppState *state) {
    state->colors.background = (Clay_Color){ 239, 241, 245, 255 };
    state->colors.foreground = (Clay_Color){ 230, 233, 239, 255 };
    state->colors.bar = (Clay_Color){ 220, 224, 232, 255 };
    state->colors.text = (Clay_Color){ 76, 79, 105, 255 };
    state->colors.textFaded = (Clay_Color){ 172, 176, 190, 255 };

    state->theme = THEME_LIGHT;
    state->needs_redraw = true;
}

static inline void toggle_theme(AppState *state) {
    if (state->theme == THEME_DARK)
        set_theme_light(state);
    else 
        set_theme_dark(state);
}
