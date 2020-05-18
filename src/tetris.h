#define BOARD_WIDTH     12
#define BOARD_HEIGHT    22
#define PIECE_WIDTH     5
#define PIECE_HEIGHT    5
#define NUMBER_ROTATIONS 4

#include <vector>

#ifndef __TETRIS_H__
#define __TETRIS_H__

enum TETROMINO{
  T,J,Z,O,S,L,I
};
const
char pieces[][5][5] = {
                      0,0,0,0,0,
                      0,0,1,0,0, //T UP
                      0,1,1,1,0,
                      0,0,0,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //T RIGHT
                      0,0,1,0,0,
                      0,0,1,1,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //T DOWN
                      0,0,0,0,0,
                      0,1,1,1,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //T LEFT
                      0,0,1,0,0,
                      0,1,1,0,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //J LEFT
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //J UP
                      0,1,0,0,0,
                      0,1,1,1,0,
                      0,0,0,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //J RIGHT
                      0,0,1,1,0,
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //J DOWN
                      0,0,0,0,0,
                      0,1,1,1,0,
                      0,0,0,1,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //Z H
                      0,0,0,0,0,
                      0,1,1,0,0,
                      0,0,1,1,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //Z V
                      0,0,0,1,0,
                      0,0,1,1,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //Z H
                      0,0,0,0,0,
                      0,1,1,0,0,
                      0,0,1,1,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //Z V
                      0,0,0,1,0,
                      0,0,1,1,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, // O
                      0,0,0,0,0,
                      0,1,1,0,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, // O
                      0,0,0,0,0,
                      0,1,1,0,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, // O
                      0,0,0,0,0,
                      0,1,1,0,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, // O
                      0,0,0,0,0,
                      0,1,1,0,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //s H
                      0,0,0,0,0,
                      0,0,1,1,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //s v
                      0,0,0,0,0,
                      0,0,1,0,0,
                      0,0,1,1,0,
                      0,0,0,1,0,

                      0,0,0,0,0, //s H
                      0,0,0,0,0,
                      0,0,1,1,0,
                      0,1,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //s v
                      0,0,0,0,0,
                      0,0,1,0,0,
                      0,0,1,1,0,
                      0,0,0,1,0,

                      0,0,0,0,0, //L R
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,1,1,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //L D
                      0,0,0,0,0,
                      0,1,1,1,0,
                      0,1,0,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //L LEFT
                      0,1,1,0,0,
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //L UP
                      0,0,0,1,0,
                      0,1,1,1,0,
                      0,0,0,0,0,
                      0,0,0,0,0,

                      0,0,1,0,0, //I V
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //I H
                      0,0,0,0,0,
                      1,1,1,1,0,
                      0,0,0,0,0,
                      0,0,0,0,0,

                      0,0,1,0,0, //I V
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,1,0,0,
                      0,0,0,0,0,

                      0,0,0,0,0, //I H
                      0,0,0,0,0,
                      1,1,1,1,0,
                      0,0,0,0,0,
                      0,0,0,0,0
                        };

class Tetris{
private:
    int x, y;
    int z, c;
    char innerBoard[BOARD_HEIGHT][BOARD_WIDTH];
    void checkForALine();
    void checkForGameOver();
    int randomGenerator();
    int getNextPiece();
    int getNewY();
public:
    Tetris();
    ~Tetris();

    void newGame();
    void rotate();
    void update();

    bool canMovePieceHorizontally(int xx, int yy, int zz);
    bool canMovePieceVertically(int xx, int yy, int zz);

    void moveHorizontally(int increment);
    void moveVertically(bool increaseScore);
    void movePreview();

    int  score;
    int  lines;
    int  nextPiece;
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    char previewBoard[BOARD_HEIGHT][BOARD_WIDTH];
    bool isGameOver;    
    int numberOfConsecutiveLines;
    
    std::vector<int> bag{T,J,Z,O,S,L,I};
    std::vector<int> bagState{1,1,1,1,1,1,1};
    int bagSize = 7;
};
#endif
