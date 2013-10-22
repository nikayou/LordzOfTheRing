#ifndef STATEHANDLER_HPP
#define STATEHANDLER_HPP

#include "../headers/GameState.hpp"

#include <vector>

class StateHandler{

public:
  void push(GameState *);
  void change(GameState *);
  void pop();
  void update();
  void render();
  bool empty();
  void deleteState(GameState *);
  void clear();

private:
  std::vector <GameState * > m_states;

};

#endif
