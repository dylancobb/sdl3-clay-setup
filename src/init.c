#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define CLAY_IMPLEMENTATION
#include "clay/clay.h"

#include "state.h"

void HandleClayErrors(Clay_ErrorData errorData) {
    SDL_Log("%s", errorData.errorText.chars);
}

static inline Clay_Dimensions SDL_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *userData) {
    TTF_Font **fonts = userData;
    TTF_Font *font = fonts[config->fontId];
    int width, height;

    TTF_SetFontSize(font, config->fontSize);
    if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to measure text = %s", SDL_GetError());
    }

    return (Clay_Dimensions) { (float) width, (float) height };
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    AppState *state = SDL_calloc(1, sizeof(AppState));
    if (!state) {
        SDL_Log("Failed to allocate memory for AppState = %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("SDL3 + Clay", 800, 600, SDL_WINDOW_RESIZABLE,
                                     &state->window, &state->rendererData.renderer)) {
        SDL_Log("Failed to create window and renderer = %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Failed to initialise SDL_ttf = %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->rendererData.textEngine = TTF_CreateRendererTextEngine(state->rendererData.renderer);
    if (!state->rendererData.textEngine) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create text engine from renderer = %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->rendererData.fonts = SDL_calloc(FONT_COUNT, sizeof(TTF_Font *));
    if (!state->rendererData.fonts) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for the font array = %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    #define FONT_PATH "resources/Fira-Code.ttf"
    
    TTF_Font* font_normal = TTF_OpenFont(FONT_PATH, 24);
    TTF_Font* font_bold   = TTF_OpenFont(FONT_PATH, 24);
    TTF_Font* font_italic = TTF_OpenFont(FONT_PATH, 24);
    
    if (!font_normal || !font_bold || !font_italic) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font = %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    TTF_SetFontStyle(font_normal, TTF_STYLE_NORMAL);
    TTF_SetFontStyle(font_bold,   TTF_STYLE_BOLD);
    TTF_SetFontStyle(font_italic, TTF_STYLE_ITALIC);
    
    state->rendererData.fonts[FONT_NORMAL] = font_normal;
    state->rendererData.fonts[FONT_BOLD]   = font_bold;
    state->rendererData.fonts[FONT_ITALIC] = font_italic;

    /* Initialize Clay */
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = SDL_malloc(totalMemorySize),
        .capacity = totalMemorySize
    };

    int width, height;
    SDL_GetWindowSize(state->window, &width, &height);
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float) width, (float) height }, (Clay_ErrorHandler) { HandleClayErrors });
    Clay_SetMeasureTextFunction(SDL_MeasureText, state->rendererData.fonts);

    state->needs_redraw = true;
    state->animating = false;
    state->last_frame_ns = 0;

    return SDL_APP_CONTINUE;
}
