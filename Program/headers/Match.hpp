#ifndef MATCH_HPP
#define MATCH_HPP

#include "../headers/CharacterPlayed.hpp"
#include "../headers/Player.hpp"

#include <string>

//typedef Player * [2] Players;

namespace MatchOptions{
  typedef enum{ 
    KO, //only KOs count in victory
    POINTS, //only points count in victory
    BOTH //points count, and KOs give points
  } scoreType;
}

class Match{

private:
  Player * m_players[2];
  unsigned short m_timePerRound; //time (in seconds). 0 = infinity
  unsigned short m_roundsNumber; //number of rounds to play
  unsigned short m_currentRound; 
  MatchOptions::scoreType m_type; 

public:
  //constructors
  Match(Player * p1 = NULL, Player * p2 = NULL, 
const unsigned short& = 90, 
const unsigned short& = 3, 
const MatchOptions::scoreType& = MatchOptions::KO
);
  ~Match();
  //getters
  unsigned short getTimePerRound() const{
    return m_timePerRound;
  };
  unsigned short getRoundsNumber() const{
    return m_roundsNumber;
  };
  unsigned short getCurrentRound() const{
    return m_currentRound;
  };
  MatchOptions::scoreType getType() const{
    return m_type;
  };
  Player * getPlayer(const unsigned short& n) const{
    return m_players[n];
  };
  Player * getPlayer1() const{
    return m_players[0];
  };
  Player * getPlayer2() const{
    return m_players[1];
  };
  CharacterPlayed * getCharacter1() const{
    return m_players[0]->getCharacter();
  };
  CharacterPlayed * getCharacter2() const{
    return m_players[1]->getCharacter();
  };
  CharacterPlayed * getCharacter(const unsigned short& v) const{
    return m_players[v]->getCharacter();
  };
  //setters
  void setTimePerRound(const unsigned short& value){
    m_timePerRound = value;
  };
  void setRoundsNumber(const unsigned short& value){
    m_roundsNumber = value;
  };
  void setCurrentRound(const unsigned short& value){
    m_currentRound = (value >= m_roundsNumber)?m_roundsNumber:value;
  };
  void setType(const MatchOptions::scoreType& value){
    m_timePerRound = value;
  };
  void setPlayer1(Player * value){
    m_players[0] = value;
  };
  void setPlayer2(Player * value){
    m_players[1] = value;
};
  //others
  bool isFinished(){
    return m_currentRound >= m_roundsNumber;
  };
  void newRound(){
    setCurrentRound( m_currentRound +1 );
  }
  void manage();
  std::string toString();
};

#endif
