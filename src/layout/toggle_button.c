#include "../state.h"
#include "../theme.h"

void HandleButtonInteraction(Clay_ElementId elementId, Clay_PointerData pointerInfo, void *state) {
    if (pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        toggle_theme(state);
    }
}

void toggle_button(AppState *state) {
    CLAY(CLAY_ID("Toggle button"), {
        .layout = {
            .padding = CLAY_PADDING_ALL(8)
        },
        .backgroundColor = state->colors.foreground,
        .border = {
            .color = Clay_Hovered() ? state->colors.text : state->colors.textFaded,
            .width = CLAY_BORDER_ALL(1)
        },
    }) {
        bool buttonHovered = Clay_Hovered();
        Clay_OnHover(HandleButtonInteraction, state);
        CLAY_TEXT(CLAY_STRING("Toggle Theme"), CLAY_TEXT_CONFIG({
            .fontId = FONT_NORMAL,
            .fontSize = 16,
            .textColor = buttonHovered ? state->colors.text : state->colors.textFaded
        }));
    }
}
