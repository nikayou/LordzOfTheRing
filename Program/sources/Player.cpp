#include "../headers/Player.hpp"

#include <cstdio> //delete
#include <sstream>
#include <string>

Player::Player(const std::string& name, CharacterPlayed * c){
  m_name = name;
  printf("player : character = (before) %p\n", m_character);
  m_character = c;
  printf("player : character = (mid) %p (parameter is %p)\n", m_character, c);
  if(c == NULL){
    Character d;
    m_character = new CharacterPlayed(d);
    //e.fromCharacter(d);
    //m_character = &e;
  printf("player : character = (after) %p\n", m_character);
  }
  m_victories = 0;
  m_points = 0;
}

Player::~Player(){
  delete m_character;
}

void Player::manage(){
  m_character->manage();
}

std::string Player::toString(){
  std::ostringstream oss;
  oss<<"Player \""<< m_name << "\""<<std::endl;
  oss<<"Character : "<< m_character << std::endl;
  oss<<"Victories = "<< m_victories << std::endl;
  oss<<"Points = "<< m_points << std::endl;
  return oss.str();
}
