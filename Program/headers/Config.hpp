#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../headers/Action.hpp"
#include "../headers/Game.hpp"
#include "../headers/Misc.hpp"
#include "../headers/Singleton.hpp"

#include <SFML/Window/Event.hpp>

#include <map>
#include <string>

#include <iostream> //delete

typedef sf::Keyboard::Key Key;

/** Configuration class (singleton)
    It defines the input keys, graphic options...
*/
class Config : public Singleton<Config>{
  friend class Singleton<Config>;

private:
  Config(){ 
    loadFromFile("config.txt"); 
  };
  ~Config(){ };
  std::map< Key, action > m_mapping; // no double in both sides 
  byte m_musicVolume;
  byte m_soundVolume;
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;
  bool m_fullscreen;

public:
  //getters
  action getAction(const Key& k);
  Key getKey(const action&) const;
  std::string keyToString(const Key&) const;
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
  bool getFullscreen() const{
    return m_fullscreen;
  };
  //setters
  void setFullscreen(const bool& b){
    m_fullscreen = b;
  };
  void setAction(const Key&, const action&);
  void dropAction(const action&);
  void dropKey(const Key&);
  void setMusicVolume(const byte& v){
    m_musicVolume = MIN(100, v);
    Game::getInstance()->getMusic()->pause();
    Game::getInstance()->getMusic()->setVolume(m_musicVolume);
    Game::getInstance()->getMusic()->play();
  };
  void addMusic(const unsigned int& s){
    setMusicVolume(m_musicVolume+s);
  };
  void lessMusic(const unsigned int& s){
    std::cout<<"music : ";
    std::cout<<(unsigned int)m_musicVolume<<std::endl;
    if( (int)( (int)m_musicVolume - (int)s) < 0)
      m_musicVolume = 0;
    else
      m_musicVolume -= s;
    Game::getInstance()->getMusic()->pause();
    Game::getInstance()->getMusic()->setVolume(m_musicVolume);
    Game::getInstance()->getMusic()->play();
  };
  void setSoundVolume(const byte& v){
    m_soundVolume = MIN(100, v);
  };
  void addSound(const unsigned int& s){
    setSoundVolume(m_soundVolume+s);
  };
  void lessSound(const unsigned int& s){
    if( (int)(m_soundVolume - s) < 0)
      m_soundVolume = 0;
    else
      m_soundVolume -= s;
  };
  void setWindowWidth(const unsigned int& w){
    m_windowWidth = w;
  };
  void setWindowHeight(const unsigned int& h){
    m_windowHeight = h;
  };
  //others
  bool loadFromFile(const std::string&);
  bool saveFile(const std::string&);
  void init();
};

#endif
