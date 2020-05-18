#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "globals.h"
#include "gamestate.h"
class System {
    private:
        SDL_Renderer *renderer;
        GameState *state;
        int     initAudio();
        void    shutdownAudio();
        
        int     initVideo();
        void    shutdownVideo();
    public:
        System();
        ~System();

        void    mainLoop();
        void    changeState();
        void    updateScreen();

};

#endif
