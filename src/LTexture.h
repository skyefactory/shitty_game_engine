//
// Created by host on 8/7/25.
//

#ifndef MYGAMEPROJECT_LTEXTURE_H
#define MYGAMEPROJECT_LTEXTURE_H
#include <SDL3_image/SDL_image.h>
#include <string>
#include "utility.h"


class LTexture {
public:
    LTexture();
    ~LTexture();

    static constexpr float kOriginalSize = -1.f;

    bool loadFromFile(const std::string &path, SDL_Renderer *renderer);
    bool loadFromFileColorKey(const std::string &path, SDL_Renderer *renderer, int r, int g, int b);

    void destroy();

    void render(vec2<float> pos, vec2<float> scale, const SDL_FRect *clip, SDL_Renderer *renderer) const;

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] bool isLoaded() const;
private:
    SDL_Texture* mTexture;
    vec2<int> mSize;
};


#endif //MYGAMEPROJECT_LTEXTURE_H