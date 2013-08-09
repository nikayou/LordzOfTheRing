/**
   Here we define a player, for the current game session : as in many fight games, we keep the number of victories
 */
#include "../headers/Player.hpp"

#include <cstdio> //delete
#include <sstream>
#include <string>

Player::Player(const std::string& name, CharacterPlayed * c){
  m_name = name;
  m_character = c;
  if(c == NULL){
    Character d;
    m_character = new CharacterPlayed(d);
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
