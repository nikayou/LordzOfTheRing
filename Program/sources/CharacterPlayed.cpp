#include "../headers/CharacterPlayed.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"

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

void CharacterPlayed::fromCharacter(const Character& c){
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
  m_frame++;
  if(m_frame >= t[m_phase].nb_frames){
    m_phase++;
    m_frame = 0;
    if(m_phase >= t.size() )
      m_phase = 0;
  }
}

unsigned short CharacterPlayed::loseHealth(const unsigned short& v){
  return (m_currentHealth = (m_currentHealth>v)?m_currentHealth-v:0 );
}

unsigned short CharacterPlayed::gainHealth(const unsigned short& v){
  return (m_currentHealth = MIN(m_health, m_currentHealth+v) );
}

void CharacterPlayed::manage(){
  switch(m_action){
  case Action::ATTACK_LEFT :
    addFrame(Action::Framing_AttackL);
    break;

  case Action::ATTACK_MIDDLE :
    addFrame(Action::Framing_AttackM);
    break;

  case Action::ATTACK_RIGHT :
    addFrame(Action::Framing_AttackR);
    break;

  case Action::DODGE_LEFT :
    addFrame(Action::Framing_DodgeL);
      break;

    case Action::DODGE_MIDDLE :
      addFrame(Action::Framing_DodgeM);
      break;

    case Action::DODGE_RIGHT :
      addFrame(Action::Framing_DodgeR);
      break;

    case Action::STROKE :
      addFrame(Action::Framing_Stroke);
      break;

    default:
      break;
    }
  }

