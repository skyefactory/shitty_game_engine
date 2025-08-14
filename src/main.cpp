#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "LTexture.h"
#include "App.h"
#include "utility.h"

std::vector<SDL_FRect> generateClipRectForSpriteSheet(
    int horizontalSpriteCount,
    int verticalSpriteCount,
    int sizeOfSprite)
{
    std::vector<SDL_FRect> clipRectForSprite;
    clipRectForSprite.reserve(horizontalSpriteCount * verticalSpriteCount);

    for (int v = 0; v < verticalSpriteCount; ++v) {
        for (int h = 0; h < horizontalSpriteCount; ++h) {
            SDL_FRect clip;
            clip.x = static_cast<float>(h * sizeOfSprite);
            clip.y = static_cast<float>(v * sizeOfSprite);
            clip.w = static_cast<float>(sizeOfSprite);
            clip.h = static_cast<float>(sizeOfSprite);

            clipRectForSprite.push_back(clip);
        }
    }

    return clipRectForSprite;
}


void ClearScreen(SDL_Renderer *renderer,const int r,const int g,const int b,const int a) {
    SDL_SetRenderDrawColor(renderer, dth(r), dth(g), dth(b), dth(a));
    SDL_RenderClear(renderer);
}

int main(int argc, char* args[]) {
    int exitCode{0};
    App app;

    if (app.Init("Window", 640, 480)) {
        //Texture Loading
        app.GetOrLoadTexture("dots", "dots.png", true, new RGB{0,255,255});

        const vec2<float> baseSize = {100.f, 100.f};
        const vec2<int> screenSize = app.GetScreenSize();

        std::vector<SDL_FRect> clipRectForSprite = generateClipRectForSpriteSheet(2,2,100);


        // Main loop
        while (!app.gameLoop()->WindowShouldClose()) {
            app.gameLoop()->PollEvents();
            ClearScreen(app.GetRenderer(), 0, 0, 0, 0);

            if (app.KeyJustPressed(SDLK_ESCAPE)) {
                app.gameLoop()->Quit();
            }

            app.RenderTexture({0.f, 0.f}, baseSize, &clipRectForSprite[0], "dots");

            app.RenderTexture({screenSize.x - baseSize.x / 2.f, 0.f},
                              {baseSize.x / 2.f, baseSize.y / 2.f},
                              &clipRectForSprite[1], "dots");

            app.RenderTexture({0.f, screenSize.y - baseSize.y * 2.f},
                              {baseSize.x, baseSize.y * 2.f},
                              &clipRectForSprite[2], "dots");

            app.RenderTexture({screenSize.x - baseSize.x,
                               screenSize.y - baseSize.y},
                              baseSize,
                              &clipRectForSprite[3], "dots");

            SDL_RenderPresent(app.GetRenderer());
        }

    } else {
        exitCode = -1;
    }
    app.shutdown();

    return exitCode;
}