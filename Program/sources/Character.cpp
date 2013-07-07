#include "../headers/Character.hpp"
#include "../headers/CharacterPlayed.hpp"

#include <sstream>
#include <string>


namespace Stats{

  Stats::stats fromString(const std::string& s){
    if(s.compare("medium") != 0 ){
      return Stats::MEDIUM;
    }
    if(s.compare("strong") != 0 ){
      return Stats::STRONG;
    }
    if(s.compare("weak") != 0 ){
      return Stats::WEAK;
    }
    if(s.compare("stronger") != 0 ){
      return Stats::STRONGER;
    }
    if(s.compare("weaker") != 0 ){
      return Stats::WEAKER;
    }
    if(s.compare("strongest") != 0 ){
      return Stats::STRONGEST;
    }
    if(s.compare("weakest") != 0 ){
      return Stats::WEAKEST;
    }
    return Stats::MEDIUM;

  }
}


Character::Character(){
  m_name = "Unknown";
  m_health = 100;
  m_resistance = Stats::MEDIUM;
  m_attack = Stats::MEDIUM;
  m_stamina = Stats::MEDIUM;
}

Character::Character(
		     const std::string& n = "Unknown",
		     const unsigned short& h = 100, 
		     const Stats::stats& r = Stats::MEDIUM, 
		     const Stats::stats& a = Stats::MEDIUM, 
		     const Stats::stats& sta = Stats::MEDIUM){
  m_name = n;
  m_health = h;
  m_resistance = r;
  m_attack = a;
  m_stamina = sta;
}

Character::~Character(){}


std::string Character::toString(){
  std::ostringstream oss;
  oss<<"Character : "<< m_name << std::endl;
  oss<<"Health = "<< m_health << std::endl;
  oss<<"Resistance (L/H) = "<< m_resistance << std::endl;
  oss<<"Strength (L/H) = "<< m_attack << std::endl;
  oss<<"Stamina = "<< m_stamina << std::endl;
  return oss.str();
}

