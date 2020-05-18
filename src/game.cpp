#include "game.h"

Game::Game(){
  renderer = SDL_GetRenderer(window);
  if (loadImages() < 0){
    errorFlag = true;
  }
  if (initFonts() < 0){
    errorFlag = true;
  }
  if (loadAudio() < 0){
    errorFlag = true;
  }
  pause = false;
  x = 100;
  y = 9;
  tetris = new Tetris();
  playMusic();
  initialTime = SDL_GetTicks();
  deltaTime = 0;
  waitingTime = 0;
  initialTimeSound = SDL_GetTicks();
  deltaTimeSound = 0;
  waitingTimeSound = 0;
}
Game::~Game(){
  shutdownFonts();
  shutdownVideo();
  shutdownAudio();
}
int  Game::initFonts(){  
  if (TTF_Init() < 0){
    return -1;
  }
  font = TTF_OpenFont("fonts/arial.ttf", 20);
  initTextTextures();
  return 0;
}
void Game::shutdownFonts(){
  TTF_CloseFont(font);
  TTF_Quit();
}
void Game::shutdownAudio(){
  Mix_FreeMusic(music);
  Mix_FreeChunk(explosionSound);
  Mix_FreeChunk(pauseSound);
  Mix_FreeChunk(moveSound);
}
int  Game::loadAudio(){
  music = Mix_LoadMUS("music/Dubstep-loop-150-bpm.wav");
  explosionSound = Mix_LoadWAV("music/Explosion+3.wav");
  pauseSound = Mix_LoadWAV("music/pause.wav");
  moveSound = Mix_LoadWAV("music/heat-vision.wav");
  if (music == NULL || explosionSound == NULL || pauseSound == NULL){
      return -1;
  }
  return 0;
}
void Game::playMusic(){
  Mix_PlayMusic( music, -1);
}
void Game::playExplosionSound(){
  Mix_PlayChannel( -1, explosionSound, 0);
}
void Game::playPauseSound(){
  Mix_PlayChannel( -1, pauseSound, 0);
}
void Game::playGameOverSound(){
  Mix_PlayChannel( -1, explosionSound, 0);
}
void Game::playMoveSound(){
  Mix_PlayChannel( -1, moveSound, 0);
}
void Game::toggleMusic(){
  if (Mix_PausedMusic()){
    Mix_ResumeMusic();
  }else{
    Mix_PauseMusic();
  }
}
void Game::pauseMusic(){
  if (!Mix_PausedMusic()){
      Mix_PauseMusic();
  }
}
void Game::shutdownVideo(){
  SDL_DestroyTexture(backgroundTexture);
  SDL_DestroyTexture(brickTexture);
  SDL_DestroyTexture(brickPreviewTexture);
  SDL_DestroyTexture(scoreTexture);
  SDL_DestroyTexture(linesTexture);
  SDL_DestroyTexture(numbersTexture);  
  SDL_DestroyTexture(nextTexture);  
}
int  Game::loadImages(){
  SDL_Surface *background = SDL_LoadBMP("images/background.bmp");
  if (background == NULL){
      std::cout << "ERROR: Can't load background image" << std::endl;
      return -1;
  }
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
  SDL_Surface *brick = SDL_LoadBMP("images/cubes.bmp");
  if (brick == NULL){
    std::cout << "ERROR: Can't load brick image" << std::endl;
    return -1;
  }
  brickTexture = SDL_CreateTextureFromSurface(renderer, brick);
  brickPreviewTexture = SDL_CreateTextureFromSurface(renderer, brick);
  SDL_SetTextureBlendMode( brickPreviewTexture, SDL_BLENDMODE_BLEND );
  SDL_SetTextureAlphaMod( brickPreviewTexture, 80 );

  SDL_FreeSurface(background);
  SDL_FreeSurface(brick);
  return 0;
}
void Game::initTextTextures(){    
  const SDL_Color color = { 255, 255, 255 };
  SDL_Surface *score = TTF_RenderText_Solid(font, "Score", color);
  SDL_Surface *lines = TTF_RenderText_Solid(font, "Lines", color);
  SDL_Surface *numbers = TTF_RenderText_Solid(font, "0123456789", color);
  SDL_Surface *next = TTF_RenderText_Solid(font, "Next", color);
  SDL_Surface *pause = TTF_RenderText_Solid(font, "Pause", color);
  
  scoreWidth = score->w;
  scoreHeight = score->h;
  linesWidth = lines->w;
  linesHeight = lines->h;
  numbersWidth = numbers->w;
  numbersHeight = numbers->h;
  nextWidth = next->w;
  nextHeight = next->h;
  pauseWidth = pause->w;
  pauseHeight= pause->h; 
  
  scoreTexture = SDL_CreateTextureFromSurface(renderer, score);
  linesTexture = SDL_CreateTextureFromSurface(renderer, lines);
  numbersTexture = SDL_CreateTextureFromSurface(renderer, numbers);
  nextTexture = SDL_CreateTextureFromSurface(renderer, next);
  pauseTexture = SDL_CreateTextureFromSurface(renderer, pause);
  
  SDL_FreeSurface(score);
  SDL_FreeSurface(lines);
  SDL_FreeSurface(numbers);
  SDL_FreeSurface(next);
  SDL_FreeSurface(pause);
}
void Game::print(char *text, int x, int y){
  char *c = text;
  int dx = numbersWidth/10;  
  int i=0;
  
  while (*c != '\0'){
    int j = *c - '0';
    srcRect = { dx*j, 0, dx, numbersHeight };
    tmpRect = { x + dx*i, y, dx, numbersHeight };
    SDL_RenderCopy(renderer, numbersTexture, &srcRect, &tmpRect);
    i++;
    c++;
  }
}
void Game::handleEvents(){  
  if (tetris->numberOfConsecutiveLines > 0){
    deltaTimeSound = SDL_GetTicks() - initialTimeSound;
    if (waitingTimeSound >= 200 ){
      playExplosionSound();
      waitingTimeSound = 0;
      initialTimeSound = SDL_GetTicks();
      tetris->numberOfConsecutiveLines = tetris->numberOfConsecutiveLines - 1;
    }else {waitingTimeSound =+ deltaTimeSound;}
  }

  SDL_Event event;
  while( SDL_PollEvent( &event ) ){
    if( event.type == SDL_QUIT ){nextGameState = EXIT;}
    else if( event.type == SDL_KEYDOWN ){
      switch( event.key.keysym.sym ){
        case SDLK_1:
        tetris->newGame();
        playMusic();
        break;
      case SDLK_2:
        playExplosionSound();
        break;
      case SDLK_RETURN:
        if (!tetris->isGameOver){
          toggleMusic();
          playPauseSound();
          pause = !pause;
        }
        break;
      case SDLK_LEFT:
        tetris->moveHorizontally(-1);
      break;
        case SDLK_RIGHT:
        tetris->moveHorizontally(+1);
        break;
      case SDLK_UP:
        if (!tetris->isGameOver){
          playMoveSound();
          tetris->rotate();
        }
        break;
      case SDLK_LSHIFT: //A-Button
        if (!tetris->isGameOver){
          playMoveSound();
          tetris->rotate();
        }
        break;
      case SDLK_DOWN:
        tetris->moveVertically(true);
        break;
      case SDLK_LALT: //B-Button
        tetris->moveVertically(true);
        break;
      default:
        break;
      }
    }
  }
}
void Game::logic(){
  if (!pause){
    deltaTime = SDL_GetTicks() - initialTime;
    if (waitingTime >= 500 ){
      tetris->moveVertically(false);
      waitingTime = 0;
      initialTime = SDL_GetTicks();
    }
    else {
      waitingTime =+ deltaTime;
    }
  }
  if (tetris->isGameOver){
    playGameOverSound();
    SDL_Delay(1000);
    nextGameState = GAMEOVER;
  }  
}
void Game::render(){
  if (pause){
    tmpRect = { 125, 100, pauseWidth, pauseHeight };
    SDL_RenderCopy(renderer, pauseTexture, NULL, &tmpRect);
  }  
  else{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    
    sprintf(charScore, "%d", tetris->score);
    sprintf(charLines, "%d", tetris->lines);
  
    tmpRect = { 240, 10, scoreWidth, scoreHeight };
    SDL_RenderCopy(renderer, scoreTexture, NULL, &tmpRect);
    
    tmpRect = { 240, 75, linesWidth, linesHeight };
    SDL_RenderCopy(renderer, linesTexture, NULL, &tmpRect);
    
    tmpRect = { 240, 140, nextWidth, nextHeight };
    SDL_RenderCopy(renderer, nextTexture, NULL, &tmpRect);
    
    print(&charScore[0], 240, 33);
    print(&charLines[0], 240, 98);

    for (int j=0;j<BOARD_HEIGHT;j++){
      for (int i=0;i<BOARD_WIDTH;i++){
        // draw board
        if (tetris->board[j][i] != 0){
          int c = (int) (tetris->board[j][i] - 1);
          SDL_Rect srcrect = { c*20, 0, 20, 20 };
          SDL_Rect dstrect = { x + i*10, y + j*10, 10, 10 };
          SDL_RenderCopy(renderer, brickTexture, &srcrect, &dstrect);
        }
        // preview board
        if (tetris->previewBoard[j][i] != 0){
          int c = (int) (tetris->previewBoard[j][i] - 1);
          SDL_Rect srcrect = { c*20, 0, 20, 20 };
          SDL_Rect dstrect = { x + i*10, y + j*10, 10, 10 };
          SDL_RenderCopy(renderer, brickPreviewTexture, &srcrect, &dstrect);
        }
      }
    }
    // draw the next piece
    for (int j=0;j<PIECE_HEIGHT;j++){
      for (int i=0;i<PIECE_WIDTH;i++){
        if (pieces[NUMBER_ROTATIONS*tetris->nextPiece][j][i] != 0){
          int c = (int) tetris->nextPiece;
          SDL_Rect srcrect = { c*20, 0, 20, 20 };
          SDL_Rect dstrect = { NEXT_PIECE_X + i*10, NEXT_PIECE_Y + j*10, 10, 10 };
          SDL_RenderCopy(renderer, brickTexture, &srcrect, &dstrect);
        }
      }
    }
  }
  SDL_RenderPresent(renderer);
}