#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "LTexture.h"
#include "App.h"
#include "utility.h"



int main(int argc, char* args[]) {
    int exitCode{0};
    App app;

    if (app.Init("Window", 640, 480)) {
        //Texture Loading
        app.GetOrLoadTexture("dots", "dots.png", true, new RGB{0,255,255});



        const std::vector<SDL_FRect> clipRectForSprite = generateClipRectForSpriteSheet(2,2,100);


        // Main loop
        while (!app.gameLoop()->WindowShouldClose()) {
            app.gameLoop()->PollEvents();
            ClearScreen(app.GetRenderer(),RGBA{0,0,0,0});

            if (app.KeyJustPressed(SDLK_ESCAPE)) {
                app.gameLoop()->Quit();
            }

            spriteClippingExample(clipRectForSprite, app);


            SDL_RenderPresent(app.GetRenderer());
        }

    } else {
        exitCode = -1;
    }
    app.shutdown();

    return exitCode;
}