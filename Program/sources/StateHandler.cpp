#include "../headers/StateHandler.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/MatchState.hpp"

#include <iostream> //delete
#include <vector>

void StateHandler::push(GameState * s){
  m_states.push_back(s);
  m_states.back()->enter();
}

void StateHandler::change(GameState * s){
  GameState * g = NULL;
  if(!m_states.empty() ){
    if(m_states.back()->getID().compare( s->getID() ) == 0){
      return;
    }
    if(m_states.back()->exit() ){
      g = m_states.back();
      m_states.pop_back();
    }
  }
  m_states.push_back(s);
  m_states.back()->enter();
  if(g != NULL){
    g->deleteAll(); // useless ?
    if( ! g->getID().compare("MAIN_MENU") ){
      delete (MainMenuState *)g;
      return;
    }
    if( ! g->getID().compare("CHAR_MENU") ){
      delete (CharacterState *)g;
      return;
    }
    if( ! g->getID().compare("MATCH") ){
      delete (MatchState *)g;
      return;
    }
  }
}

void StateHandler::pop(){
  if(!m_states.empty() ){
    if(m_states.back() ->exit() ){
      delete m_states.back();
      m_states.pop_back();
    }
  }
}

void StateHandler::update(){
  if(!m_states.empty() )
    m_states.back()->update();
}

void StateHandler::render(){
  if(!m_states.empty() )
    m_states.back()->render();
}
