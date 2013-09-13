/**
   Here we define a match : two players and gaming options 
 */
#ifndef MATCH_HPP
#define MATCH_HPP

#include "../headers/CharacterPlayed.hpp"
#include "../headers/Player.hpp"

#include <string>

#define BASE_STRIKE 3
#define NICE_STRIKE 9

typedef enum{
  KO, //each KO counts as 1 point 
  ROUND, //1 point for the one who makes more KO in this round
  DAMAGE //damages count as score
} MatchType;

class Match{

private:
  Player * m_players[2];
  unsigned short m_timePerRound; //time (in seconds). 0 = infinity
  unsigned short m_roundsNumber; //number of rounds to play
  unsigned short m_currentRound; 
  MatchType m_type; //type of scoring
  

public:
  //constructors
  Match(Player * p1 = NULL, Player * p2 = NULL, 
const unsigned short& = 90, 
const unsigned short& = 3
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
  MatchType getType() const{
    return m_type;
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
  void setPlayer1(Player * value){
    m_players[0] = value;
  };
  void setPlayer2(Player * value){
    m_players[1] = value;
  };
  void setType(const MatchType& t){
    m_type = t;
  };
  //others
  void newRound(){
    setCurrentRound( m_currentRound +1 );
  }
  void manage();
  void subCheckHits(const unsigned short&, const unsigned short&);
  void checkHits();
  void KO(const unsigned short&);
  bool checkHit(const unsigned short&, const unsigned short&);
  bool checkKO(const unsigned short&);
  bool isFinished();
};

#endif
