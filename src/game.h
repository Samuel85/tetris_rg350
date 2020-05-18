#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <SDL_ttf.h>

#include "globals.h"
#include "gamestate.h"
#include "tetris.h"

enum Element {
	ELEMENT_DPAD_UP,
	ELEMENT_DPAD_DOWN,
	ELEMENT_DPAD_LEFT,
	ELEMENT_DPAD_RIGHT,
	ELEMENT_Y,
	ELEMENT_B,
	ELEMENT_X,
	ELEMENT_A,
	ELEMENT_SELECT,
	ELEMENT_START,
	ELEMENT_L1,
	ELEMENT_R1,
	ELEMENT_L2,
	ELEMENT_R2,
	ELEMENT_L3,
	ELEMENT_R3,
	ELEMENT_POWER,
#ifndef SDL_1
	ELEMENT_VOLDOWN,
	ELEMENT_VOLUP,
#endif	
	ELEMENT_COUNT
};

class Game:public GameState{
  public:
    Game();
    ~Game();
    void keyboardHandler();
    void joystickHandler();    
  
    void handleEvents();
    void logic();
    void render();
  private:
    SDL_Texture *backgroundTexture;
    SDL_Texture *brickTexture;
    SDL_Texture *brickPreviewTexture;
    
    SDL_Renderer *renderer;
    Tetris *tetris;
    bool pause;
    int x,y;
    
    SDL_Texture *scoreTexture, *linesTexture, *numbersTexture, *nextTexture, *pauseTexture;
    int scoreWidth, linesWidth, numbersWidth, nextWidth, pauseWidth;
    int scoreHeight,linesHeight,numbersHeight, nextHeight, pauseHeight;
    SDL_Rect tmpRect, srcRect;

    unsigned int initialTime, deltaTime, waitingTime;
    unsigned int initialTimeSound, deltaTimeSound, waitingTimeSound;

    Mix_Music *music;
    Mix_Chunk *explosionSound, *pauseSound, *moveSound;    
    TTF_Font *font;
  
    char    charLines[20], charScore[20];
    void    initTextTextures();
    void    print(char *text, int x, int y);
  
    void    playMusic();
    void    pauseMusic();
    void    toggleMusic();
    void    playExplosionSound();
    void    playPauseSound();
    void    playGameOverSound();
    void    playMoveSound();

    int     initVideo();
    void    shutdownVideo();

    int     initFonts();
    void    shutdownFonts();

    int     initAudio();
    void    shutdownAudio();

    int     loadImages();
    int     loadAudio();

};

#endif
