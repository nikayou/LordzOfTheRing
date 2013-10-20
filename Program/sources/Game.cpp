/**
   Here is the game singleton : in which state we are, how many times since launching, the window...
*/
#include "../headers/Game.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/CharacterManager.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/GameState.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/Match.hpp"
#include "../headers/Misc.hpp"
//#include "../headers/Music.hpp"
//#include "../headers/MusicManager.hpp"
#include "../headers/Player.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/ResourcesDirectories.hpp"
#include "../headers/RoundEndState.hpp"
#include "../headers/SpritesheetManager.hpp"
#include "../headers/StateHandler.hpp"
#include "../headers/Texture.hpp"
#include "../headers/TextureManager.hpp"
#include "../headers/GUI_Bordered.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/FontManager.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>


/** init all required the game : 
    -loads configuration
    -creates the window
    -loads files
    -initialize default players, characters, matches...
    -begins the loop
**/
void Game::init(){
  m_window = new sf::RenderWindow(sf::VideoMode(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() ), "Lordz Of The Ring", sf::Style::Titlebar|sf::Style::Close); 
  m_window->setFramerateLimit( (float) FRAMERATE);
  m_window->setPosition(sf::Vector2i(10, 10) ); //adjust
  m_window->setKeyRepeatEnabled(false);
  m_render->create(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() );
  //starting loop
  m_music->setVolume(Config::getInstance()->getMusicVolume() );
  m_music->openFromFile("../../resources/audio/menu1.ogg");
  m_music->setVolume(Config::getInstance()->getMusicVolume() );
  m_music->play();
  m_container = new Container(m_render);
  m_gui = new GUIWindow (m_window, m_container );
  m_stateHandler->change(new MainMenuState() );
  loop();
}

void Game::start(){
  m_updating = true;
  m_render = new sf::RenderTexture();
  m_stateHandler = new StateHandler();
  m_clock = new sf::Clock();
  m_timer = new sf::Time();
  m_music = new sf::Music();
  Player p1("Player1");
  Player p2("Player2");
  m_match = new Match(&p1, &p2, 90, 3);
  m_match->setType(MatchType::KO);
  splash();
}

/** Starts the game loop : 
    -read input
    -eval action
    -print situation
**/
void Game::loop(){
  while(m_updating && m_window->isOpen() ){
    m_stateHandler->update();
    m_stateHandler->render();
    display();
  }
}

void Game::display(){
  if(m_updating)
    m_window->display();
}

void Game::splash(){
  sf::RenderWindow rw(sf::VideoMode(600, 400), "LOTR", sf::Style::None );
  rw.setPosition(sf::Vector2i(0,0) ); //adjust
  sf::Texture * t;
  t = TextureManager::getInstance()->get("splashscreens/sfml.splash")->getTexture();
  sf::Sprite s;
  s.setTexture(*t);
  s.setOrigin(t->getSize().x/2, t->getSize().y/2);
  s.setPosition(sf::Vector2f(300, 200) );
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 2.);
  t = TextureManager::getInstance()->get("splashscreens/auth.splash")->getTexture();
  s.setTexture(*t );
  s.setOrigin(t->getSize().x/2, t->getSize().y/2);
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 4.);
  t = TextureManager::getInstance()->get("splashscreens/pixotters.splash")->getTexture();
  s.setTexture(*t );
  s.setOrigin(t->getSize().x/2, t->getSize().y/2);
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 6.);
  rw.close();
  TextureManager::getInstance()->remove("splashscreens/sfml.splash");
  TextureManager::getInstance()->remove("splashscreens/auth.splash");
  TextureManager::getInstance()->remove("splashscreens/pixotters.splash");
  init();
}  


void Game::pause(const sf::Int64& t0){
  sf::Event event;
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::PAUSE ){
	Game::getInstance()->getStateHandler()->pop();
	*m_timer = sf::microseconds(t0);
	break;
      }
    }
  }
}

/** Closes the game instance, trying to free memory
 **/
void Game::close(){
  m_updating = false;
  CharacterManager::getInstance()->clear();
  SpritesheetManager::getInstance()->clear();
  FontManager::getInstance()->clear();
  TextureManager::getInstance()->clear();
  m_window->close();
  while(!getStateHandler()->empty() ){
    getStateHandler()->pop();
  }
  delete( m_container );
  delete( m_music);
  delete( m_timer);
  delete( m_clock);
  delete( m_match);
  delete( m_stateHandler);
  delete( m_render);
  delete( m_window);
  delete( m_gui);
}



int main(int argc, char *argv[]){
   if(argc <= 1){
     std::string p("../../resources/");
     ResDir::recompute_resdir(p);
    p.clear();
  }else{
     ResDir::recompute_resdir(argv[1]);
  }
  Game::getInstance()->start();
  return 0;
}

