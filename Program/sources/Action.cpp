#include <cstdio> //DELETE

#include "../headers/Action.hpp"

#include <sstream>
#include <string>

Action::Subject Action::getDoer(const action& a){
  int f = (1<<7);
  return (Action::Subject) (a&f);
}

Action::Subject Action::getTarget(const action& a){
  int f= 1<<6;
  return (Action::Subject) ( a&f);
}

Action::Type Action::getType(const action& a){
  int f = 1 + (1<<1) + (1<<2) + (1<<3) + (1<<4) + (1<<5);
  return (Action::Type) ( a&f);
}

byte Action::actionToByte(const Action::Type& a, const Action::Subject& doer, const Action::Subject& target){
  return a+(doer<<7)+(target<<6);
}

byte Action::targetToByte(const Action::Subject& t){
  return t<<6;
}

byte Action::doerToByte(const Action::Subject& d){
  return d<<7;
}

std::string Action::actionToString(const action& a){
  std::ostringstream oss;
  if(Action::getDoer(a) == Action::PLAYER1){
    oss << "Player1 - ";
  }else{
    oss << "Player2 - ";
  }
  switch( Action::getType(a) ){
  case Action::ATTACK_LEFT: oss << "Attack Left"; break;
  case Action::ATTACK_MIDDLE: oss << "Uppercut"; break;
  case Action::ATTACK_RIGHT: oss << "Attack Right"; break;
  case Action::DODGE_LEFT: oss << "Dodge Left"; break;
  case Action::DODGE_MIDDLE: oss << "Dodge Middle"; break;
  case Action::DODGE_RIGHT: oss << "Dodge Right"; break;
  case Action::PAUSE: oss << "Pause"; break;
  default: oss << "Unknown"; break;
  }
  return oss.str();
}
