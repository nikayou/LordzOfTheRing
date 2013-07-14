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

public:
  //constructors
  CharacterPlayed(const std::string& = "Unknown",
		  const unsigned short& = 100, 
		  const Stats::stats& = Stats::MEDIUM, 
		  const Stats::stats& = Stats::MEDIUM, 
		  const Stats::stats& = Stats::MEDIUM);
  CharacterPlayed(const CharacterPlayed& c);
  CharacterPlayed(const Character& c);
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
  Action::State getState() const{
    return m_state;
  };
  //setters
  void setCurrentHealth(const unsigned short& v){
    m_currentHealth = v;
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
  //others
  void checkActionEnd(const Action::Framing& t);
  void addFrame(const Action::Framing&);
  unsigned short loseHealth(const unsigned short&);
  unsigned short gainHealth(const unsigned short&);
  void manage();
  std::string toString();

};

#endif
