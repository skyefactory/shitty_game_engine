#include "utility.h"
#include "App.h"

void spriteClippingExample(const std::vector<SDL_FRect> &spriteClips, App &app) {
    constexpr vec2<float> baseSize = {100.f, 100.f};
    const vec2<int> screenSize = app.GetScreenSize();

    app.RenderTexture({0.f, 0.f}, baseSize, &spriteClips[0], "dots");

    app.RenderTexture({screenSize.x - baseSize.x / 2.f, 0.f},
                      {baseSize.x / 2.f, baseSize.y / 2.f},
                      &spriteClips[1], "dots");

    app.RenderTexture({0.f, screenSize.y - baseSize.y * 2.f},
                      {baseSize.x, baseSize.y * 2.f},
                      &spriteClips[2], "dots");

    app.RenderTexture({screenSize.x - baseSize.x,
                       screenSize.y - baseSize.y},
                      baseSize,
                      &spriteClips[3], "dots");
}

void ClearScreen(SDL_Renderer *renderer, RGBA rgba) {
    SDL_SetRenderDrawColor(renderer, dth(rgba.r), dth(rgba.g), dth(rgba.b), dth(rgba.a));
    SDL_RenderClear(renderer);
}
