/**
   Here we define a played character : they are like characters, but gets additional attributes, necessary for in-game treatment
*/

/*
CharacterPlayed are Characters with additionnal attributes necessary for match.

 */
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/Game.hpp"
#include "../headers/Random.hpp"

#include <iostream> //delete
#include <sstream>
#include <string>
#include <vector>


CharacterPlayed::CharacterPlayed(
				 const std::string& n,
				 const unsigned short& h, 
				 const unsigned short& r, 
				 const unsigned short& a, 
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
  m_receivedHits = 0;
  m_kos = 0;
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
  m_receivedHits = 0;
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
  m_receivedHits = 0;
  m_kos = 0;
}

void CharacterPlayed::addFrame(const Action::Framing& f){
  m_frame++;
  if(m_frame >= f.nb_frames){
    actionEnd();
  }else if(m_frame == f.change_state){
    setState(f.state);
  }else if(m_frame == f.return_state){
    setState(Action::NORMAL);
  }
}

unsigned short CharacterPlayed::loseHealth(const unsigned short& v){
  unsigned short nextHealth = m_currentHealth - v;
  return (m_currentHealth = nextHealth<m_currentHealth? nextHealth:0 );
}

unsigned short CharacterPlayed::gainHealth(const unsigned short& v){
  return (m_currentHealth = MIN(m_health, m_currentHealth+v) );
}

unsigned short CharacterPlayed::loseStamina(const unsigned short& v){
  unsigned short nextStamina = m_currentStamina - v;
  return (m_currentStamina = nextStamina<m_currentStamina? nextStamina:0 );
}

unsigned short CharacterPlayed::gainStamina(const unsigned short& v){
  return (m_currentStamina = MIN(m_stamina, m_currentStamina+v) );
}


void CharacterPlayed::manage(){
  Action::Framing f;
  if(m_currentStamina == 0 && m_action != Action::ATTACK_LEFT && m_action != Action::ATTACK_MIDDLE && m_action != Action::ATTACK_RIGHT)
    m_action = Action::BREATHING;
  switch(m_action){
  case Action::ATTACK_LEFT :
    if(m_currentStamina > 0)
      gainStamina(FRAMERATE/10);
    f = Action::Framing_AttackL;
    break;

  case Action::ATTACK_MIDDLE :
    
    if(m_currentStamina > 0)
      gainStamina(FRAMERATE/10);
    f = Action::Framing_AttackM;
    break;

  case Action::ATTACK_RIGHT :
    
    if(m_currentStamina > 0)
      gainStamina(FRAMERATE/10);
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
    gainStamina(FRAMERATE/10);
    f = Action::Framing_Stroke;
    break;

  case Action::KO :
    f = Action::Framing_KO;
    break;

  case Action::HAPPY :
    f = Action::Framing_Happy;
    gainStamina(FRAMERATE/10);
    break;

  case Action::RAISING :
    f = Action::Framing_Raising;
    gainHealth( (m_health*(MAX(0.2, 1-0.2*m_kos )) )/(f.nb_frames) );
    gainStamina(FRAMERATE/10);
    break;

  case Action::STUN :
    f = Action::Framing_Stun;
    break;

  case Action::BREATHING :
    f = Action::Framing_Breathing;
    gainStamina(FRAMERATE/10);
    break;

  default:
    f = Action::Framing_None;
    gainStamina(FRAMERATE/10);
    break;
  }

  addFrame(f);
}

void CharacterPlayed::takeHit(const unsigned short& dmg){
  setAction(Action::STROKE);
  loseHealth(dmg);
  m_receivedHits++;
}

bool CharacterPlayed::doHit(){
  if(m_currentStamina < FRAMERATE) 
    return false;
  loseStamina(2*FRAMERATE);
  return true;
}

void CharacterPlayed::actionEnd(){
  m_frame = 0;
  if(m_action == Action::STROKE && m_receivedHits >= 3){
    unsigned int r = Random::getInstance()->get(0, 100);
    if(r <= 50.0 + ( (m_receivedHits-3)*m_resistance) ){
      zeroHits();
      m_state = Action::NORMAL;
      m_action = Action::STUN;
      return;
    }
  }
  if(m_action == Action::KO){
    m_state = Action::CRYING;
    setAction(Action::RAISING);
    m_kos++;
    return;
  }
  m_state = Action::NORMAL;
  setAction(Action::NONE);
}

unsigned int CharacterPlayed::getDamages(){
  int accu = 1;
  int res = 0;
  for(int j = 0; j < m_kos; j++){
    res += accu*(m_health-m_currentHealth);
    accu -= 0.2;
  }
  return res;
}

void CharacterPlayed::reset(){
  m_currentHealth = m_health;
  m_currentStamina = m_stamina;
  m_action = Action::NONE;
  m_state = Action::NORMAL;
  m_receivedHits = 0;
  m_kos = 0;
};
