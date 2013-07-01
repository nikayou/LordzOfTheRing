#include "../headers/Player.hpp"

#include <sstream>
#include <string>

Player::Player(const std::string& name = "Player", Character * chara = NULL){
  m_name = name;
  m_character = chara;
  m_victories = 0;
  m_points = 0;
}

Player::~Player(){
}

std::string Player::toString(){
  std::ostringstream oss;
  oss<<"Player \""<< m_name << "\""<<std::endl;
  oss<<"Character : "<< m_character << std::endl;
  oss<<"Victories = "<< m_victories << std::endl;
  oss<<"Points = "<< m_points << std::endl;
  return oss.str();
}