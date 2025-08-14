//
// Created by host on 8/8/25.
//

#ifndef MYGAMEPROJECT_APP_H
#define MYGAMEPROJECT_APP_H
#include <SDL3/SDL.h>
#include <string>
#include "LTexture.h"
#include <unordered_map>
#include "GameLoop.h"


struct Window {
    SDL_Window* sdl_window{ nullptr };
    std::string title;
    vec2<int> size{0,0};
};

class App {
public:
    App();
    ~App();

    bool Init(const std::string& windowTitle, int windowWidth, int windowHeight);

    LTexture* LoadTexture(const std::string &name, const std::string &path, bool colorKey, const RGB *rgb);

    void RenderTexture(const vec2<float> &pos, const std::string &texName);

    LTexture *GetOrLoadTexture(const std::string &name, const std::string &path, bool colorKey, RGB *rgb);

    void shutdown();
    SDL_Renderer* GetRenderer() const {return mRenderer;}

    [[nodiscard]] bool KeyJustPressed(const SDL_Keycode key) const{
        return mGameLoop->IsKeyDown(key) && !mGameLoop->WasKeyDown(key);
    }

    [[nodiscard]] bool KeyJustReleased(const SDL_Keycode key) const{
        return !mGameLoop->IsKeyDown(key) && mGameLoop->WasKeyDown(key);
    }

    GameLoop* gameLoop() const {
        return mGameLoop;
    };
private:
    GameLoop* mGameLoop;
    Window mWindow;
    SDL_Renderer* mRenderer{nullptr};
    std::unordered_map<std::string, LTexture*> mTextures;
};


#endif //MYGAMEPROJECT_APP_H