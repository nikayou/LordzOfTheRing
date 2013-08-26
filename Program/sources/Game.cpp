/**
   Here is the game singleton : in which state we are, how many times since launching, the window...
*/
#include "../headers/Game.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/CharacterManager.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/Match.hpp"
#include "../headers/Misc.hpp"
//#include "../headers/Music.hpp"
//#include "../headers/MusicManager.hpp"
#include "../headers/Player.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/SpritesheetManager.hpp"
#include "../headers/Texture.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Audio/Music.hpp>
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
#define FRAMERATE 10

/** init all required the game : 
    -loads configuration
    -creates the window
    -loads files
    -initialize default players, characters, matches...
    -begins the loop
**/
void Game::init(){
  //setting the window
  sf::RenderWindow rw(sf::VideoMode(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() ), "MyBadPunchOut");
  rw.setFramerateLimit( (float) FRAMERATE);
  rw.setPosition(sf::Vector2i(10, 10) ); //adjust
  m_window = &rw;
  m_music.setVolume(Config::getInstance()->getMusicVolume() );
  //setting match settings
  Player p1("Aaron");
  Player p2("Barney");
  Match match(&p1, &p2, 210, 3);
  setMatch(&match);
  //starting loop
  setState(GameState::CHARACTER_SELECT);
  //setState(GameState::MAIN_MENU);
  std::cout<<"Game initialized"<<std::endl;
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
    printf("Time : %d\n", getClock().getElapsedTime().asSeconds() );
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
      displayMatch();
      break;

    case GameState::PAUSE :
      pause(m_timer.asMicroseconds() );
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
  s.setPosition(sf::Vector2f(300, 200) );
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 4.);
  rw.close();
  TextureManager::getInstance()->remove("splashscreens/sfml.splash");
  TextureManager::getInstance()->remove("splashscreens/auth.splash");
  
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
    getMatch()->getPlayer2()->setName(s);
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
  std::cout<<"Character selection"<<std::endl;
  CharacterPlayed c1(* (CharacterManager::getInstance()->get("avrage.chara") )  );
  CharacterPlayed c2(* (CharacterManager::getInstance()->get("sdard.chara") )  );
  getMatch()->getPlayer2()->setCharacter(c2);
  getMatch()->getPlayer1()->setCharacter(c1);
  loadMatch();

}

void Game::loadMatch(){
  m_music.stop();
  m_window->clear(sf::Color::Black);
  sf::Texture * t = TextureManager::getInstance()->get("loading")->getTexture();
  sf::Sprite s;
  s.setTexture(*t);
  s.setPosition(0,0);
  m_window->draw(s);
  m_window->display();
  TextureManager::getInstance()->get("background")->getTexture();
  TextureManager::getInstance()->get("sprites.png")->getTexture();
  std::string file = "characters/";
  // character 2
  unsigned int frame = getMatch()->getCharacter2()->getFrame();
  file += getMatch()->getCharacter2()->getBasename();
  file += "_front.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = getMatch()->getCharacter2()->getBasename();
  file += "_front.sprt";
  SpritesheetManager::getInstance()->get(file);
  frame = getMatch()->getCharacter1()->getFrame();
  file = "characters/";
  file += getMatch()->getCharacter1()->getBasename();
  file += "_back.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = getMatch()->getCharacter1()->getBasename();
  file += "_back.sprt";
  SpritesheetManager::getInstance()->get(file);
  m_window->clear(sf::Color::Black);
  m_timer = sf::microseconds(0);
  m_clock.restart();
  if(m_music.openFromFile("../../resources/audio/battle1.ogg") )
    m_music.play();
  setState(GameState::MATCH);
}


void Game::loopMatch(){
  if(getClock().getElapsedTime().asSeconds() >= 1){
    m_timer += sf::seconds(1);
    m_clock.restart();
  }
  printf("player1 : %p\n%s\n", getMatch()->getCharacter1(), getMatch()->getCharacter1()->toString().c_str() );
  printf("player2 : %p\n%s\n", getMatch()->getCharacter2(), getMatch()->getCharacter2()->toString().c_str() );
  sf::Event event;
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(a == (action)0 )
	break;
      if(Action::getType(a) == Action::PAUSE ){
	setState(GameState::PAUSE);
	break;
      }
      
      if(getMatch()->getCharacter(Action::getDoer(a) )->getAction() == Action::NONE ){
	getMatch()->getCharacter(Action::getDoer(a) )->setAction( Action::getType(a) );
      }else{
	//player is already performing an action
	printf("Cannot do an action until the curent is done\n");
      }
    }

  }
  getMatch()->manage();
}



