#include "../headers/CharacterPlayed.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"

#include <cstdio> //delete
#include <sstream>
#include <string>
#include <vector>


CharacterPlayed::CharacterPlayed(
				 const std::string& n,
				 const unsigned short& h, 
				 const Stats::stats& r, 
				 const Stats::stats& a, 
				 const Stats::stats& sta): Character(n, h, r, a, sta){
  m_name = n;
  m_health = h;
  m_resistance = r;
  m_attack = a;
  m_stamina = sta;

  m_currentHealth = h;
  m_action = Action::NORMAL;
  m_frame = 0;
  m_phase = 0;
}

CharacterPlayed::CharacterPlayed(const CharacterPlayed& c){
  m_name = c.getName();
  m_health = c.getHealth();
  m_resistance = c.getResistance();
  m_attack = c.getAttack();
  m_stamina = c.getStamina();
  m_currentHealth = c.getCurrentHealth();
  m_action = c.getAction();
  m_frame = c.getFrame();
  m_phase = c.getPhase();
}

CharacterPlayed::CharacterPlayed(const Character& c){
  m_name = c.getName();
  m_health = c.getHealth();
  m_resistance = c.getResistance();
  m_attack = c.getAttack();
  m_stamina = c.getStamina();
  m_currentHealth = m_health;
  m_action = Action::NORMAL;
  m_phase = 0;
  m_frame = 0;
}

void CharacterPlayed::addFrame(const std::vector< Action::Framing_t >& t){
  printf("Adding frame - %d:%d (%d)\n", m_phase, m_frame, (m_frame >= t[m_phase].nb_frames) );
  m_frame++;
  if(m_frame >= t[m_phase].nb_frames){
    m_phase++;
    m_frame = 0;
  }
}

void CharacterPlayed::checkActionEnd(const std::vector< Action::Framing_t >& t){
  if(m_phase >= t.size() ){
    m_phase = 0;
    m_action = Action::NORMAL;
  }
}

unsigned short CharacterPlayed::loseHealth(const unsigned short& v){
  return (m_currentHealth = (m_currentHealth>v)?m_currentHealth-v:0 );
}

unsigned short CharacterPlayed::gainHealth(const unsigned short& v){
  return (m_currentHealth = MIN(m_health, m_currentHealth+v) );
}

void CharacterPlayed::manage(){
  printf("Managing : action = %s\n", Action::typeToString(m_action).c_str() );
  std::vector<Action::Framing_t> t;
  switch(m_action){
  case Action::ATTACK_LEFT :
    t = Action::Framing_AttackL;
    break;

  case Action::ATTACK_MIDDLE :
    t = Action::Framing_AttackM;
    break;

  case Action::ATTACK_RIGHT :
    t = Action::Framing_AttackR;
    break;

  case Action::DODGE_LEFT :
    t = Action::Framing_DodgeL;
    break;

  case Action::DODGE_MIDDLE :
    t = Action::Framing_DodgeM;
    break;

  case Action::DODGE_RIGHT :
    t = Action::Framing_DodgeR;
    break;

  case Action::STROKE :
    t = Action::Framing_Stroke;
    break;

  default:
    t = Action::Framing_Normal;
    break;
  }

  addFrame(t);
  checkActionEnd(t);
}

std::string CharacterPlayed::toString(){
  std::ostringstream oss;
  oss << m_name << " :" << m_currentHealth<< "/"<< m_health <<std::endl;
  oss << "Framing : action = "<< Action::typeToString(m_action) << "-"<< m_phase <<":"<< m_frame <<std::endl;
  return oss.str();
}

