#include "../headers/Singleton.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

class Game : public Singleton<Game>{
  friend class Singleton<Game>;

private:
  Game() { }
  ~Game(){ }
  sf::RenderWindow * m_window;

public:
  void start();
  void loop();
  void close();

};
