/**
   Here is the game singleton : in which state we are, how many times since launching, the window...
 */
#include "../headers/Singleton.hpp"
#include "../headers/Match.hpp"
#include "../headers/StateHandler.hpp"

#include <iostream> //delete
#include <vector>

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>

#define FRAMERATE 10


class Game : public Singleton<Game>{
  friend class Singleton<Game>;

private:
  Game() { };
  ~Game(){ };
  sf::RenderWindow * m_window;
  sf::RenderTexture * m_render;
  //GameState::state m_state;
  StateHandler * m_stateHandler;
  Match * m_match;
  sf::Clock * m_clock;
  sf::Time * m_timer;
  sf::Music * m_music;

public:
  void start();
  void init();
  void loop();
  void splash();
  void displayGauges();
  void displayClock();
  void displayCharacters();
  void displayMatch();
  void pause(const sf::Int64&);
  void close();
  //getters
  Match * getMatch() const{
    return m_match;
  };
  StateHandler * getStateHandler() const{
    return m_stateHandler;
  };
  sf::Time * getTimer() const{
    return m_timer;
  };
  sf::Clock * getClock() const{
    return m_clock;
  };
  sf::Int32 getMsTime() const{
    return m_clock->getElapsedTime().asMilliseconds();
  };
  float getTime() const{
    return m_clock->getElapsedTime().asSeconds();
  };
  sf::RenderTexture * getRender() const{
    return m_render;
  };
  sf::RenderWindow * getWindow() const{
    return m_window;
  };
  sf::Music * getMusic() const{
      return m_music;
    };
  //setters
  void setMatch(Match * m){
    m_match = m;
  };
  //others
  void addTime(const sf::Time &s){
    *m_timer += s;
  };

};
