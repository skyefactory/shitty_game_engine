//
// Created by host on 8/13/25.
//

#include "GameLoop.h"

void GameLoop::PollEvents() {
    for (int i = 0; i < mPrevKeyboardState.size(); ++i) {
        mPrevKeyboardState[i] = mKeyboardState[i];
    }

    while (SDL_PollEvent(mEvent)) {
        if (mEvent->type == SDL_EVENT_QUIT) {
            mQuit = true;
        }
    }

    int numKeys = 0;
    mKeyboardState = SDL_GetKeyboardState(&numKeys);
}

GameLoop::~GameLoop() {
    delete mEvent;
}

GameLoop::GameLoop(SDL_Event *event): mEvent(event) {
    int numKeys = 0;
    mKeyboardState = SDL_GetKeyboardState(&numKeys);
    mPrevKeyboardState.resize(numKeys);
    for (int i = 0; i < numKeys; ++i) {
        mPrevKeyboardState[i] = mKeyboardState[i];
    }
}

bool GameLoop::WindowShouldClose() const {
    return mQuit;
}

