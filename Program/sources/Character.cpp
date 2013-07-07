#include "../headers/Character.hpp"
#include "../headers/CharacterPlayed.hpp"

#include <sstream>
#include <string>

Character::Character(){
}

Character::Character(
		     const unsigned short& h = 100, 
		     const Stats::stats& r = Stats::MEDIUM, 
		     const Stats::stats& a = Stats::MEDIUM, 
		     const Stats::stats& sta = Stats::MEDIUM){
  m_health = h;
  m_resistance = r;
  m_attack = a;
  m_stamina = sta;
}

Character::~Character(){}


std::string Character::toString(){
  std::ostringstream oss;
  oss<<"Character "<< std::endl;
  oss<<"Health = "<< m_health << std::endl;
  oss<<"Resistance (L/H) = "<< m_resistance << std::endl;
  oss<<"Strength (L/H) = "<< m_attack << std::endl;
  oss<<"Stamina = "<< m_stamina << std::endl;
  return oss.str();
}
