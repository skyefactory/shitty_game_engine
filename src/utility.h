#ifndef MYGAMEPROJECT_UTILITY_H
#define MYGAMEPROJECT_UTILITY_H

#include "SDL3/SDL_stdinc.h"
#include <SDL3/SDL.h>
#include <vector>

// Forward declaration - to break circular dependency
class App;

// le classic utility file, full of bullshit and

//converts decimal color value to a hex color value for , SDL uses h
inline Uint8 dth(const int d) {
    return static_cast<Uint8>(d & 0xFF);
}

//struct for red,green,blue for color functions
struct RGB {
    int r,g,b;
};
//struct for red,green,blue,alpha for color functions
struct RGBA {
    int r,g,b,a;
};
//generic vec2 type for storing things like x,y pos or w,h scale, etc.
template <typename T>
struct vec2 {
    T x, y;
};
//generates a clipping rectangle for a sprite sheet, for use with a sprite sheet texture.
inline std::vector<SDL_FRect> generateClipRectForSpriteSheet(
    const int horizontalSpriteCount, // "width" of sprite sheet, i.e. how many sprites along the horizontal
    const int verticalSpriteCount, // "height" of sprite sheet, i.e. how many sprites along the vertical
    const int sizeOfSprite) // Size of each sprite on the sprite sheet
{
    std::vector<SDL_FRect> clipRectForSprite; // vector that stores a clipping rectangle for each sprite
    clipRectForSprite.reserve(horizontalSpriteCount * verticalSpriteCount); // calculates the total sprites

    //goes through each sprite and makes a clipping rectangle for them
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

// Function declaration - implementation in utility.cpp
void spriteClippingExample(const std::vector<SDL_FRect> &spriteClips, App &app);

// clear screen w/ color
void ClearScreen(SDL_Renderer *renderer, RGBA rgba);

#endif //MYGAMEPROJECT_UTILITY_H