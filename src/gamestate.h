#ifndef GAMESTATE_H_
#define GAMESTATE_H_

class GameState {
    public:
      virtual void handleEvents() = 0;
      virtual void logic() = 0;
      virtual void render() = 0;
      virtual ~GameState(){};
};

#endif
