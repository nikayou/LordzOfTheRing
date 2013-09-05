#include "../headers/CharacterState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/CharacterManager.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/Match.hpp"
#include "../headers/MatchState.hpp"
#include "../headers/Texture.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>

const std::string CharacterState::m_charMenuID = "CHAR_MENU";

void CharacterState::confirmCharacters(){
  std::vector< Character * > chars = CharacterManager::getInstance()->getArray();
  Character c1 = *chars[m_index1];
  Character c2 = *chars[m_index2];
  Game::getInstance()->getMatch()->getPlayer1()->setCharacter(c1);
  Game::getInstance()->getMatch()->getPlayer2()->setCharacter(c2);
  Game::getInstance()->getStateHandler()->change(new MatchState() );
}

void CharacterState::update(){
  std::cout<<"updating char"<<std::endl;
  std::vector< Character * > chars = CharacterManager::getInstance()->getArray();
  unsigned int size = chars.size();
  sf::Event event;
  while( m_window->getWindow()->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      Game::getInstance()->close();
      return;
    }else if(event.type ==sf::Event::KeyPressed ){
      if(event.key.code == sf::Keyboard::Space){
	confirmCharacters();      
	Game::getInstance()->getStateHandler()->change(new MatchState() );
	return;
      }
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::ATTACK_MIDDLE ){
        if(Action::getDoer(a) == 0){
	  m_index1 = (m_index1 == 0 )?size-1:m_index1-1;
	}else{
	  m_index2 = (m_index2 == 0 )?size-1:m_index2-1;
	}
      }
      if(Action::getType(a) == Action::DODGE_MIDDLE ){
        if(Action::getDoer(a) == 0){
	  m_index1 = (m_index1 == size-1 )?0:m_index1+1;
	}else{
	  m_index2 = (m_index2 == size-1 )?0:m_index2+1;
	}
      }
    }
  }
  
}

void CharacterState::render(){
  std::cout<<"rendering char"<<std::endl;
  m_render->clear(sf::Color::Black);
  sf::Sprite s;
  sf::Texture * t;
  //displaying characters labels
  float scale = 2.0;
  s.scale(scale, scale);
  s.setPosition(sf::Vector2f(400, -16) );
  s.move(0, 32*scale);
  std::vector< Character * >  chars = (CharacterManager::getInstance()->getArray() );
  for(std::vector< Character * >::iterator it = chars.begin() ; it != chars.end() ; ++it)
    {
      std::string tex = "characters/" + (*it)->getBasename() + "_menu.png";
      t = TextureManager::getInstance()->get(tex)->getTexture();
      s.setTexture(*t);
      s.setTextureRect(sf::IntRect(0, 0, 32, 32 ) );
      s.setOrigin(16, 16);
      s.setScale(1, 1);
      m_container->getContent()->draw(s);
      t = TextureManager::getInstance()->get("sprites.png")->getTexture();
      s.setTextureRect(sf::IntRect(156, 0, 32, 32 ) );
      s.setTexture(*t);
      s.scale(scale, scale);
      m_container->getContent()->draw(s);
      s.move(0, 32*scale);
    }	
  //displaying little arrows 
  s.setOrigin(3, 5);
  s.setTextureRect(sf::IntRect(188, 0, 6, 9) );
  s.setPosition(sf::Vector2f(400-20*scale, -16+(32*scale*(m_index1+1)) ) );
  m_container->getContent()->draw(s);
  s.setTextureRect(sf::IntRect(188, 9, 6, 9) );
  s.setPosition(sf::Vector2f(400+20*scale, -16+(32*scale*(m_index2+1)) ) );
  m_container->getContent()->draw(s);
  //displaying stats rulers
  t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(128, 46, 99, 9) );
  s.setOrigin(45, 5);
  s.setPosition(sf::Vector2f(230, 480) );
  m_container->getContent()->draw(s);  
  s.move(0, 32);
  m_container->getContent()->draw(s);  
  s.move(0, 32);
  m_container->getContent()->draw(s);  
  s.move(0, 32);
  m_container->getContent()->draw(s);  
  s.setPosition(sf::Vector2f(570, 480) );
  m_container->getContent()->draw(s);  
  s.move(0, 32);
  m_container->getContent()->draw(s);  
  s.move(0, 32);
  m_container->getContent()->draw(s);  
  s.move(0, 32);
  m_container->getContent()->draw(s);
  //displaying stats markers
  s.setTextureRect(sf::IntRect(128, 55, 3, 13) );
  s.setOrigin(2, 7);
  s.setPosition(sf::Vector2f(230-(40*scale), 480) );
  unsigned short value = (unsigned short)(Stats::baseHealth(chars[m_index1]->getHealth() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseStamina(chars[m_index1]->getStamina() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseResistance(chars[m_index1]->getResistance() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseAttack(chars[m_index1]->getAttack() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  //p2
  s.setPosition(sf::Vector2f(570-(40*scale), 480) );
  value = (unsigned short)(Stats::baseHealth(chars[m_index2]->getHealth() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseStamina(chars[m_index2]->getStamina() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseResistance(chars[m_index2]->getResistance() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_container->getContent()->draw(s);
  s.move(-value, 32);
  value = (unsigned short)(Stats::baseAttack(chars[m_index2]->getAttack() ) );
  value *= 15*scale;
  s.move(value, 0);
  m_render->draw(s);
  m_window->draw();
 
}

bool CharacterState::enter(){
  CharacterPlayed c1(* (CharacterManager::getInstance()->get("avrage.chara") )  );
  CharacterPlayed c2(* (CharacterManager::getInstance()->get("sdard.chara") )  );
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
  //Game::getInstance()->setState(GameState::CHARACTER_SELECT);
  m_index1 = 0;
  m_index2 = 1;

  sf::Font * font = FontManager::getInstance()->get("../../resources/ArialPixel.ttf");
  Button * b_back = new Button(sf::Vector2u(25, 25), sf::Vector2f(370, 550), sf::Color(100, 50, 50) );
  b_back->setBorderThickness(1);
  b_back->setText(sf::Text("<-", *font, 16) );
  b_back->setTextToCenter();
  b_back->setAction( [this]()-> void{
      //Game::getInstance()->setState(GameState::MAIN_MENU);
    } );
  Button * b_play = new Button(sf::Vector2u(25, 25), sf::Vector2f(430, 550), sf::Color(50,50, 100) );
  b_play->setBorderThickness(1);
  b_play->setText(sf::Text("->", *font, 16) );
  b_play->setTextToCenter();
  b_play->setAction( [this]()-> void{
      confirmCharacters();
      Game::getInstance()->getStateHandler()->change(new MatchState() );
      return;
    } );
  m_render = new sf::RenderTexture();
  m_render->create(800, 600);
  m_container = new Container(m_render );
  m_container->add(b_back);
  m_container->add(b_play);
  m_buttons.push_back(b_back);
  m_buttons.push_back(b_play);
  m_window = new GUIWindow (Game::getInstance()->getWindow(), m_container);
  std::cout<<"loaded menu char"<<std::endl;
  return true;
}

bool CharacterState::exit(){
  std::cout << "exiting Charstate\n";
  /* delete m_window;
  delete m_container;
  delete m_render;
  delete m_buttons[1];
  delete m_buttons[0];*/

  return true;
}
