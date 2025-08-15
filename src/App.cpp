//
// Created by host on 8/8/25.
//

#include "App.h"

App::App():mGameLoop{nullptr}, mWindow{}, mRenderer {nullptr}{}

App::~App() {
    shutdown();
}

bool App::Init(const std::string& windowTitle, const int windowWidth, const int windowHeight) {
    bool success{true};
    mWindow.size = {windowWidth, windowHeight};
    mWindow.title = windowTitle;

    auto* event = new SDL_Event();
    SDL_zero(*event);
    mGameLoop = new GameLoop(event);

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL Failed to initialize! Error information: %s \n", SDL_GetError());
        success = false;
    }
    else {
        if (SDL_CreateWindowAndRenderer(
                windowTitle.c_str(),
                windowWidth,
                windowHeight,
                0,
                &mWindow.sdl_window,
                &mRenderer) == false)
        {
            SDL_Log("Window could not be created! Error information: %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

LTexture* App::LoadTexture(const std::string &name, const std::string &path, const bool colorKey = false, const RGB* rgb = nullptr) {

    auto* texture = new LTexture();
    if (colorKey && rgb) {
        if (texture->loadFromFileColorKey(path, mRenderer, rgb->r, rgb->g, rgb->b)) {
            mTextures[name] = texture;
            delete rgb;
            return texture;
        }
    }
    else if (texture->loadFromFile(path, mRenderer)) {
        mTextures[name] = texture;
        return texture;
    }

    SDL_Log("Failed to load texture %s. Error information: %s,\n",path.c_str(), SDL_GetError());
    delete texture;
    return nullptr;
}

void App::RenderTexture(const vec2<float>& pos, const vec2<float>& scale, const SDL_FRect *clip, const std::string& texName) {
    auto it = mTextures.find(texName);
    if (it != mTextures.end()) {
        it->second->render(pos, scale, clip, mRenderer);
    } else {
        SDL_Log("RenderTexture: Texture '%s' not found in cache.", texName.c_str());
    }
}

LTexture* App::GetOrLoadTexture(const std::string& name, const std::string& path, bool colorKey, RGB* rgb) {
    auto it = mTextures.find(name);
    if (it != mTextures.end()) {
        return it->second;
    }
    return LoadTexture(name, path, colorKey, rgb);
}


void App::shutdown() {
    for (const auto& pair : mTextures) {
        delete pair.second;
        SDL_Log("Texture %s freed", pair.first.c_str());
    }
    mTextures.clear();

    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
        SDL_Log("Renderer destroyed");
    }

    if (mWindow.sdl_window) {
        SDL_DestroyWindow(mWindow.sdl_window);
        mWindow.sdl_window = nullptr;
    }
    SDL_Log("Window SDestroyed");

    if (mGameLoop) {
        delete mGameLoop;
        mGameLoop = nullptr;
    }

    SDL_Quit();
}
