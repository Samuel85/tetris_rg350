#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "globals.h"
#include "gamestate.h"

class GameOver:public GameState{
  public:
    GameOver();
    ~GameOver();
    int loadImages();
    void handleEvents();
    void logic();
    void render();
  private:
    SDL_Texture *backgroundTexture;
    SDL_Renderer *renderer;

    Mix_Music *music;
    int loadAudio();
    void shutdownAudio();
};

#endif
