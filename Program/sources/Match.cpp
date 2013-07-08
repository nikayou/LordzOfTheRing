#include "../headers/Match.hpp"

#include <cstdio> //delete
#include <sstream>
#include <string>

Match::Match(Player * p1, Player * p2, 
	     const unsigned short& t,
	     const unsigned short& r,
	     const MatchOptions::scoreType& st){
  m_players[0] = p1;
  m_players[1] = p2;
  m_timePerRound = t;
  m_roundsNumber = r;
  m_currentRound = 0;
  m_type = st;
}

Match::~Match(){
}

void Match::manage(){
  printf("managing match\n");
  m_players[0]->manage();
  m_players[1]->manage();
  //check if match is ended
  printf("managed match\n");
}

std::string Match::toString(){
  std::ostringstream oss;
  oss<<"Match "<<m_players[0]->getName()<<" vs "<<m_players[1]->getName()<<std::endl;
  oss<<"Rounds : "<< m_currentRound << "/" <<m_roundsNumber << std::endl;
  oss<<"Time per round : "<< m_timePerRound<<" seconds" <<std::endl;
  oss<<"Victory : "<< m_type<< std::endl;
  return oss.str();
}
