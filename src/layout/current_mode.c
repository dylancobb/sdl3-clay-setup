#include "../state.h"

void current_mode(AppState *state) {
    CLAY(CLAY_ID("Current Mode"), {
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(0)
            },
            .childAlignment = {
                .x = CLAY_ALIGN_X_CENTER
            },
            .padding = {
                .top = 8,
                .bottom = 8
            }
        },
        .backgroundColor = state->colors.bar
    }) {
        CLAY_TEXT(CLAY_STRING("Current: "), CLAY_TEXT_CONFIG({
            .fontId = FONT_BOLD,
            .fontSize = 16,
            .textColor = state->colors.text
        }));
        CLAY_TEXT(
            state->theme == THEME_DARK
                ? CLAY_STRING("Dark")
                : CLAY_STRING("Light"),
            CLAY_TEXT_CONFIG({
                .fontId = FONT_ITALIC,
                .fontSize = 16,
                .textColor = state->colors.text
            }));
    }
}
