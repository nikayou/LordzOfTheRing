#include "../headers/Player.hpp"


Player::Player(const std::string& name = "Player", Character * chara = NULL){
  m_name = name;
  m_character = chara;
  m_victories = 0;
  m_points = 0;
}

int main(){
	return 0;
}
