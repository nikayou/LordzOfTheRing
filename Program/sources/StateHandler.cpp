#include "../headers/StateHandler.hpp"
#include "../headers/Game.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/MatchState.hpp"
#include "../headers/OptionState.hpp"
#include "../headers/SettingsState.hpp"
#include "../headers/RoundEndState.hpp"

#include <vector>

bool StateHandler::empty(){
  return m_states.empty();
}

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
      Game::getInstance()->setUpdating(false);
      g = m_states.back();
      m_states.pop_back();
    }
  }
  m_states.push_back(s);
  m_states.back()->enter();
  deleteState(g);
}


void StateHandler::pop(){
  if(!m_states.empty() ){
    GameState * g = m_states.back();
    Game::getInstance()->setUpdating(false);
    if(g ->exit() ){
      m_states.pop_back();
      deleteState(g);
    }
  }
}

void StateHandler::update(){
  if(Game::getInstance()->updating() && !m_states.empty() )
    m_states.back()->update();
}

void StateHandler::deleteState( GameState * g){
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
    if( ! g->getID().compare("ROUND") ){
      delete (RoundEndState *)g;
      return;
    }
    if( ! g->getID().compare("SETTINGS") ){
      delete (SettingsState *)g;
      return;
    }
    if( ! g->getID().compare("OPTION_MENU") ){
      delete (OptionState *)g;
      return;
    }
  }
}

void StateHandler::render(){
  if(Game::getInstance()->updating() && !m_states.empty() )
    m_states.back()->render();
}
