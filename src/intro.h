#ifndef INTRO_H_
#define INTRO_H_

#include <iostream>
#include <SDL.h>
#include "globals.h"
#include "gamestate.h"

class Intro : public GameState {
    public:
        Intro();
        ~Intro();
        int loadImages();
        void handleEvents();
        void logic();
        void render();
    private:
        SDL_Texture *backgroundTexture;
        SDL_Renderer *renderer;
          //SDL_Surface *message;
};

#endif
