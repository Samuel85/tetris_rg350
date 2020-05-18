#include "intro.h"
#include "globals.h"

Intro::Intro(){
  renderer = SDL_GetRenderer(window);
  if (loadImages() < 0){
    errorFlag = true;
  }
}
Intro::~Intro(){
  SDL_DestroyTexture(backgroundTexture);
}
void Intro::handleEvents(){
  SDL_Event event;
  while( SDL_PollEvent( &event ) ){
    if( event.type == SDL_QUIT ){
      nextGameState = EXIT;
    }
    else if( event.type == SDL_KEYDOWN ){
      switch ( event.key.keysym.sym ){
        case SDLK_RETURN:
          nextGameState = GAMING;
          break;
        default:
          break;
      }
    }
  }
}
void Intro::logic(){

}
void Intro::render(){
  SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(200);
}
int Intro::loadImages(){
  SDL_Surface *background = SDL_LoadBMP("images/intro.bmp");
  if (background == NULL){
      std::cout << "Puta!!!" << std::endl;
      return -1;
  }
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
  SDL_FreeSurface(background);
  return 0;
}
