#include "../headers/Match.hpp"

#include <sstream>
#include <string>

Match::Match(Player * p1, Player * p2, 
	     const unsigned short& t = 90,
	     const unsigned short& r = 3,
	     const MatchOptions::scoreType& st = MatchOptions::KO){
  m_player1 = p1;
  m_player2 = p2;
  m_timePerRound = t;
  m_roundsNumber = r;
  m_currentRound = 0;
  m_type = st;
}

Match::~Match(){
}

std::string Match::toString(){
  std::ostringstream oss;
  oss<<"Match "<<m_player1->getName()<<" vs "<<m_player2->getName()<<std::endl;
  oss<<"Rounds : "<< m_currentRound << "/" <<m_roundsNumber << std::endl;
  oss<<"Time per round : "<< m_timePerRound<<" seconds" <<std::endl;
  oss<<"Victory : "<< m_type<< std::endl;
  return oss.str();
}
