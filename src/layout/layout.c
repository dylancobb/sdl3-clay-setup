#include "../state.h"

#include "current_mode.h"
#include "toggle_button.h"

Clay_RenderCommandArray create_app_layout(AppState *state) {
    Clay_Sizing layoutExpand = {
        .width = CLAY_SIZING_GROW(0),
        .height = CLAY_SIZING_GROW(0)
    };

    Clay_BeginLayout();

    CLAY(CLAY_ID("Layout Background"), {
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = layoutExpand,
            .padding = CLAY_PADDING_ALL(32),
            .childGap = 8,
            .childAlignment = {
                .x = CLAY_ALIGN_X_CENTER
            }
        },
        .backgroundColor = state->colors.background
    }) {
        CLAY_TEXT(CLAY_STRING("Going Interactive"), CLAY_TEXT_CONFIG({
            .fontId = FONT_BOLD,
            .fontSize = 32,
            .textColor = state->colors.text,
        }));
        CLAY(CLAY_ID("Main Container"), {
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = layoutExpand,
                .padding = {
                    .top = 24
                },
                .childAlignment = {
                    .x = CLAY_ALIGN_X_CENTER
                },
                .childGap = 24
            },
            .backgroundColor = state->colors.foreground,
            .cornerRadius = CLAY_CORNER_RADIUS(8)
        }) {
            current_mode(state);
            toggle_button(state);
        }
    }

    return Clay_EndLayout();
}
