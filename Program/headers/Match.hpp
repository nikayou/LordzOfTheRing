#ifndef MATCH_HPP
#define MATCH_HPP

#include "../headers/Player.hpp"

namespace MatchOptions{
  typedef enum{ 
    KO, //only KOs count in victory
    POINTS, //only points count in victory
    BOTH //points count, and KOs give points
  } scoreType;
}

class Match{

private:
  unsigned short m_timePerRound; //time (in seconds). 0 = infinity
  unsigned short m_roundsNumber; //number of rounds to play
  unsigned short m_currentRound; 
  MatchOptions::scoreType m_type; 
  Player * m_player1;
  Player * m_player2;

public:
  //constructors
  Match();
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
  Player * getPlayer1() const{
    return m_player1;
  };
  Player * getPlayer2() const{
    return m_player2;
  };
  //setters
  void setTimePerRound(const unsigned short& value){
    m_timePerRound = value;
  };
  void setRoundsNumber(const unsigned short& value){
    m_roundsNumber = value;
  };
  void setCurrentRound(const unsigned short& value){
    m_currentRound = value;
  };
  void setType(const MatchOptions::scoreType& value){
    m_timePerRound = value;
  };
  void setPlayer1(Player * value){
    m_player1 = value;
  };
  void setPlayer2(Player * value){
    m_player2 = value;
  };
  //others
  bool isFinished(){
    return m_currentRound >= m_roundsNumber;
  };
};

#endif
