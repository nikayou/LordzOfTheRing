#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../headers/Action.hpp"
#include "../headers/Misc.hpp"
#include "../headers/Singleton.hpp"

#include <SFML/Window/Event.hpp>

#include <map>
#include <string>

#define CONFIG_FILE "../../Resources/config.txt"

typedef sf::Keyboard::Key Key;

/** Configuration class (singleton)
    It defines the input keys, graphic options...
*/
class Config : public Singleton<Config>{
  friend class Singleton<Config>;

private:
  Config(){ 
    loadFromFile(CONFIG_FILE); 
  };
  ~Config(){ };
  bool loadFromFile(const std::string&);
  std::map< Key, action > m_mapping; // no double in both sides 
  byte m_musicVolume;
  byte m_soundVolume;
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;

public:
  //getters
  action getAction(const Key& k);
  Key getKey(const action&) const;
  Key getKey(const Action::Type&) const;
  byte getMusicVolume() const{
    return m_musicVolume;
  };
  byte getSoundVolume() const{
    return m_soundVolume;
  };
  unsigned int getWindowWidth() const{
    return m_windowWidth;
  };
  unsigned int getWindowHeight() const{
    return m_windowHeight;
  };
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
  void init();
  std::string toString();
};

#endif
