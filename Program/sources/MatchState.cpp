#include "../headers/MatchState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/Action.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/Game.hpp"
#include "../headers/SpritesheetManager.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>

const std::string MatchState::m_matchID = "MATCH";

void MatchState::update(){
  std::cout<<"updating matchState"<<std::endl;
  
  if(Game::getInstance()->getClock()->getElapsedTime().asSeconds() >= 1){
    std::cout<<"1 sec pasts"<<std::endl;
    Game::getInstance()->addTime(sf::seconds(1) );
    Game::getInstance()->getClock()->restart();
  }
  sf::Event event;
  while( Game::getInstance()->getWindow()->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      Game::getInstance()->close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(a == (action)0 )
	break;
      if(Action::getType(a) == Action::PAUSE ){
	//setState(GameState::PAUSE);
	break;
      }
      
      if(Game::getInstance()->getMatch()->getCharacter(Action::getDoer(a) )->getAction() == Action::NONE ){
	if(
	   !( ( (Action::getType(a) == Action::ATTACK_LEFT)
		||(Action::getType(a) == Action::ATTACK_MIDDLE)
		||(Action::getType(a) == Action::ATTACK_RIGHT) )
	      && !Game::getInstance()->getMatch()->getCharacter(Action::getDoer(a) )->doHit() )
	   )
	  Game::getInstance()->getMatch()->getCharacter(Action::getDoer(a) )->setAction( Action::getType(a) );
      }else{
	//player is already performing an action
      }
    }

  }
  Game::getInstance()->getMatch()->manage();
}


void MatchState::render(){
  std::cout<<"rendering matchState"<<std::endl;
  //printf("player1 : %p\n%s\n", getMatch()->getCharacter1(), getMatch()->getCharacter1()->toString().c_str() );
  // printf("player2 : %p\n%s\n", getMatch()->getCharacter2(), getMatch()->getCharacter2()->toString().c_str() );
  //drawing order : 
  //background, opponent, opponent's spec, player's spec, player,
  // background
  sf::Texture * t = TextureManager::getInstance()->get("background")->getTexture();
  sf::Sprite s;
  s.setTexture(*t);
  s.setPosition(sf::Vector2f(0, 0) );
  m_render->draw(s);
  displayCharacters();
  displayGauges();
  displayClock();
  m_window->draw();
}


void MatchState::displayGauges(){
  CharacterPlayed * c1 = Game::getInstance()->getMatch()->getCharacter1();
  CharacterPlayed * c2 = Game::getInstance()->getMatch()->getCharacter2();
  // health bars : red, green, border
  sf::Sprite s;
  sf::Texture * t;
  float width = Config::getInstance()->getWindowWidth();
  // opponent
  //opponent's spec
  //player's spec
  //player
  float scale = 2.0;
  s.scale(scale, scale);
  //p1 red
  t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 156, 16) );
  s.setPosition (sf::Vector2f(0, 26) );
  m_render->draw(s);
  //p1 green
  float percent = 0.0+c1->getCurrentHealth();
  percent /= c1->getHealth();
  percent *= 150;
  s.setTextureRect(sf::IntRect(0, 16, 3+(percent), 16) );
  m_render->draw(s);
  //p2 red
  s.setTextureRect(sf::IntRect(0, 0, 156, 16) );
  s.setPosition (sf::Vector2f(width-156*scale, 26) );
  m_render->draw(s);
  //p2 green
  percent = 0.0+c2->getCurrentHealth();
  percent /= c2->getHealth();
  percent *= 150;
  s.setPosition (sf::Vector2f(width-(156-(150-percent) )*scale, 26) );
  s.setTextureRect(sf::IntRect(0, 16, 4+percent, 16) );
  m_render->draw(s);
 
  //stamina bars
  s.setTextureRect(sf::IntRect(0, 32, 104, 8) );
  s.setPosition(sf::Vector2f(0, 70) );
  m_render->draw(s);
  percent = 0.0+c1->getCurrentStamina();
  percent /= c1->getStamina();
  percent *= 100;
  s.setTextureRect(sf::IntRect(0, 40, 2+percent, 6) );
  m_render->draw(s);
  //p2
  s.setTextureRect(sf::IntRect(0, 32, 104, 8) );
  s.setPosition(sf::Vector2f(width-104*scale, 70) );
  m_render->draw(s);
  percent = 0.0+c2->getCurrentStamina();
  percent /= c2->getStamina();
  percent *= 100;
  s.setPosition(sf::Vector2f(width-(104-(100-percent) )*scale, 70 ) );
  s.setTextureRect(sf::IntRect(0, 40, 3+percent, 6) );
  m_render->draw(s);
  
}

