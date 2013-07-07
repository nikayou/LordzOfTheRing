#include "../headers/Game.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/Match.hpp"
#include "../headers/Misc.hpp"
#include "../headers/Player.hpp"

#include <SFML/Graphics/Color.hpp>
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


#include <cstdio> //DELETE
#include <cstdlib>
#include <iostream>
#include <sstream>

#define FREQUENCE 1/30
#define FRAMERATE 1

/** init all required the game : 
    -loads configuration
    -creates the window
    -loads files
    -initialize default players, characters, matches...
    -begins the loop
**/
void Game::init(){
  //setting the window
  sf::RenderWindow rw(sf::VideoMode(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() ), "Heil");
  rw.setFramerateLimit(FRAMERATE);
  rw.setPosition(sf::Vector2i(0, 0) ); //adjust
  m_window = &rw;
  //setting match settings
  Character defC(100, Stats::MEDIUM, Stats::MEDIUM, Stats::MEDIUM);
  CharacterPlayed defCP;
  defCP.fromCharacter(defC);
  Player p1("Aaron", &defCP);
  Player p2("Barney", &defCP);
  Match match(&p1, &p2, 60, 3, MatchOptions::POINTS);
  setMatch(&match);
  //starting loop
  setState(GameState::MAIN_MENU);
  loop();
}

void Game::start(){
  setState(GameState::SPLASH);
  splash();
}

/** Starts the game loop : 
    -read input
    -eval action
    -print situation
**/
void Game::loop(){
  while(m_window->isOpen() ){
    //we refresh at every time = frequency
    //read inputs
    printf("Time : %d\n", getClock().getElapsedTime().asMilliseconds() );
    m_window->clear();
    //switching looping with game state
    switch(m_state){

    case GameState::SPLASH :
      splash();
      break;

    case GameState::MAIN_MENU :
      loopMainMenu();
      break;

    case GameState::OPTIONS_MENU :
      loopOptionsMenu();
      break;

    case GameState::PROFILE_MENU :
      loopProfileMenu();
      break;

    case GameState::CHARACTER_SELECT :
      loopCharacterSelect();
      break;

    case GameState::MATCH :
      loopMatch();
      break;

    case GameState::PAUSE :
      pause();
      break;

    default:
      break;
    }
      
    m_window->display();

  }
    
}


void Game::splash(){
  sf::RenderWindow rw(sf::VideoMode(600, 400), "splashscreen", sf::Style::None );
  rw.setPosition(sf::Vector2i(0,0) ); //adjust
  sf::Texture t;
  t.loadFromFile("../../Resources/Images/splash_sfml.png");
  sf::Sprite s;
  s.setTexture(t);
  s.setOrigin(t.getSize().x/2, t.getSize().y/2);
  s.setPosition(sf::Vector2f(300, 200) );
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 2.);
  t.loadFromFile("../../Resources/Images/splash_author.png");
  s.setTexture(t);
  s.setOrigin(t.getSize().x/2, t.getSize().y/2);
  s.setPosition(sf::Vector2f(300, 200) );
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 4.);
  rw.close();
  init();
}

void Game::loopMainMenu(){
  char entry = '_';
  do{
    printf("\033c");
    printf("Main menu\n");
    printf("---------------\n");
    printf("1-Start game\n");
    printf("2-Options\n");
    printf("0-Quit\n");
    printf("---------------\n");
    printf(">");
    std::cin>>entry;
  }while(entry != '1' && entry != '2' && entry != '0');
  switch(entry){
  case '1':
    setState(GameState::PROFILE_MENU);
    loopProfileMenu();
    break;

  case '2':
    setState(GameState::OPTIONS_MENU);
    loopOptionsMenu();
    break;

  case '0':
    close();
    break;

  default:
    loopMainMenu();
    break;
  }

}

