#include "tetris.h"
#include <iostream>
#include <random>
#include <math.h>

Tetris::Tetris(){
    newGame();
}

Tetris::~Tetris(){
}

void Tetris::newGame(){
    for (int m=0;m<BOARD_HEIGHT;m++)
        for (int n=0;n<BOARD_WIDTH;n++){
            board[m][n] = 0;
            innerBoard[m][n] = 0;
            previewBoard[m][n] = 0;
        }
    score = 0;
    lines =0;
    numberOfConsecutiveLines = 0;
    isGameOver = false;
    nextPiece = randomGenerator();
    c = randomGenerator();
    x = (BOARD_WIDTH >> 1) - 1;
    y = getNewY();    
    z = 0;
    update();
    movePreview();
}

int Tetris::getNewY(){
  int yy = 0;
  // T,J,Z,O,S,L,I
  switch (c) {
    case T: yy = -1; break;
    case J: yy = -1; break;
    case Z: yy = -2; break;
    case O: yy = -2; break;
    case S: yy = -2; break;
    case L: yy = -1; break;
    case I: yy = 0; break;
  }
  return yy;
}

void Tetris::update(){
    for (int m=0;m<BOARD_HEIGHT;m++){
        for (int n=0;n<BOARD_WIDTH;n++){
            board[m][n] = innerBoard[m][n];
        }
    }

    for (int m=0;m<PIECE_HEIGHT;m++){
        for (int n=0;n<PIECE_WIDTH;n++){
            if (pieces[NUMBER_ROTATIONS*c+z][m][n] != 0){
                board[y+m][x+n] = (char)(c + 1);
            }
        }
    }
    checkForGameOver();
}
void Tetris::rotate(){
    const char numberOfBits = 2;
    const char mask = (1 << numberOfBits)-1;

    // check all possible rotations if the nextone isn't possible
    for (int i=1;i<NUMBER_ROTATIONS+1;i++){
      char zz = (char) z + i;
      zz = (char) zz & mask;

      if (canMovePieceHorizontally(x,y,zz)){
          z = zz;
          movePreview();
          update();
          checkForALine();
          return;
      }
    }
}

void Tetris::moveHorizontally(int increment){
    if (isGameOver)
        return;
    if (canMovePieceHorizontally(x + increment, y, z)){
        x = x + increment;
        movePreview();
        update();
        checkForALine();
    }
}
void Tetris::moveVertically(bool increaseScore){
    if (isGameOver)
        return;

    if (increaseScore)
        score++;

    if (canMovePieceVertically(x, y+1, z)){
        y++;
        movePreview();
    }else{
        // settle piece in the inner board
        for (int m=0;m<PIECE_HEIGHT;m++){
            for (int n=0;n<PIECE_WIDTH;n++){
                if (pieces[NUMBER_ROTATIONS*c+z][m][n] != 0){
                    innerBoard[y+m][x+n] = c+1;
                }
            }
        }
        checkForGameOver();
        c = getNextPiece();
        x = (BOARD_WIDTH >> 1) - 1;
        y = getNewY();
        z = 0;
        if (!canMovePieceVertically(x, y, z)){
          isGameOver = true;
        }
    }
    update();
    checkForALine();
}
void Tetris::movePreview(){
    // clear the preview
    for (int m=0;m<BOARD_HEIGHT;m++){
        for (int n=0;n<BOARD_WIDTH;n++){
          previewBoard[m][n] = 0;
        }
    }
    
    int yy = y;
    while(canMovePieceVertically(x, yy+1, z)){
        yy++;
    }

    // settle piece in the inner board
    for (int m=0;m<PIECE_HEIGHT;m++){
        for (int n=0;n<PIECE_WIDTH;n++){
            if (pieces[NUMBER_ROTATIONS*c+z][m][n] != 0){
                if (yy+m >=BOARD_HEIGHT) return;
                previewBoard[yy+m][x+n] = c+1;                
            }
        }
    }
}
bool Tetris::canMovePieceHorizontally(int xx, int yy, int zz){
    for (int m=0;m<PIECE_HEIGHT;m++){
        for (int n=0;n<PIECE_WIDTH;n++){
            if (pieces[NUMBER_ROTATIONS*c+zz][m][n] != 0){
                int j = yy + m;
                int i = xx + n;
                // break if the position is outside of the board
                if ((i > BOARD_WIDTH -1) || i < 0){
                    return false;
                }
                // if the space is already occupied
                if (innerBoard[j][i] != 0){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Tetris::canMovePieceVertically(int xx, int yy, int zz){
    for (int m=0;m<PIECE_HEIGHT;m++){
        for (int n=0;n<PIECE_WIDTH;n++){
            if (pieces[NUMBER_ROTATIONS*c+zz][m][n] != 0){
                int j = yy + m;
                int i = xx + n;
                // break if the space is already occupied
                if (innerBoard[j][i] != 0 || j == BOARD_HEIGHT){
                    return false;
                }
            }
        }
    }
    return true;
}
void Tetris::checkForALine(){
    for (int m=0; m < BOARD_HEIGHT; m++){
        char sum = 0;
        for (int n=0; n < BOARD_WIDTH; n++){
            if (innerBoard[m][n] != 0){
            sum++;
            }
        }
        if (sum == BOARD_WIDTH){
            // move lines
            for (int b=m;b>0; b--)
                for (int a=0;a<BOARD_WIDTH;a++){
                    innerBoard[b][a] = innerBoard[b-1][a];
                }
            for (int a=0;a<BOARD_WIDTH;a++){
                innerBoard[0][a] = 0;
            }

            lines++;
            numberOfConsecutiveLines++;
            //update board
            for (int m=0;m<BOARD_HEIGHT;m++){
                for (int n=0;n<BOARD_WIDTH;n++){
                    board[m][n] = innerBoard[m][n];
                }
            }
        }
    }
}
//Random bag
int Tetris::randomGenerator(){    
    if (bagSize <= 0){
        for (int i=0;i<7;i++){
            bagState[i] = 1;
        }
        bagSize = 7;
    }
    // random shuffle from the bag
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(0, 6);
    
    int i = round(distr(generator));
    
    while(!bagState[i]){
        i = round(distr(generator));
    }
    int ret = bag[i];
    bagState[i] = 0;
    bagSize--;
        
    return ret;
    
}

int Tetris::getNextPiece(){
    int tmp = randomGenerator();
    int tmp2 = nextPiece;
    nextPiece = tmp;
    return tmp2;
}

void Tetris::checkForGameOver(){
    char sum = 0;
    for (int n=0;n<BOARD_WIDTH;n++){
        sum = sum + innerBoard[0][n];
    }
    if (sum > 0){isGameOver= true;}
    else {isGameOver = false;}
}
