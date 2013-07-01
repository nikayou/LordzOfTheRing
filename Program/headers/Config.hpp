#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../headers/Action.hpp"
#include "../headers/Singleton.hpp"

#include <SFML/Window/Event.hpp>

typedef sf::Keyboard::Key Key;

typedef struct { 
  Key inpt_key;  
  action inpt_action;
} input;


/** Configuration class (singleton)
    It defines the input keys, graphic options...
 */
class Config : public Singleton<Config>{
  friend class Singleton<Config>;

private:
  Config(){ };
  ~Config(){ };

protected:
  Key m_pause;
  unsigned short m_musicVolume;
  unsigned short m_soundVolume;
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;

public:
  //getters
  //setters
  void setAction(const Key& k, const action& a){
    //m_keyboard[k] = a;
  }
  void setAction(const Key& k, const NAction::Subject){

  }
  //others
};

#endif
