#include "system.h"
#include "intro.h"
#include "game.h"
#include "gameover.h"
#include "globals.h"
#include "gamestate.h"

int currentGameState;
int nextGameState;
SDL_Window *window;
bool errorFlag;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;

System::System(){
  WINDOW_WIDTH  = zoom*WIDTH;
  WINDOW_HEIGHT = zoom*HEIGHT;

  currentGameState = INTRO;
  nextGameState = INTRO;
  errorFlag = false;

  if (initVideo()<0){
      nextGameState = EXIT;
      errorFlag = true;
  }
  if (initAudio()<0){
      nextGameState = EXIT;
      errorFlag = true;
  }
}
System::~System(){
  shutdownVideo();
  shutdownAudio();
}
void System::mainLoop(){
  state = new Intro();

  while( currentGameState != EXIT){
    unsigned int frameTime = SDL_GetTicks();
    state->handleEvents();
    state->logic();
    state->render();
    changeState();

    //cap the frame rate
    if (SDL_GetTicks() - frameTime < MINIMUM_FRAME_TIME){
        SDL_Delay(MINIMUM_FRAME_TIME - (SDL_GetTicks() - frameTime));
    }
  }
}
int System::initVideo(){
  SDL_Init(SDL_INIT_VIDEO);
  Uint32 flags = SDL_WINDOW_SHOWN;
  
  if (fullscreen){
    flags = flags | SDL_WINDOW_FULLSCREEN;
  }  
  window = SDL_CreateWindow(WINDOW_TITLE, 0, 0,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            flags);
  if (window == NULL){
      std::cout << "ERROR: Could not create window: " << SDL_GetError() << std::endl;
      return -1;
  }

  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  if( renderer == NULL ){
      std::cout << "ERROR: Could not create renderer: " << SDL_GetError() << std::endl;
      return -1;
  }

  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  return 0;
}
void System::shutdownVideo(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
int System::initAudio(){
  if (SDL_Init(SDL_INIT_AUDIO) < 0){
		return -1;
  }
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		return -1;
  }
  return 0;
}
void System::shutdownAudio(){
  Mix_CloseAudio();
}
void System::changeState(){
  if (errorFlag){
    nextGameState = EXIT;
  }
  if (nextGameState != currentGameState){
    currentGameState = nextGameState;
    delete state;
    switch (currentGameState) {
      case EXIT:
        break;
      case INTRO:
        state = new Intro();
        break;
      case GAMING:
        state = new Game();
        break;
      case GAMEOVER:
        state = new GameOver();
        break;
      default:
        break;
    }
  }
}
