/**
   Here is the game singleton : in which state we are, how many times since launching, the window...
 */
#include "../headers/Singleton.hpp"
#include "../headers/Match.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>

namespace GameState{
  typedef enum{
    SPLASH,
    MAIN_MENU,
    OPTIONS_MENU,
    PROFILE_MENU,
    CHARACTER_SELECT,
    MATCH,
    PAUSE
  } state;
}

class Game : public Singleton<Game>{
  friend class Singleton<Game>;

private:
  Game() { }
  ~Game(){ }
  sf::RenderWindow * m_window;
  GameState::state m_state;
  Match * m_match;
  sf::Clock m_clock;

public:
  void start();
  void init();
  void loop();
  void splash();
  void loopMainMenu();
  void loopOptionsMenu();
  void loopProfileMenu();
  void loopCharacterSelect();
  void loopMatch();
  void displayMatch();
  void pause();
  void close();
  //getters
  Match * getMatch() const{
    return m_match;
  };
  GameState::state getState() const{
    return m_state;
  };
  sf::Clock getClock() const{
    return m_clock;
  };
  sf::Int32 getMsTime() const{
    return m_clock.getElapsedTime().asMilliseconds();
  };
  float getTime() const{
    return m_clock.getElapsedTime().asSeconds();
  };
  //setters
  void setMatch(Match * m){
    m_match = m;
  };
  void setState(const GameState::state& s){
    m_state = s;
  };

};