void Game::loopOptionsMenu(){  
  char entry = '_';
  do{
    printf("\033c");
    printf("Options menu\n");
    printf("---------------\n");
    printf("Resolution : %d x %d\n", Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() );
    printf("Volume : music = %d - sound = %d\n", Config::getInstance()->getMusicVolume(), Config::getInstance()->getSoundVolume() );
    printf("Inputs : \n");
    printf("Volume : music = %d - sound = %d\n", Config::getInstance()->getMusicVolume(), Config::getInstance()->getSoundVolume() );
    printf("---------------\n");
    printf("1-Change resolution\n");
    printf("2-Change volume\n");
    printf("3-Change inputs\n");
    printf("0-Quit\n");
    printf("---------------\n");
    printf(">");
    std::cin>>entry;
  }while(entry != '1' && entry != '2' && entry != '3' && entry != '0');
  switch(entry){
  case '1':
    break;

  case '2':
    break;

  case '3':
    break;

  case '0':
    close();
    break;

  default:
    loopMainMenu();
    break;
  }

}

void Game::loopProfileMenu(){ 
  char entry = '_';
  do{
    printf("\033c");
    printf("Profile menu\n");
    printf("---------------\n");
    printf("1-Player 1's name : %s\n", getMatch()->getPlayer1()->getName().c_str() );
    printf("2-Player 2's name : %s\n", getMatch()->getPlayer2()->getName().c_str() );
    printf("3-Choose characters\n" );
    printf("0-Quit\n");
    printf("---------------\n");
    printf(">");
    std::cin>>entry;
  }while(entry != '1' && entry != '2' && entry != '3' && entry != '0');
  std::string s = "";
  switch(entry){
  case '1':
    printf("New name : ");
    std::cin>>s;
    getMatch()->getPlayer1()->setName(s);
    loopProfileMenu();
    break;

  case '2':
    printf("New name : ");
    std::cin>>s;
    getMatch()->getPlayer1()->setName(s);
    loopProfileMenu();
    break;

  case '3':
    setState(GameState::CHARACTER_SELECT);
    loopCharacterSelect();
    break;

  case '0':
    close();
    break;

  default:
    loopMainMenu();
    break;
  }

}

void Game::loopCharacterSelect(){
  char entry = '_';  
  do{
    printf("\033c");
    printf("Character selection\n");
    printf("---------------\n");
    printf("Player 1 (%s)\n", getMatch()->getPlayer1()->getName().c_str() );
    printf("---------------\n");
    printf("1- Charasian\n");
    printf("2- Charab\n" );
    printf("0-Quit\n");
    printf("---------------\n");
    printf(">");
    std::cin>>entry;
  }while(entry != '1' && entry != '2' && entry != '0');
  
  switch(entry){
  case '1':
    break;

  case '2':
    break;

  case '0':
    close();
    break;

  default:
    break;
  }

  do{
    printf("\033c");
    printf("Character selection\n");
    printf("---------------\n");
    printf("Player 2 (%s)\n", getMatch()->getPlayer2()->getName().c_str() );
    printf("---------------\n");
    printf("1- Charasian\n");
    printf("2- Charab\n" );
    printf("0-Quit\n");
    printf("---------------\n");
    printf(">");
    std::cin>>entry;
  }while(entry != '1' && entry != '2' && entry != '0');
  
  switch(entry){
  case '1':
    break;

  case '2':
    break;

  case '0':
    close();
    break;

  default:
    break;
  }
  setState(GameState::MATCH);
  loopMatch();

}

void Game::loopMatch(){
  printf("this is a match\n");
  printf("player1 : %s\n", getMatch()->getPlayer1()->getName().c_str() );
  printf("player2 : %s\n", getMatch()->getPlayer2()->getName().c_str() );
  sf::Event event;
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::PAUSE ){
	setState(GameState::PAUSE);
	break;
      }
      

    }

  }


}

void Game::pause(){
  printf("pause\n");
  sf::Event event;
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::PAUSE ){
	setState(GameState::MATCH);
        break;
      }
    }

  }

}

/** Closes the game
 **/
void Game::close(){
  std::cout<<"closing"<<std::endl;
  m_window->close();
}



int main(){
  Game::getInstance()->start();
  return 0;
}

