#include "../headers/Match.hpp"
#include "../headers/Game.hpp"

#include <iostream> //delete
#include <sstream>
#include <string>

/**
   Here we define a match : two players and gaming options 
 */

Match::Match(Player * p1, Player * p2, 
	     const unsigned short& t,
	     const unsigned short& r){
  m_players[0] = p1;
  m_players[1] = p2;
  m_options.mo_type = MatchType::KO;
  m_options.mo_roundsNumber = r;
  m_options.mo_strengthModifier = 100;
  m_options.mo_fatigueModifier = 100;
  m_options.mo_timePerRound = t;
  m_options.mo_TKO = true;
  m_currentRound = 0;
  m_loaded = false;
}

Match::~Match(){
}

void Match::manage(){
  m_players[0]->manage();
  m_players[1]->manage();
  checkHits();
}

void Match::subCheckHits(const unsigned short& a, const unsigned short& b){
  if( checkHit(a,b) ){
    unsigned short hit = (getCharacter(a)->getAction() == Action::ATTACK_MIDDLE) ? NICE_STRIKE+BASE_STRIKE:BASE_STRIKE;
    hit += getCharacter(a)->getAttack();
    getCharacter(b)->takeHit(hit*((0.0+getStrengthModifier() )/100) );
    getCharacter(a)->zeroHits();
    if(m_options.mo_type == MatchType::DAMAGE)
      m_players[a]->addPoints(hit);
    if( checkKO(b) ){
      getCharacter(b)->setAction(Action::KO);
      getCharacter(a)->setAction(Action::HAPPY);
      KO(b);
    }else{
      getCharacter(b)->setAction(Action::STROKE);
    }
  }
}

void Match::checkHits(){
  //check if someone hits, loses health and is KO
  subCheckHits(0, 1);
  subCheckHits(1, 0);
}

void Match::KO(const unsigned short& p){
  if(m_options.mo_type == MatchType::KO)
    m_players[1^p]->addPoints(1);
}

bool Match::checkHit(const unsigned short& a, const unsigned short& b){
  CharacterPlayed * p1 = getCharacter(a), * p2 = getCharacter(b);
  if (
      ( ( p1->getAction() == Action::ATTACK_LEFT ) && (p2->getAction() != Action::DODGE_LEFT) )
      ||
      ( ( p1->getAction() == Action::ATTACK_MIDDLE ) && (p2->getAction() != Action::DODGE_RIGHT) && (p2->getAction() != Action::DODGE_LEFT)&& (p2->getAction() != Action::DODGE_MIDDLE) )
      || 
      ( ( p1->getAction() == Action::ATTACK_RIGHT ) && (p2->getAction() != Action::DODGE_RIGHT) )
      ){
    if(p1->getState() == Action::ATTACKING) {
      if(p2->getState() != Action::DODGING ){
	return true;
      }
      else{
	// dodge
	std::cout<<"nice dodge ! "<<std::endl;
	p2->zeroHits();
	return false;
      }
    }
  }
  return false;
}

bool Match::checkKO(const unsigned short& p){
  return( getCharacter(p)->getCurrentHealth() == 0);
    
}

bool Match::isFinished(){
  return ( 
	  ( m_currentRound >= m_options.mo_roundsNumber)
	  || (m_options.mo_TKO && (getCharacter1()->getKOs() >= 5 || getCharacter2()->getKOs() >= 5 ) )
	   );
}
