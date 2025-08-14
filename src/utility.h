//
// Created by host on 8/14/25.
//

#ifndef MYGAMEPROJECT_UTILITY_H
#define MYGAMEPROJECT_UTILITY_H
#include "SDL3/SDL_stdinc.h"

inline Uint8 dth(const int d) {
    return static_cast<Uint8>(d & 0xFF);
}

struct RGB {
    int r,g,b;
};
struct RGBA {
    int r,g,b,a;
};

template <typename T>
struct vec2 {
    T x, y;
};

#endif //MYGAMEPROJECT_UTILITY_H