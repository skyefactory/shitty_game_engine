#ifndef MYGAMEPROJECT_GAMELOOP_H
#define MYGAMEPROJECT_GAMELOOP_H

#include <SDL3/SDL.h>
#include <vector>

/*
 * This class manages the main update loop, and actions that should occur within it, such as event polling,
 * keyboard states, and provides a method to Quit the app
 */
class GameLoop {
public:
    ~GameLoop();
    explicit GameLoop(SDL_Event* event);

    //Updates mKeyboardState, mPrevKeyboardState, and mEvent
    void PollEvents();

    //Used to monitor when the program should quit, used in main like while(!WindowShouldClose()){game loop}
    [[nodiscard]] bool WindowShouldClose() const;

    //getter
    [[nodiscard]] const bool* keyboardState() const {
        return mKeyboardState;
    }
    //getter
    std::vector<bool>* prevKeyboardState() {
        return &mPrevKeyboardState;
    }

    //Returns if a key is down in this frame
    [[nodiscard]] bool IsKeyDown(const SDL_Keycode key) const {
        const SDL_Scancode sc = SDL_GetScancodeFromKey(key, nullptr);
        return mKeyboardState[sc];
    }
    //returns if a key was down in the last frame
    [[nodiscard]] bool WasKeyDown(const SDL_Keycode key) const{
        const SDL_Scancode sc = SDL_GetScancodeFromKey(key, nullptr);
        return mPrevKeyboardState[sc];
    }
    //manually quit the program, sets WindowShouldClose() to true.
    void Quit() {
        mQuit = true;
    }

private:
    SDL_Event* mEvent = nullptr; // SDL events
    bool mQuit = false; // Flag to quit
    const bool* mKeyboardState = nullptr; // keyboard state of the current frame
    std::vector<bool> mPrevKeyboardState; // keyboard state of the previous frame
};



#endif //MYGAMEPROJECT_GAMELOOP_H