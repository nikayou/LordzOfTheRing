#include "../headers/Game.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
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


#include <cstdio> //DELETE
#include <cstdlib>
#include <iostream>
#include <sstream>

#define FREQUENCE 1/30
#define FRAMERATE 1

/** Starts the game : 
    -loads configuration
    -creates the window
    -loads files
    -begins the loop
**/
void Game::start(){
  sf::RenderWindow rw(sf::VideoMode(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() ), "Heil");
  rw.setFramerateLimit(FRAMERATE);
  m_window = &rw;
  // DELETE
  printf("Initialized Attack_Left Framing : %d\n", Action::Framing_AttackL.size() );
  for(unsigned int i = 0; i < 4; i++)
    printf("%d - ", Action::Framing_AttackL[i].nb_frames );
  printf("\n");
  //END DELETE
  setState(GameState::MATCH);
  loop();
}


/** Starts the game loop : 
    -read input
    -eval action
    -print situation
**/
void Game::loop(){
  sf::Clock loopTimer;
  Character defaut(100, Stats::MEDIUM, Stats::MEDIUM, Stats::MEDIUM, Stats::MEDIUM, Stats::MEDIUM, Stats::MEDIUM);
  CharacterPlayed defautp;
  defautp.fromCharacter(defaut);
  Player p1("player1", &defautp);
  Player p2("player2", &defautp);
  Match match(&p1, &p2, 60, 3, MatchOptions::POINTS);
  while(m_window->isOpen() ){
    //we refresh at every time = frequency
    //read inputs
    printf("Time : %d\n", loopTimer.getElapsedTime().asMilliseconds() );
    m_window->clear();
    //switching looping with game state
    switch(m_state){
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
  //
    
}


void Game::loopSplash(){

}

void Game::loopMainMenu(){

}

void Game::loopOptionsMenu(){

}

void Game::loopProfileMenu(){

}

void Game::loopCharacterSelect(){

}

void Game::loopMatch(){
  printf("this is a match\n");
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
      m_window->close();
    }



    int main(){
      Character c(110, Stats::WEAK, Stats::WEAKEST, Stats::STRONG, Stats::STRONGEST, Stats::MEDIUM, Stats::MEDIUM);
      CharacterPlayed d;
      d.fromCharacter(c);
      Player p("Moi", &d);
      std::cout<< p.toString();
      Game::getInstance()->start();
      return 0;
    }

