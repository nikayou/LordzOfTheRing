#include "../headers/Config.hpp"
#include "../headers/Action.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cstdlib>
#include <fstream>
#include <map>
#include <string>

//TODO complete default input
void Config::init(){
  m_pause = sf::Keyboard::Escape;
  m_musicVolume = 70;
  m_soundVolume = 100;
  m_windowWidth = 300;
  m_windowHeight = 100;
  m_mapping[sf::Keyboard::A] = NAction::ATTACK_LEFT + (NAction::PLAYER1<<7);
  m_mapping[sf::Keyboard::Z] = NAction::ATTACK_MIDDLE + (NAction::PLAYER1<<7);
  m_mapping[sf::Keyboard::E] = NAction::ATTACK_RIGHT + (NAction::PLAYER1<<7);
}

bool Config::loadFromFile(const std::string& path){
  init();
  std::ifstream ifs;
  ifs.open(path.c_str() );
  if( !ifs.good() ){
    return false;
  }
  std::string line = "";
  while( !ifs.eof() ){
    getline(ifs, line);
    if(line[0] == '#' )
      continue;
    if(line.find("width=") != std::string::npos ){
      m_windowWidth = atoi(line.substr( line.find_first_of('=')+1, std::string::npos).c_str() );
      continue;
    }
    if(line.find("height=") != std::string::npos ){
      m_windowHeight = atoi(line.substr( line.find_first_of('=')+1, std::string::npos).c_str() );
      continue;
    }
    if(line.find("music=") != std::string::npos ){
      setMusicVolume( atoi(line.substr( line.find_first_of('=')+1, std::string::npos).c_str() ) );
      continue;
    }
    if(line.find("sound=") != std::string::npos ){
      setSoundVolume( atoi(line.substr( line.find_first_of('=')+1, std::string::npos).c_str() ) );
      continue;
    }
  }
  return true;
}

action Config::getAction(const Key& k){
  if( m_mapping.find(k) == m_mapping.end() )
    return (action)0;
  return m_mapping[k];
}

//TODO
Key Config::getKey(const action& a) const{
  return (Key)-1;
}

void Config::setAction(const Key& k, const action& a){
  std::map<Key,action>::iterator it = m_mapping.find(k);
  if( it != m_mapping.end() )
    m_mapping.erase( it );
  m_mapping.insert( std::pair<Key, action>(k, a) );
}
