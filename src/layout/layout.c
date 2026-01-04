#include "../state.h"

Clay_RenderCommandArray create_app_layout(AppState *state) {
    Clay_BeginLayout();

    CLAY(CLAY_ID("Main Container"), {
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = {
                .width = CLAY_SIZING_GROW(0),
                .height = CLAY_SIZING_GROW(0)
            },
            .padding = CLAY_PADDING_ALL(8)
        },
        .backgroundColor = state->colors.background
    }) {
        CLAY(CLAY_ID("Text Container"), {
            .layout = {
                .padding = CLAY_PADDING_ALL(8)
            },
            .backgroundColor = state->colors.foreground,
            .border = {
                .color = state->colors.accent,
                .width = CLAY_BORDER_ALL(1)
            },
            .cornerRadius = CLAY_CORNER_RADIUS(5)
        }) {
            CLAY_TEXT(CLAY_STRING("Hello World"), CLAY_TEXT_CONFIG({
                .fontSize = 16,
                .textColor = state->colors.text,
                .fontId = FONT_NORMAL
            }));
        }
    }

    return Clay_EndLayout();

}
