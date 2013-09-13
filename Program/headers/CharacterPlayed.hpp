/**
   Here we define a played character : they are like characters, but gets additional attributes, necessary for in-game treatment
*/

#ifndef CHARACTERPLAYED_HPP
#define CHARACTERPLAYED_HPP

#include "../headers/Character.hpp"
#include "../headers/Action.hpp"

#include <string>
#include <vector>

class CharacterPlayed : public Character{

protected:
  unsigned short m_currentHealth;
  Action::Type m_action; //what is he doing
  unsigned short m_frame; //in which point of the action he is
  Action::State m_state; //the beggining of the real act (hit of a strike)
  unsigned short m_currentStamina; //current stamina
  unsigned short m_receivedHits; //the number of consecutive hits taken
  unsigned short m_kos; //the number of KOs took

public:
  //constructors
  CharacterPlayed(const std::string& = "Unknown",
		  const unsigned short& = 100, 
		  const unsigned short& = 25, 
		  const unsigned short& = 3, 
		  const unsigned short& = 70);
  CharacterPlayed(const CharacterPlayed& c);
  CharacterPlayed(const Character& c);
  //getters
  unsigned short getCurrentHealth() const{
    return m_currentHealth;
  };
  unsigned short getCurrentStamina() const{
    return m_currentStamina;
  };
  Action::Type getAction() const{
    return m_action;
  };
  unsigned short getFrame() const{
    return m_frame;
  };
  Action::State getState() const{
    return m_state;
  };
  unsigned short getKOs() const{
    return m_kos;
  };
  //setters
  void setCurrentHealth(const unsigned short& v){
    m_currentHealth = v;
  };
  void setCurrentStamina(const unsigned short& v){
    m_currentStamina = v;
  };
  void setAction(const Action::Type& v){
    m_action = v;
    m_frame = 0;
  };
  void setFrame(const unsigned short& v){
    m_frame = v;
  };
  void setState(const Action::State& v){
    m_state = v;
  };
  void setKOs(const unsigned short& v){
    m_kos = v;
  };
  //others
  void takeHit(const unsigned short&);
  bool doHit();
  void actionEnd();
  void addFrame(const Action::Framing&);
  unsigned short loseHealth(const unsigned short&);
  unsigned short gainHealth(const unsigned short&);
  unsigned short loseStamina(const unsigned short&);
  unsigned short gainStamina(const unsigned short&);
  void manage();
  void zeroHits(){ m_receivedHits = 0; };
  unsigned int getDamages();
  void reset();

};

#endif
