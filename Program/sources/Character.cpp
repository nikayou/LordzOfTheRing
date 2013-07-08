#include "../headers/Character.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Game.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


namespace Stats{

  Stats::stats fromString(const std::string& s){
    if(s.compare("medium") == 0 ){
      return Stats::MEDIUM;
    }
    if(s.compare("strong") == 0 ){
      return Stats::STRONG;
    }
    if(s.compare("weak") == 0 ){
      return Stats::WEAK;
    }
    if(s.compare("stronger") == 0 ){
      return Stats::STRONGER;
    }
    if(s.compare("weaker") == 0 ){
      return Stats::WEAKER;
    }
    if(s.compare("strongest") == 0 ){
      return Stats::STRONGEST;
    }
    if(s.compare("weakest") == 0 ){
      return Stats::WEAKEST;
    }
    return Stats::MEDIUM;

  }
}


Character::Character(
		     const std::string& n,
		     const unsigned short& h, 
		     const Stats::stats& r, 
		     const Stats::stats& a, 
		     const Stats::stats& sta){
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

bool Character::loadFromFile(const std::string& path){
  //std::cout<<"load from file (CharacterManager)"<<std::endl;
  //std::cout<< "Loading Character "<<path<<std::endl;
  std::ifstream ifs;
  ifs.open(path.c_str() );
  if( !ifs.good() ){
    return false;
  }
  Character c;
  bool defn = false, defh = false, defr = false, defa = false, defs = false;
  std::string line = "";
  while( !ifs.eof() ){
    getline(ifs, line);
    if(line[0] == '#' )
      continue;
    if(!defn && contains(line, "name=") ){
      c.setName( cutFrom(line, '=') );
      defn = true;
      continue;
    }
    if(!defh && contains(line, "health=") ){
      c.setHealth( extractInt(line)  );
      defh = true;
      continue;
    }
    if(!defr && contains(line, "resistance=") ){
      c.setResistance( Stats::fromString( cutFrom(line, '=') )  );
      defr = true;
      continue;
    }
    if(!defa && contains(line, "attack=") ){
      c.setAttack( Stats::fromString( cutFrom(line, '=') )  );
      defa = true;
      continue;
    }
    if(!defs && contains(line, "stamina=") ){
      c.setStamina( Stats::fromString( cutFrom(line, '=') )  );
      defs = true;
      continue;
    }

  }
  if(defn && defh && defr && defa && defs){
    m_name = c.getName();
    m_health = c.getHealth();
    m_resistance = c.getResistance();
    m_attack = c.getAttack();
    m_stamina = c.getStamina();
    return true;
  }
  std::cout <<"Error : incomplete character file \""<< path<<"\""<< std::endl;
  return false;
}