void MatchState::displayClock(){
  // chrono : back, second 100, second 10, second 1
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  float width = Config::getInstance()->getWindowWidth();
  s.setTextureRect(sf::IntRect(0, 46, 128, 64) );
  s.setPosition(width/2-64, 10);
  s.setTexture(*t);
  m_render->draw(s);  
  unsigned short time;
  time = Game::getInstance()->getMatch()->getTimePerRound()-(Game::getInstance()->getTimer()->asSeconds() );
  if(time > 0){ // if time is infinity, we are not displaying time
    //get time remaining
    //displaying 100'
    s.setTextureRect(sf::IntRect( (28*(time/100) ), 111, 28, 36) );
    s.setPosition(width/2-64+16, 10+ 14);
    m_render->draw(s);
    //displaying 10'
    s.setTextureRect(sf::IntRect((28*(time%100/10) ), 111, 28, 36) );
    s.setPosition(width/2-64+16+34, 10+ 14);
    m_render->draw(s);
    //displaying 1'
    s.setTextureRect(sf::IntRect((28*(time%10) ), 111, 28, 36) );
    s.setPosition(width/2-64+16+68, 10+ 14);
    m_render->draw(s);
  }
  
}

void MatchState::displayCharacters(){
  CharacterPlayed * c1 = Game::getInstance()->getMatch()->getCharacter1();
  CharacterPlayed * c2 = Game::getInstance()->getMatch()->getCharacter2();
  sf::Sprite s;
  Spritesheet * ss;
  sf::Texture * t;
  //displaying players' sprites : we need the image, the spritesheet, and the current frame of the action
  std::string file = "characters/";
  // character 2
  file += c2->getBasename();
  file += "_front.png";
  t = TextureManager::getInstance()->get(file)->getTexture();
  file = c2->getBasename();
  file += "_front.sprt";
  ss = SpritesheetManager::getInstance()->get(file);
  s.setTexture(*t);
  s.setPosition( 400, 400  );
  unsigned short idSprite = ss->getAnimation(c2->getAction() ).get(c2->getFrame() ); 
  Sprite * sprt = ss->getSprite(idSprite);
  if(sprt){
    s.setTextureRect(sf::IntRect(sprt->getPositionX(), sprt->getPositionY(), sprt->getWidth(), sprt->getHeight() ) );
    s.setOrigin( sprt->getHotpointX(), sprt->getHotpointY()  );
    s.scale(2.0, 2.0);
    m_render->draw(s);
  }
  // character 1
  file = "characters/";
  file += c1->getBasename();
  file += "_back.png";
  t = TextureManager::getInstance()->get(file)->getTexture();
  file = c1->getBasename();
  file += "_back.sprt";
  ss = SpritesheetManager::getInstance()->get(file);
  s.setTexture(*t);
  s.setPosition( 400, 600 );
  idSprite = ss->getAnimation(c1->getAction() ).get(c1->getFrame() );
  sprt = ss->getSprite(idSprite);
  if(sprt){
    s.setTextureRect(sf::IntRect(sprt->getPositionX(), sprt->getPositionY(), sprt->getWidth(), sprt->getHeight() ) );
    s.setOrigin( sprt->getHotpointX(), sprt->getHotpointY()  );
    s.scale(1.25, 1.25);
    m_render->draw(s);
  }
}


bool MatchState::enter(){
  std::cout<<"entering matchState"<<std::endl;
  Game::getInstance()->getMusic()->stop();
  sf::Texture * t = TextureManager::getInstance()->get("loading")->getTexture();
  sf::Sprite s;
  CharacterPlayed * c1 = Game::getInstance()->getMatch()->getCharacter1();
  CharacterPlayed * c2 =Game::getInstance()-> getMatch()->getCharacter2();
  s.setTexture(*t);
  s.setPosition(0,0);
  Game::getInstance()->getWindow()->draw(s);
  Game::getInstance()->getWindow()->display();
  TextureManager::getInstance()->get("background")->getTexture();
  TextureManager::getInstance()->get("sprites.png")->getTexture();
  std::string file = "characters/";
  // character 2
  file += c2->getBasename();
  file += "_front.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = c2->getBasename();
  file += "_front.sprt";
  SpritesheetManager::getInstance()->get(file);
  file = "characters/";
  file += c1->getBasename();
  file += "_back.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = c1->getBasename();
  file += "_back.sprt";
  SpritesheetManager::getInstance()->get(file);
  *Game::getInstance()->getTimer() = sf::microseconds(0);
  Game::getInstance()->getClock()->restart();
  if(Game::getInstance()->getMusic()->openFromFile("../../resources/audio/battle1.ogg") )
    Game::getInstance()->getMusic()->play();
  c1->gainStamina(600);
  c2->gainStamina(600);
  m_render = new sf::RenderTexture();
  m_render->create(800, 600);
  m_container = new Container(m_render );
  m_window = new GUIWindow (Game::getInstance()->getWindow(), m_container);
  return true;
}


bool MatchState::exit(){
  std::cout<<"exiting matchState"<<std::endl;
  return true;
}
