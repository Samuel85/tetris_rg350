#include "gameover.h"

GameOver::GameOver(){
  renderer = SDL_GetRenderer(window);
  if (loadImages() < 0){
    errorFlag = true;
  }
  if (loadAudio() < 0){
    errorFlag = true;
  }
  Mix_PlayMusic( music, 0);
}
GameOver::~GameOver(){
  SDL_DestroyTexture(backgroundTexture);
  shutdownAudio();
}
void GameOver::handleEvents(){
  SDL_Event event;
  while( SDL_PollEvent( &event ) ){
      if( event.type == SDL_QUIT ){
        nextGameState = EXIT;
      }
      else if( event.type == SDL_KEYDOWN ){
        switch ( event.key.keysym.sym ){
          case SDLK_RETURN:
            nextGameState = INTRO;
            break;
          default:
            break;
        }
      }
  }
}
void GameOver::logic(){
  SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
}
void GameOver::render(){
  SDL_RenderPresent(renderer);
}
int GameOver::loadImages(){
  SDL_Surface *background = SDL_LoadBMP("images/gameover.bmp");
  if (background == NULL){
      std::cout << "ERROR: Can't load background image" << std::endl;
      return -1;
  }
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
  SDL_FreeSurface(background);
  return 0;
}

void GameOver::shutdownAudio(){
  Mix_FreeMusic(music);
}
int GameOver::loadAudio(){
  music = Mix_LoadMUS("music/gameover.wav");

  if (music == NULL){
      return -1;
  }
  return 0;
}
