#include "../state.h"

Clay_RenderCommandArray create_app_layout(AppState *state) {
    Clay_BeginLayout();

    const Clay_Color backgroundColor = { 30, 30, 46, 255 };
    const Clay_Color foregroundColor = { 24, 24, 37, 255 };
    const Clay_Color accentColor = { 49, 50, 68, 255 };
    const Clay_Color textColor = { 205, 214, 244, 255 };

    CLAY(CLAY_ID("Main Container"), {
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = {
                .width = CLAY_SIZING_GROW(0),
                .height = CLAY_SIZING_GROW(0)
            },
            .padding = CLAY_PADDING_ALL(8)
        },
        .backgroundColor = backgroundColor
    }) {
        CLAY(CLAY_ID("Text Container"), {
            .layout = {
                .padding = CLAY_PADDING_ALL(8)
            },
            .backgroundColor = foregroundColor,
            .border = {
                .color = accentColor,
                .width = CLAY_BORDER_ALL(1)
            },
            .cornerRadius = CLAY_CORNER_RADIUS(5)
        }) {
            CLAY_TEXT(CLAY_STRING("Hello World"), CLAY_TEXT_CONFIG({
                .fontSize = 16,
                .textColor = textColor,
                .fontId = FONT_NORMAL
            }));
        }
    }

    return Clay_EndLayout();

}
