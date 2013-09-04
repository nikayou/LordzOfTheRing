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
#include "../headers/GUI_Bordered.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
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


#include <cstdio> //DELETE
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>


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
  Match match(&p1, &p2, 90, 3);
  setMatch(&match);
  sf::RenderTexture rt;
  rt.create(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() );
  m_render = &rt;
  //starting loop
  //setState(GameState::CHARACTER_SELECT);
  setState(GameState::MAIN_MENU);
  std::cout<<"Game initialized"<<std::endl;
  m_music.openFromFile("../../resources/audio/menu1.ogg");
  m_music.setVolume(Config::getInstance()->getMusicVolume() );
  m_music.play();
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
    //printf("Time : %f\nState : %d\n", getClock().getElapsedTime().asSeconds(), getState() );
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
      loopCharacterSelect( );
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
  
  init();
}

void Game::loopMainMenu(){
  m_render->clear(sf::Color::White);
  sf::Font * font = FontManager::getInstance()->get("../../resources/ArialPixel.ttf");
  Button b_play(sf::Vector2u(200, 70) , sf::Vector2f(300, 200), sf::Color(60, 60, 60) );
  b_play.setBorderThickness(1);
  b_play.setText(sf::Text("Play", *font, 32 ) );
  b_play.setTextToCenter();
  b_play.setAction( [ this]() -> void{
      loadCharacterSelect();
    } );
  Button b_net(sf::Vector2u(200, 70) , sf::Vector2f(300, 300), sf::Color(60, 60, 60) );
  b_net.setBorderThickness(1);
  b_net.setText(sf::Text("Net", *font, 32 ) );
  b_net.setTextToCenter();
  b_net.setAction( [&b_net, this]() ->void{
      
    } );
  Button b_options(sf::Vector2u(200, 70) , sf::Vector2f(300, 400), sf::Color(60, 60, 60) );
  b_options.setBorderThickness(1);
  b_options.setText(sf::Text("Options", *font, 32 ) );
  b_options.setTextToCenter();
  b_options.setAction( [this]()->void{
      Game::getInstance()->setState(GameState::OPTIONS_MENU);
    } );
  Button b_quit(sf::Vector2u(200, 70) , sf::Vector2f(300, 500), sf::Color(60, 60, 60) );
  b_quit.setBorderThickness(1);
  b_quit.setText(sf::Text("Quit", *font, 32 ) );
  b_quit.setTextToCenter();
  b_quit.setAction( [this]()->void{
      Game::getInstance()->close();
    }
    );
  Container ct(m_render);
  ct.add(&b_play);
  ct.add(&b_net);
  ct.add(&b_options);
  ct.add(&b_quit);
  GUIWindow gw(m_window, &ct);
  gw.draw();
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

}

void Game::loadCharacterSelect(){
  CharacterPlayed c1(* (CharacterManager::getInstance()->get("avrage.chara") )  );
  CharacterPlayed c2(* (CharacterManager::getInstance()->get("sdard.chara") )  );
  // getMatch()->getPlayer2()->setCharacter(c2);
  //getMatch()->getPlayer1()->setCharacter(c1);
  std::map<std::string, Character > chars = CharacterManager::getInstance()->getData();
  for(std::map<std::string, Character >::iterator it = chars.begin() ; it != chars.end() ; ++it)
    {
      std::string file = "characters/"+it->second.getBasename();
      file += "_menu.png";
      if(TextureManager::getInstance()->get(file) != NULL){
	TextureManager::getInstance()->remove(it->first);
      }
    }
  CharacterManager::getInstance()->computeArray();
  Game::getInstance()->setState(GameState::CHARACTER_SELECT);
}

