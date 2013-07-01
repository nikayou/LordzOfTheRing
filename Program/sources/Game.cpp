#include "../headers/Game.hpp"
#include "../headers/Character.hpp"
#include "../headers/Player.hpp"
#include "../headers/Match.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

#include <iostream>
#include <sstream>

#define FREQUENCE 1/30

/** Starts the game : 
-loads configuration
-creates the window
-loads files
-begins the loop
 **/
void Game::start(){
  sf::RenderWindow rw(sf::VideoMode(800, 600), "Heil");
  m_window = &rw;
  loop();
}


/** Starts the game loop : 
    -read input
    -eval action
    -print situation
**/
void Game::loop(){
  sf::Clock loopTimer;
  while(true){
    if(loopTimer.getElapsedTime().asMilliseconds() > FREQUENCE*1000){
      //we refresh at every time = frequency
      //read inputs
      m_window->clear();
      sf::Event event;
      while( m_window->pollEvent(event) ){
	if(event.type == sf::Event::Closed){
	  close();
	}else if(event.type ==sf::Event::KeyPressed ){
	  std::ostringstream oss;
	  oss << event.key.code;
	  std::cout<<"Pressed "<< oss.str() <<std::endl;
	  //readInput( event.key );
	}
	  
      
      }
      //
      m_window->display();
    }
  }
}


/** Closes the game
 **/
void Game::close(){
  m_window->close();
}



int main(){
  Character c(110, Stats::WEAK, Stats::WEAKEST, Stats::STRONG, Stats::STRONGEST, Stats::MEDIUM, Stats::MEDIUM);
  Player p("Moi", &c);
  std::cout<< p.toString();
  Game::getInstance()->start();
  return 0;
}