void Game::displayGauges(){
  
  // health bars : red, green, border
  sf::Sprite s;
  sf::Texture * t;
  float width = Config::getInstance()->getWindowWidth();
  // background
  t = TextureManager::getInstance()->get("background")->getTexture();
  s.setTexture(*t);
  s.setPosition(sf::Vector2f(0, 0) );
  m_window->draw(s);
  // opponent
  //opponent's spec
  //player's spec
  //player

  //red
  t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 312, 40) );
  s.setPosition (sf::Vector2f(0, 26) );
  m_window->draw(s);
  s.setPosition (sf::Vector2f(width-312, 26) );
  m_window->draw(s);
  //green
  s.setTextureRect(sf::IntRect(0, 40, 312, 40) );
  //p1
  float percent = 0.0+getMatch()->getCharacter1()->getHealth()-getMatch()->getCharacter1()->getCurrentHealth();
  percent /= getMatch()->getCharacter1()->getHealth();
  percent *= 300;
  s.setPosition(sf::Vector2f(-percent, 26) );
  m_window->draw(s);
  //p2
  percent = 0.0+getMatch()->getCharacter2()->getHealth()-getMatch()->getCharacter2()->getCurrentHealth();
  percent /= getMatch()->getCharacter2()->getHealth();
  percent *= 300;
  s.setPosition (sf::Vector2f(width-312+percent, 26) );
  m_window->draw(s);
  //borders
  s.setTextureRect(sf::IntRect(128, 116, 8, 40 ) );
  s.setPosition(0, 26);
  m_window->draw(s);
  s.setTextureRect(sf::IntRect(128+8, 116, 8, 40 ) );
  s.setPosition(width-8, 26);
  m_window->draw(s);
  
  
}

void Game::displayClock(){
  
  // chrono : back, second 100, second 10, second 1
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  float width = Config::getInstance()->getWindowWidth();
  s.setTextureRect(sf::IntRect(0, 80, 128, 64) );
  s.setPosition(width/2-64, 10);
  s.setTexture(*t);
  m_window->draw(s);  
  unsigned short time;
  time = getMatch()->getTimePerRound()-(getTimer().asSeconds() );
  if(time > 0){ // if time is infinity, we are not displaying time
    //get time remaining
    //displaying 100'
    s.setTextureRect(sf::IntRect(128+(28*(time/100) ), 80, 28, 36) );
    s.setPosition(width/2-64+16, 10+ 14);
    m_window->draw(s);
    //displaying 10'
    s.setTextureRect(sf::IntRect(128+(28*(time%100/10) ), 80, 28, 36) );
    s.setPosition(width/2-64+16+34, 10+ 14);
    m_window->draw(s);
    //displaying 1'
    s.setTextureRect(sf::IntRect(128+(28*(time%10) ), 80, 28, 36) );
    s.setPosition(width/2-64+16+68, 10+ 14);
    m_window->draw(s);
  }
  
}

void Game::displayCharacters(){
  float width = Config::getInstance()->getWindowWidth();
  sf::Sprite s;
  Spritesheet * ss;
  sf::Texture * t;
  //displaying players' sprites : we need the image, the spritesheet, and the current frame of the action
  std::string file = "characters/";
  // character 2
  unsigned int frame = getMatch()->getCharacter2()->getFrame();
  file += getMatch()->getCharacter2()->getBasename();
  file += "_front.png";
  t = TextureManager::getInstance()->get(file)->getTexture();
  file = getMatch()->getCharacter2()->getBasename();
  file += "_front.sprt";
  ss = SpritesheetManager::getInstance()->get(file);
  s.setTexture(*t);
  s.setPosition( 400, 400  );
  unsigned short idSprite = ss->getAnimation(getMatch()->getCharacter2()->getAction() ).get(getMatch()->getCharacter2()->getFrame() ); 
  Sprite * sprt = ss->getSprite(idSprite);
  if(sprt){
    s.setTextureRect(sf::IntRect(sprt->getPositionX(), sprt->getPositionY(), sprt->getWidth(), sprt->getHeight() ) );
    s.setOrigin( sprt->getHotpointX(), sprt->getHotpointY()  );
    s.scale(2.0, 2.0);
    m_window->draw(s);
  }
  // character 2
  frame = getMatch()->getCharacter1()->getFrame();
  file = "characters/";
  file += getMatch()->getCharacter1()->getBasename();
  file += "_back.png";
  t = TextureManager::getInstance()->get(file)->getTexture();
  file = getMatch()->getCharacter1()->getBasename();
  file += "_back.sprt";
  ss = SpritesheetManager::getInstance()->get(file);
  s.setTexture(*t);
  s.setPosition( 400, 600 );
  idSprite = ss->getAnimation(getMatch()->getCharacter1()->getAction() ).get(getMatch()->getCharacter1()->getFrame() );
  sprt = ss->getSprite(idSprite);
  if(sprt){
    s.setTextureRect(sf::IntRect(sprt->getPositionX(), sprt->getPositionY(), sprt->getWidth(), sprt->getHeight() ) );
    s.setOrigin( sprt->getHotpointX(), sprt->getHotpointY()  );
    s.scale(1.25, 1.25);
    m_window->draw(s);
  }
}

void Game::displayMatch(){
  //drawing order : 
  //background, opponent, opponent's spec, player's spec, player,
  displayGauges();
  displayClock();
  displayCharacters();
}
  


void Game::pause(const sf::Int64& t0){
  printf("pause\n");
  displayMatch();
  sf::Event event;
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::PAUSE ){
	setState(GameState::MATCH);
	m_timer = sf::microseconds(t0);
        break;
      }
    }

  }

}

/** Closes the game
 **/
void Game::close(){
  std::cout<<"closing"<<std::endl;
  TextureManager::getInstance()->remove("background.png");
  TextureManager::getInstance()->remove("sprites.png");
  m_window->close();
}



int main(){
  Game::getInstance()->init();
  return 0;
}

