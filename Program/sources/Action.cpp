#include <cstdio> //DELETE

#include "../headers/Action.hpp"

#include <sstream>
#include <string>

NAction::Subject NAction::getDoer(const action& a){
  int f = (1<<7);
  return (NAction::Subject) (a&f);
}

NAction::Subject NAction::getTarget(const action& a){
  int f= 1<<6;
  return (NAction::Subject) ( a&f);
}

NAction::Action NAction::getAction(const action& a){
  int f = 1 + (1<<1) + (1<<2) + (1<<3) + (1<<4) + (1<<5);
  return (NAction::Action) ( a&f);
}

byte NAction::actionToByte(const NAction::Action& a, const NAction::Subject& doer, const NAction::Subject& target){
  return a+(doer<<7)+(target<<6);
}

byte NAction::targetToByte(const NAction::Subject& t){
  return t<<6;
}

byte NAction::doerToByte(const NAction::Subject& d){
  return d<<7;
}

std::string NAction::actionToString(const action& a){
  std::ostringstream oss;
  if(NAction::getDoer(a) == NAction::PLAYER1){
    oss << "Player1 - ";
  }else{
    oss << "Player2 - ";
  }
  switch( NAction::getAction(a) ){
  case NAction::ATTACK_LEFT: oss << "Attack Left"; break;
  case NAction::ATTACK_MIDDLE: oss << "Uppercut"; break;
  case NAction::ATTACK_RIGHT: oss << "Attack Right"; break;
  case NAction::DODGE_LEFT: oss << "Dodge Left"; break;
  case NAction::DODGE_MIDDLE: oss << "Dodge Middle"; break;
  case NAction::DODGE_RIGHT: oss << "Dodge Right"; break;
  case NAction::PAUSE: oss << "Pause"; break;
  default: oss << "Unknown"; break;
  }
  return oss.str();
}
