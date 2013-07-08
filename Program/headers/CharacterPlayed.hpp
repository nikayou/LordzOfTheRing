#ifndef CHARACTERPLAYED_HPP
#define CHARACTERPLAYED_HPP

#include "../headers/Character.hpp"
#include "../headers/Action.hpp"

#include <vector>

class CharacterPlayed : public Character{

protected:
  unsigned short m_currentHealth;
  Action::Type m_action; //what is he doing
  unsigned short m_phase; //in which point of the action he is
  unsigned short m_frame; //in which point in the phase he is

public:
  //constructors
  CharacterPlayed(const std::string& = "Unknown",
		  const unsigned short& = 100, 
		  const Stats::stats& = Stats::MEDIUM, 
		  const Stats::stats& = Stats::MEDIUM, 
		  const Stats::stats& = Stats::MEDIUM);
  //getters
  unsigned short getCurrentHealth() const{
    return m_currentHealth;
  };
  Action::Type getAction() const{
    return m_action;
  };
  unsigned short getFrame() const{
    return m_frame;
  };
  //setters
  void setCurrentHealth(const unsigned short& v){
    m_currentHealth = v;
  };
  void setAction(const Action::Type& v){
    m_currentHealth = v;
  };
  void setFrame(const unsigned short& v){
    m_currentHealth = v;
  };
  //others
  void addFrame(const std::vector<Action::Framing_t>&);
  unsigned short loseHealth(const unsigned short&);
  unsigned short gainHealth(const unsigned short&);
  void fromCharacter(const Character&);
  void manage();

};

#endif
