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

typedef struct{
  MatchType mo_type;
  unsigned short mo_roundsNumber;
  unsigned short mo_strengthModifier;
  unsigned short mo_fatigueModifier;
  unsigned short mo_timePerRound;
  bool mo_TKO; // when 5 KOs in 1 round, the match ends
} MatchOptions;

class Match{

private:
  Player * m_players[2];
  MatchOptions m_options;
  unsigned short m_currentRound; 
  bool m_loaded;

public:
  //constructors
  Match(Player * p1 = NULL, Player * p2 = NULL, 
	const unsigned short& = 90, 
	const unsigned short& = 3
	);
  ~Match();
  //getters
  unsigned short getTimePerRound() const{
    return m_options.mo_timePerRound;
  };
  unsigned short getRoundsNumber() const{
    return m_options.mo_roundsNumber;
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
    return m_options.mo_type;
  };
  bool getTKO() const{
    return m_options.mo_TKO;
  };
  unsigned short getStrengthModifier() const{
    return m_options.mo_strengthModifier;
  };
  unsigned short getFatigueModifier() const{
    return m_options.mo_fatigueModifier;
  };
  MatchOptions getOptions() const{
    return m_options;
  };
  //setters
  void setTimePerRound(const unsigned short& value){
    m_options.mo_timePerRound = value;
  };
  void setRoundsNumber(const unsigned short& value){
    m_options.mo_roundsNumber = value;
  };
  void setCurrentRound(const unsigned short& value){
    m_currentRound = (value >= m_options.mo_roundsNumber)?m_options.mo_roundsNumber:value;
  };
  void setPlayer1(Player * value){
    m_players[0] = value;
  };
  void setPlayer2(Player * value){
    m_players[1] = value;
  };
  void setType(const MatchType& t){
    m_options.mo_type = t;
  };
  void setLoaded(const bool& b){
    m_loaded = b;
  };
  void setStrengthModifier(const unsigned short& value){
    m_options.mo_strengthModifier = value;
  };
  void setFatigueModifier(const unsigned short& value){
    m_options.mo_fatigueModifier = value;
  };
  void setTKO(const bool& value){
    m_options.mo_TKO = value;
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
  bool hasLoaded(){
    return m_loaded;
  };
};

#endif