void Game::loopCharacterSelect(){
  std::vector< Character * > chars = CharacterManager::getInstance()->getArray();
  unsigned int size = chars.size();
  sf::Event event;
  static unsigned int index1 = 0, index2 = 0;
  
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      if(event.key.code == sf::Keyboard::Space){
	CharacterPlayed c1 = (*chars[index1]);
	CharacterPlayed c2 = (*chars[index2]);
	getMatch()->getPlayer1()->setCharacter(c1);
	getMatch()->getPlayer2()->setCharacter(c2);
	loadMatch();
	return;
      }
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::ATTACK_MIDDLE ){
        if(Action::getDoer(a) == 0){
	  index1 = (index1 == 0 )?size-1:index1-1;
	}else{
	  index2 = (index2 == 0 )?size-1:index2-1;
	}
      }
      if(Action::getType(a) == Action::DODGE_MIDDLE ){
        if(Action::getDoer(a) == 0){
	  index1 = (index1 == size-1 )?0:index1+1;
	}else{
	  index2 = (index2 == size-1 )?0:index2+1;
	}
      }
    }
  }
  m_render->clear(sf::Color::Black);
  sf::Sprite s;
  sf::Texture * t;
  Container ct(m_render);
  ct.setPosition(0, 0);
  GUIWindow gw(m_window, &ct);
  //displaying characters labels
  float scale = 2.0;
  s.scale(scale, scale);
  s.setPosition(sf::Vector2f(400, -16) );
  s.move(0, 32*scale);
  for(std::vector< Character * >::iterator it = chars.begin() ; it != chars.end() ; ++it)
    {
      std::string tex = "characters/" + (*it)->getBasename() + "_menu.png";
      t = TextureManager::getInstance()->get(tex)->getTexture();
      s.setTexture(*t);
      s.setTextureRect(sf::IntRect(0, 0, 32, 32 ) );
      s.setOrigin(16, 16);
      s.setScale(1, 1);
      m_render->draw(s);
      t = TextureManager::getInstance()->get("sprites.png")->getTexture();
      s.setTextureRect(sf::IntRect(156, 0, 32, 32 ) );
      s.setTexture(*t);
      s.scale(scale, scale);
      m_render->draw(s);
      s.move(0, 32*scale);
    }	
  //displaying little arrows 
  s.setOrigin(3, 5);
  s.setTextureRect(sf::IntRect(188, 0, 6, 9) );
  s.setPosition(sf::Vector2f(400-20*scale, -16+(32*scale*(index1+1)) ) );
  m_render->draw(s);
  s.setTextureRect(sf::IntRect(188, 9, 6, 9) );
  s.setPosition(sf::Vector2f(400+20*scale, -16+(32*scale*(index2+1)) ) );
  m_render->draw(s);
  //displaying stats rulers
  t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(128, 46, 99, 9) );
  s.setOrigin(45, 5);
  s.setPosition(sf::Vector2f(230, 480) );
  m_render->draw(s);  
  s.move(0, 32);
  m_render->draw(s);  
  s.move(0, 32);
  m_render->draw(s);  
  s.move(0, 32);
  m_render->draw(s);  
  s.setPosition(sf::Vector2f(570, 480) );
  m_render->draw(s);  
  s.move(0, 32);
  m_render->draw(s);  
  s.move(0, 32);
  m_render->draw(s);  
  s.move(0, 32);
  m_render->draw(s);
  //displaying stats markers
  s.setTextureRect(sf::IntRect(128, 55, 3, 13) );
  s.setOrigin(2, 7);
  s.setPosition(sf::Vector2f(230-(40*scale), 480) );
  unsigned short value = (unsigned short)(Stats::baseHealth(chars[index1]->getHealth() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseStamina(chars[index1]->getStamina() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseResistance(chars[index1]->getResistance() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseAttack(chars[index1]->getAttack() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  //p2
  s.setPosition(sf::Vector2f(570-(40*scale), 480) );
  value = (unsigned short)(Stats::baseHealth(chars[index2]->getHealth() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseStamina(chars[index2]->getStamina() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseResistance(chars[index2]->getResistance() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseAttack(chars[index2]->getAttack() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);

  sf::Font * font = FontManager::getInstance()->get("../../resources/ArialPixel.ttf");
  Button b_back(sf::Vector2u(25, 25), sf::Vector2f(370, 550), sf::Color(100, 50, 50) );
  b_back.setBorderThickness(1);
  b_back.setText(sf::Text("<-", *font, 16) );
  b_back.setTextToCenter();
  b_back.setAction( [this]()-> void{
      Game::getInstance()->setState(GameState::MAIN_MENU);
    } );
  Button b_play(sf::Vector2u(25, 25), sf::Vector2f(430, 550), sf::Color(50,50, 100) );
  b_play.setBorderThickness(1);
  b_play.setText(sf::Text("->", *font, 16) );
  b_play.setTextToCenter();
  b_play.setAction( [this]()-> void{
      Game::getInstance()->loadMatch();
    } );
  gw.getContentPane()->add(&b_back);
  gw.getContentPane()->add(&b_play);
  gw.open(false);
  gw.draw();
}

void Game::loadMatch(){
  m_music.stop();
  m_window->clear(sf::Color::Black);
  sf::Texture * t = TextureManager::getInstance()->get("loading")->getTexture();
  sf::Sprite s;
  CharacterPlayed * c1 = getMatch()->getCharacter1();
  CharacterPlayed * c2 = getMatch()->getCharacter2();
  s.setTexture(*t);
  s.setPosition(0,0);
  m_window->draw(s);
  m_window->display();
  TextureManager::getInstance()->get("background")->getTexture();
  TextureManager::getInstance()->get("sprites.png")->getTexture();
  std::string file = "characters/";
  // character 2
  unsigned int frame = c2->getFrame();
  file += c2->getBasename();
  file += "_front.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = c2->getBasename();
  file += "_front.sprt";
  SpritesheetManager::getInstance()->get(file);
  frame = c1->getFrame();
  file = "characters/";
  file += c1->getBasename();
  file += "_back.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = c1->getBasename();
  file += "_back.sprt";
  SpritesheetManager::getInstance()->get(file);
  m_window->clear(sf::Color::Black);
  m_timer = sf::microseconds(0);
  m_clock.restart();
  if(m_music.openFromFile("../../resources/audio/battle1.ogg") )
    m_music.play();
  c1->gainStamina(600);
  c2->gainStamina(600);
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
	if(
	   !( ( (Action::getType(a) == Action::ATTACK_LEFT)
		||(Action::getType(a) == Action::ATTACK_MIDDLE)
		||(Action::getType(a) == Action::ATTACK_RIGHT) )
	      && !getMatch()->getCharacter(Action::getDoer(a) )->doHit() )
	   )
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
  CharacterPlayed * c1 = getMatch()->getCharacter1();
  CharacterPlayed * c2 = getMatch()->getCharacter2();
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
  m_window->draw(s);
  //p1 green
  float percent = 0.0+c1->getCurrentHealth();
  percent /= c1->getHealth();
  percent *= 150;
  std::cout<<"health : "<<percent<<"%"<<std::endl;
  s.setTextureRect(sf::IntRect(0, 16, 3+(percent), 16) );
  m_window->draw(s);
  //p2 red
  s.setTextureRect(sf::IntRect(0, 0, 156, 16) );
  s.setPosition (sf::Vector2f(width-156*scale, 26) );
  m_window->draw(s);
  //p2 green
  percent = 0.0+c2->getCurrentHealth();
  percent /= c2->getHealth();
  percent *= 150;
  std::cout<<"health : "<<percent<<"%"<<std::endl;
  s.setPosition (sf::Vector2f(width-(156-(150-percent) )*scale, 26) );
  s.setTextureRect(sf::IntRect(0, 16, 4+percent, 16) );
  m_window->draw(s);
  
  //stamina bars
  s.setTextureRect(sf::IntRect(0, 32, 104, 8) );
  s.setPosition(sf::Vector2f(0, 70) );
  m_window->draw(s);
  percent = 0.0+c1->getCurrentStamina();
  percent /= c1->getStamina();
  percent *= 100;
  std::cout<<"Stamina : "<<percent<<"%"<<std::endl;
  s.setTextureRect(sf::IntRect(0, 40, 2+percent, 6) );
  m_window->draw(s);
  //p2
  s.setTextureRect(sf::IntRect(0, 32, 104, 8) );
  s.setPosition(sf::Vector2f(width-104*scale, 70) );
  m_window->draw(s);
  percent = 0.0+c2->getCurrentStamina();
  percent /= c2->getStamina();
  percent *= 100;
  std::cout<<"Stamina : "<<c2->getCurrentStamina()<<" -> "<<percent<<"%"<<std::endl;
  s.setPosition(sf::Vector2f(width-(104-(100-percent) )*scale, 70 ) );
  s.setTextureRect(sf::IntRect(0, 40, 3+percent, 6) );
  m_window->draw(s);
  
}

void Game::displayClock(){
  // chrono : back, second 100, second 10, second 1
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  float width = Config::getInstance()->getWindowWidth();
  s.setTextureRect(sf::IntRect(0, 46, 128, 64) );
  s.setPosition(width/2-64, 10);
  s.setTexture(*t);
  m_window->draw(s);  
  unsigned short time;
  time = getMatch()->getTimePerRound()-(getTimer().asSeconds() );
  if(time > 0){ // if time is infinity, we are not displaying time
    //get time remaining
    //displaying 100'
    s.setTextureRect(sf::IntRect( (28*(time/100) ), 111, 28, 36) );
    s.setPosition(width/2-64+16, 10+ 14);
    m_window->draw(s);
    //displaying 10'
    s.setTextureRect(sf::IntRect((28*(time%100/10) ), 111, 28, 36) );
    s.setPosition(width/2-64+16+34, 10+ 14);
    m_window->draw(s);
    //displaying 1'
    s.setTextureRect(sf::IntRect((28*(time%10) ), 111, 28, 36) );
    s.setPosition(width/2-64+16+68, 10+ 14);
    m_window->draw(s);
  }
  
}

void Game::displayCharacters(){
  CharacterPlayed * c1 = getMatch()->getCharacter1();
  CharacterPlayed * c2 = getMatch()->getCharacter2();
  float width = Config::getInstance()->getWindowWidth();
  sf::Sprite s;
  Spritesheet * ss;
  sf::Texture * t;
  //displaying players' sprites : we need the image, the spritesheet, and the current frame of the action
  std::string file = "characters/";
  // character 2
  unsigned int frame = c2->getFrame();
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
    m_window->draw(s);
  }
  // character 2
  frame = c1->getFrame();
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
    m_window->draw(s);
  }
}

void Game::displayMatch(){
  //drawing order : 
  //background, opponent, opponent's spec, player's spec, player,
  // background
  sf::Texture * t = TextureManager::getInstance()->get("background")->getTexture();
  sf::Sprite s;
  s.setTexture(*t);
  s.setPosition(sf::Vector2f(0, 0) );
  m_window->draw(s);
  std::cout<<"displaying characters"<<std::endl;
  displayCharacters();
  std::cout<<"displayed characters"<<std::endl;
  displayGauges();
  displayClock();
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
  Game::getInstance()->splash();
  return 0;
}

