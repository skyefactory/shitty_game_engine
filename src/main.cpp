#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "LTexture.h"
#include "App.h"
#include "utility.h"


void ClearScreen(SDL_Renderer *renderer,const int r,const int g,const int b,const int a) {
    SDL_SetRenderDrawColor(renderer, dth(r), dth(g), dth(b), dth(a));
    SDL_RenderClear(renderer);
}

int main(int argc, char* args[]) {
    int exitCode{0};
    App app;

    if (app.Init("Window", 640, 480)) {
        //Texture Loading

        app.GetOrLoadTexture("test","test.png", true, new RGB{100,0,0});

        //Main Loop
        while (!app.gameLoop()->WindowShouldClose()) {
            app.gameLoop()->PollEvents();
            ClearScreen(app.GetRenderer(), 255,255,255,0);
            if (app.KeyJustPressed(SDLK_ESCAPE)) {
                app.gameLoop()->Quit();
            }

            SDL_RenderPresent(app.GetRenderer());
        }

    } else {
        exitCode = -1;
    }
    app.shutdown();

    return exitCode;
}