#include "../headers/Singleton.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
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

public:
  void start();
  void loop();
  void loopSplash();
  void loopMainMenu();
  void loopOptionsMenu();
  void loopProfileMenu();
  void loopCharacterSelect();
  void loopMatch();
  void pause();
  void close();
  GameState::state getState() const{
    return m_state;
  };
  void setState(const GameState::state& s){
    m_state = s;
  };

};
