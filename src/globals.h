#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define WIDTH    320
#define HEIGHT   240
#define WINDOW_TITLE    "Tetris"
#define MINIMUM_FRAME_TIME 60
#define NEXT_PIECE_X    235
#define NEXT_PIECE_Y    165


#include <SDL.h>

extern int  currentGameState;
extern int  nextGameState;
extern bool errorFlag;
extern int  zoom;
extern bool fullscreen;
extern bool enableJoystick;
extern int  WINDOW_WIDTH;
extern int  WINDOW_HEIGHT;

extern SDL_Window  *window;

enum STATES{
  EXIT,
  INTRO,
  GAMING,
  GAMEOVER
};

#endif
