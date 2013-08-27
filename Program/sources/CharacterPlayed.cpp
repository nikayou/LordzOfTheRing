/**
Here we define a played character : they are like characters, but gets additional attributes, necessary for in-game treatment
 */

#include "../headers/CharacterPlayed.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"

#include <sstream>
#include <string>
#include <vector>


CharacterPlayed::CharacterPlayed(
				 const std::string& n,
				 const unsigned short& h, 
				 const Stats::stats& r, 
				 const Stats::stats& a, 
				 const unsigned short& sta): Character(n, h, r, a, sta){
  m_name = n;
  m_health = h;
  m_resistance = r;
  m_attack = a;
  m_stamina = sta;
  m_currentStamina = sta;
  m_currentHealth = h;
  m_action = Action::NONE;
  m_frame = 0;
  m_state = Action::NORMAL;
}

CharacterPlayed::CharacterPlayed(const CharacterPlayed& c){
  m_name = c.getName();
  m_basename = c.getBasename();
  m_health = c.getHealth();
  m_resistance = c.getResistance();
  m_attack = c.getAttack();
  m_stamina = c.getStamina();
  m_currentStamina = m_stamina;
  m_currentHealth = c.getCurrentHealth();
  m_action = c.getAction();
  m_frame = c.getFrame();
  m_state = c.getState();
}

CharacterPlayed::CharacterPlayed(const Character& c){
  m_name = c.getName();
  m_basename = c.getBasename();
  m_health = c.getHealth();
  m_resistance = c.getResistance();
  m_attack = c.getAttack();
  m_stamina = c.getStamina();
  m_currentHealth = m_health;
  m_currentStamina = m_stamina;
  m_action = Action::NONE;
  m_frame = 0;
  m_state = Action::NORMAL;
}

void CharacterPlayed::addFrame(const Action::Framing& f){
  m_frame++;
  if(m_frame >= f.nb_frames){
    m_frame = 0;
    m_action = Action::NONE; //action is over, come back to normal
    m_state = Action::NORMAL;
  }else if(m_frame == f.change_state){
    setState(f.state);
  }else if(m_frame == f.return_state){
    setState(Action::NORMAL);
  }
}

unsigned short CharacterPlayed::loseHealth(const unsigned short& v){
  unsigned short nextHealth = m_currentHealth - v + m_resistance;
  return (m_currentHealth = nextHealth<m_currentHealth? nextHealth:0 );
}

unsigned short CharacterPlayed::gainHealth(const unsigned short& v){
  return (m_currentHealth = MIN(m_health, m_currentHealth+v) );
}

void CharacterPlayed::manage(){
  Action::Framing f;
  switch(m_action){
  case Action::ATTACK_LEFT :
    f = Action::Framing_AttackL;
    break;

  case Action::ATTACK_MIDDLE :
    f = Action::Framing_AttackM;
    break;

  case Action::ATTACK_RIGHT :
    f = Action::Framing_AttackR;
    break;

  case Action::DODGE_LEFT :
    f = Action::Framing_DodgeL;
    break;

  case Action::DODGE_MIDDLE :
    f = Action::Framing_DodgeM;
    break;

  case Action::DODGE_RIGHT :
    f = Action::Framing_DodgeR;
    break;

  case Action::STROKE :
    f = Action::Framing_Stroke;
    break;

  default:
    f = Action::Framing_None;
    break;
  }

  addFrame(f);
  checkActionEnd(f);
}

void CharacterPlayed::takeHit(const unsigned short& dmg){
  setAction(Action::STROKE);
  loseHealth(dmg);
  m_receivedHits++;
  if(m_receivedHits > m_resistance)
    setAction(Action::STUN);
}

bool CharacterPlayed::doHit(){
  if(m_stamina < 0) 
    return false;
  m_stamina -= 1;
  return true;
}

void CharacterPlayed::checkActionEnd(const Action::Framing& f){
  if( m_frame >= f.nb_frames){
    setAction(Action::NONE);
    m_state = Action::NORMAL;
  }
}

std::string CharacterPlayed::toString(){
  std::ostringstream oss;
  oss << m_name << " : " << m_currentHealth<< "/"<< m_health << " - " << m_currentStamina << "/" << m_stamina << std::endl;
  oss << "Framing : action = "<< Action::typeToString(m_action) << "-"<< m_frame <<":"<< m_state <<std::endl;
  return oss.str();
}

