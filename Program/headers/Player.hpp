#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../headers/Character.hpp"

#include <string>

class Player{

private:
  std::string m_name; //name of the player, displayed during the match
  unsigned short m_victories; //number of victories (for global score)
  unsigned short m_points; //number of points in the current match
  Character * m_character; //character chosen by the player

public:
  //constructors
  Player(const std::string&, Character *);
  ~Player();
  //getters
  std::string getName() const{
    return m_name; 
  };
  unsigned short getVictories() const{
    return m_victories; 
  };
  unsigned short getPoints() const {
    return m_points; 
  };
  Character * getCharacter() const{
    return m_character; 
  };
  //setters
  void setName(const std::string& value){
    m_name = value;
  };
  void setVictories(const unsigned short& value){
    m_victories = value;
  };
  void setPoints(const unsigned short& value){
    m_points = value;
  };
  void setCharacter(Character * value){
    m_character = value;
  };
  //others
  void resetPoints(){
    m_points = 0;
  };
  void addPoints(const unsigned short& value){
    m_points = ( (m_points+value) <= -1) ? m_points+value : -1;
  };
  void addVictory(){
    m_victories = (m_victories == -1) ? -1 : m_victories+1;
  }
};


#endif
