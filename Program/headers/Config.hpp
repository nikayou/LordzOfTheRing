#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../headers/Action.hpp"
#include "../headers/Misc.hpp"
#include "../headers/Singleton.hpp"

#include <SFML/Window/Event.hpp>

#include <map>

typedef sf::Keyboard::Key Key;

/** Configuration class (singleton)
    It defines the input keys, graphic options...
 */
class Config : public Singleton<Config>{
  friend class Singleton<Config>;

private:
  Config(){ };
  ~Config(){ };

protected:
  std::map< Key, action > m_mapping; // no double in both sides 
  Key m_pause;
  byte m_musicVolume;
  byte m_soundVolume;
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;

public:
  //getters
  action getAction(const Key& k);
  Key getKey(const action&) const;
  //setters
  void setAction(const Key&, const action&);
  void setMusicVolume(const byte& v){
    m_musicVolume = MIN(100, v);
  };
  void setSoundVolume(const byte& v){
    m_soundVolume = MIN(100, v);
  };
  void setWindowWidth(const unsigned int& w){
    m_windowWidth = w;
  };
  void setWindowHeight(const unsigned int& h){
    m_windowHeight = h;
  };
  //others
};

#endif
