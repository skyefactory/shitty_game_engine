//
// Created by host on 8/13/25.
//

#ifndef MYGAMEPROJECT_GAMELOOP_H
#define MYGAMEPROJECT_GAMELOOP_H
#include <SDL3/SDL.h>
#include <vector>
class GameLoop {
public:
    ~GameLoop();
    explicit GameLoop(SDL_Event* event);
    void PollEvents();
    [[nodiscard]] bool WindowShouldClose() const;

    [[nodiscard]] const bool* keyboardState() const {
        return mKeyboardState;
    }
    std::vector<bool>* prevKeyboardState() {
        return &mPrevKeyboardState;
    }

    [[nodiscard]] bool IsKeyDown(const SDL_Keycode key) const {
        const SDL_Scancode sc = SDL_GetScancodeFromKey(key, nullptr);
        return mKeyboardState[sc];
    }

    [[nodiscard]] bool WasKeyDown(const SDL_Keycode key) const{
        const SDL_Scancode sc = SDL_GetScancodeFromKey(key, nullptr);
        return mPrevKeyboardState[sc];
    }

    void Quit() {
        mQuit = true;
    }

private:
    SDL_Event* mEvent = nullptr;
    bool mQuit = false;
    const bool* mKeyboardState = nullptr;
    std::vector<bool> mPrevKeyboardState;
};



#endif //MYGAMEPROJECT_GAMELOOP_H