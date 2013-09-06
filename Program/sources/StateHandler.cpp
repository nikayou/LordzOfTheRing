#include "../headers/StateHandler.hpp"
#include "../headers/GameState.hpp"

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
      m_states.back()->deleteAll();
      delete m_states.back();
      m_states.pop_back();
      std::cout<<"deleted state"<<std::endl;
    }
  }
  m_states.push_back(s);
  m_states.back()->enter();
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
