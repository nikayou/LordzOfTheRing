/** Here we define a character. They are kind of constants, because these are not those who "play", just the general attributes. 
They are loaded from a special format of files :
<
name=character's name
health=medium
resistance=medium
attack=medium
stamina=medium
>
 */

#include "../headers/Character.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Game.hpp"
#include "../headers/Misc.hpp"
#include "../headers/ResourcesDirectories.hpp"

#include <cstring>
#include <fstream>
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

  unsigned short toHealth(const Stats::stats& v){
    return 52+((unsigned short)v*16);
  }

  unsigned short toStamina(const Stats::stats& v){
    return  (4+(unsigned short)v)*FRAMERATE;
  }

  unsigned short toResistance(const Stats::stats& v){
    return  (-(unsigned short)v+8)*5;
  }

  unsigned short toAttack(const Stats::stats& v){
    return (unsigned short)v ;
  }

  stats baseHealth(const unsigned short& value){
    //health = 52+(16*stat)
    return (stats)( (unsigned short)(value-52)/16);
  }

  stats baseStamina(const unsigned short& value){
    //stamina = (4+stat)*framerate
    return (stats)( (unsigned short)(value/FRAMERATE)-4 );
  }
 
  stats baseResistance(const unsigned short& value){
    //resistance = (-stat+8) * 5
    return (stats) ( (unsigned short) ABS( (value/5)-8 ) );
  }
  
  stats baseAttack(const unsigned short& value){
    //attack = stat
    return (stats)(value);
  }

}


Character::Character(
		     const std::string& n,
		     const unsigned short& h, 
		     const unsigned short& r, 
		     const unsigned short& a, 
		     const unsigned short& sta){
  m_name = n;
  m_health = h;
  m_resistance = r;
  m_attack = a;
  m_stamina = sta;
  m_basename = n;
}

Character::~Character(){}


bool Character::loadFromFile(const std::string& f){
  std::ifstream ifs;
  std::string file = ResDir::getInstance()->getCharDir()+f;
  ifs.open(file.c_str() );
  if( !ifs.good() ){
    return false;
  }
  Character c;
  c.m_basename = f.substr(0, f.find_first_of('.') ) ;
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
      c.setHealth( toHealth(Stats::fromString( cutFrom(line, '=') )   ) );
      defh = true;
      continue;
    }
    if(!defr && contains(line, "resistance=") ){
      c.setResistance( toResistance(Stats::fromString( cutFrom(line, '=') )  ) );
      defr = true;
      continue;
    }
    if(!defa && contains(line, "attack=") ){
      c.setAttack( toAttack(Stats::fromString( cutFrom(line, '=') )  ) );
      defa = true;
      continue;
    }
    if(!defs && contains(line, "stamina=") ){
      c.setStamina( toStamina(Stats::fromString(cutFrom(line, '=')) ) );
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
    m_basename = c.getBasename();
    //std::cout<<"Complete charater file : "<< getBasename() <<std::endl;
    return true;
  }
  //std::cout <<"Error : incomplete character file \""<< file<<"\""<< std::endl;
  return false;
}

