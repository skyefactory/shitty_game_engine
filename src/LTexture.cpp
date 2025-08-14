//
// Created by host on 8/7/25.
//
#include "LTexture.h"

LTexture::LTexture():
    mTexture{nullptr},
    mSize{0,0}
{}

LTexture::~LTexture() {
    destroy();
}
bool LTexture::loadFromFile(const std::string& path, SDL_Renderer* renderer) {
    destroy();

    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! Error information: %s\n", path.c_str(), SDL_GetError());
    }
    else {
        if (mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); mTexture==nullptr) {
            SDL_Log("Unable to create texture from loaded image pixels! Error information: %s\n", SDL_GetError());
        }
        else {
            mSize = {loadedSurface->w, loadedSurface->h};
        }
        SDL_DestroySurface(loadedSurface);
    }
    return mTexture != nullptr;
}

bool LTexture::loadFromFileColorKey(const std::string &path, SDL_Renderer *renderer, int r, int g, int b) {
    destroy();

    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! Error information: %s\n", path.c_str(), SDL_GetError());
    }
    else {
        //Color key image
        if( SDL_SetSurfaceColorKey( loadedSurface, true, SDL_MapSurfaceRGB( loadedSurface, dth(r), dth(g), dth(b) ) ) == false )
        {
            SDL_Log( "Unable to color key! SDL error: %s", SDL_GetError() );
        }
        else
        {
            //Create texture from surface
            if( mTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); mTexture == nullptr )
            {
                SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                mSize.x = loadedSurface->w;
                mSize.y = loadedSurface->h;
            }
        }

        //Clean up loaded surface
        SDL_DestroySurface( loadedSurface );
    }
    return mTexture != nullptr;
}

void LTexture::destroy() {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mSize = {0, 0};
}

void LTexture::render(const vec2<float> pos, SDL_Renderer* renderer) const {
    const SDL_FRect dstRect{pos.x, pos.y, static_cast<float>(mSize.x), static_cast<float>(mSize.y)};
    SDL_RenderTexture(renderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth() const {return mSize.x;}
int LTexture::getHeight() const {return mSize.y;}
bool LTexture::isLoaded() const {return mTexture != nullptr;}
