#include <cstdio> //DELETE

#include "../headers/Action.hpp"

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
