#include "../headers/Character.hpp"

#include <sstream>
#include <string>


Character::Character(
		     const unsigned short& h = 100, 
		     const Stats::stats& lpr = Stats::MEDIUM, 
		     const Stats::stats& hpr = Stats::MEDIUM, 
		     const Stats::stats& lps = Stats::MEDIUM, 
		     const Stats::stats& hps = Stats::MEDIUM, 
		     const Stats::stats& sta = Stats::MEDIUM, 
		     const Stats::stats& dod = Stats::MEDIUM){
  m_health = h;
  m_LResistance = lpr;
  m_HResistance = hpr;
  m_LAttack = lps;
  m_HAttack = hps;
  m_stamina = sta;
  m_dodging = dod;
}

Character::~Character(){}

std::string Character::toString(){
  std::ostringstream oss;
  oss<<"Character "<< std::endl;
  oss<<"Health = "<< m_health << std::endl;
  oss<<"Resistance (L/H) = "<< m_LResistance <<"/"<< m_HResistance <<std::endl;
  oss<<"Strength (L/H) = "<< m_LAttack << "/" << m_HAttack << std::endl;
  oss<<"Stamina = "<< m_stamina << std::endl;
  oss<<"Dodging = "<< m_dodging << std::endl;
  return oss.str();
}
