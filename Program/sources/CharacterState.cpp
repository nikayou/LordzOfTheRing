/*
  CharacterState is the gamestate of characters selection
*/
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
#include "../headers/OptionState.hpp"
#include "../headers/Texture.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <functional>
#include <vector>

const std::string CharacterState::m_charMenuID = "CHAR_MENU";

void CharacterState::confirmCharacters(){
  std::vector< Character * > chars = CharacterManager::getInstance()->getArray();
  Character c1 = *chars[m_index1];
  Character c2 = *chars[m_index2];
  Game::getInstance()->getMatch()->getPlayer1()->setCharacter(c1);
  Game::getInstance()->getMatch()->getPlayer2()->setCharacter(c2);
  Game::getInstance()->getMatch()->setLoaded(false);
  Game::getInstance()->getMatch()->setCurrentRound(0);
  Game::getInstance()->getStateHandler()->change(new MatchState() );
}

void CharacterState::update(){
  std::vector< Character * > chars = CharacterManager::getInstance()->getArray();
  unsigned int size = chars.size();
  sf::Event event;
  while( Game::getInstance()->updating() && m_window && m_window->getWindow() && m_window->getWindow()->pollEvent(event) ){

    if (event.type == sf::Event::Closed){
      Game::getInstance()->close();
      break;
    }
    /*
    if (event.type == sf::Event::MouseMoved){
      m_container->updateFocus();
      }*/
    if (event.type == sf::Event::MouseButtonPressed){
      if(event.mouseButton.button == sf::Mouse::Left){
	if(m_container->click( ) )
	  continue;
	else
	  break;
      }
    }
    if (event.type == sf::Event::KeyPressed){
      if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Left){
	m_container->focusUp();
	continue;
      }
      if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Right){
	m_container->focusDown();
	continue;
      }
      if(event.key.code == sf::Keyboard::Space){
	if(m_container->click())
	  continue;
	else
	  break;
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
  m_render->clear(sf::Color(120, 120, 120) );
  sf::Sprite s;
  sf::Texture * t;
  sf::RectangleShape r(sf::Vector2f(0, 600) );
  r.setPosition(400, 0);
  r.setOutlineThickness(2);
  r.setOutlineColor(sf::Color::Black);
  m_render->draw(r);
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
  //texts for stats
  for(unsigned int i = 0; i < m_texts.size(); i++){
    m_render->draw(*m_texts[i] );
  }
  m_window->draw();
 
}

bool CharacterState::enter(){
  Game::getInstance()->setUpdating(true);
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
  m_index1 = 0;
  m_index2 = 1;

  sf::Font * font = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  unsigned int fontsize = 40;
  Button * b_back = new Button(sf::Vector2u(25, 25), sf::Vector2f(390-25, 550), sf::Color(200, 100, 100) );
  b_back->setBorderThickness(1);
  b_back->setText(sf::Text("<-", *font, fontsize) );
  b_back->setTextToCenter();
  b_back->setAction( [this]()-> void{
      Game::getInstance()->getStateHandler()->change(new OptionState() );
    } );
  Button * b_play = new Button(sf::Vector2u(25, 25), sf::Vector2f(410, 550), sf::Color(100, 200, 100) );
  b_play->setBorderThickness(1);
  b_play->setText(sf::Text("->", *font, fontsize) );
  b_play->setTextToCenter();
  b_play->setAction( [this]()-> void{
      Game::getInstance()->getMusic()->stop();
      confirmCharacters();
      return;
    } );

  sf::FloatRect fr;
  sf::Text * l_health = new sf::Text("Health", *font, fontsize*2/3);
  fr = l_health->getLocalBounds();
  l_health->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  l_health->setPosition(230-100-fr.width/2, 480);
  l_health->setColor(sf::Color::Black);
  m_texts.push_back(l_health);
  sf::Text * l_stam = new sf::Text("Stamina", *font, fontsize*2/3);
  fr = l_stam->getLocalBounds();
  l_stam->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  l_stam->setPosition(230-100-fr.width/2, 480+32);
  l_stam->setColor(sf::Color::Black);
  m_texts.push_back(l_stam);
  sf::Text * l_atk = new sf::Text("Strength", *font, fontsize*2/3);
  fr = l_atk->getLocalBounds();
  l_atk->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  l_atk->setPosition(230-100-fr.width/2, 480+64);
  l_atk->setColor(sf::Color::Black);
  m_texts.push_back(l_atk);
  sf::Text * l_def = new sf::Text("Resistance", *font, fontsize*2/3);
  fr = l_def->getLocalBounds();
  l_def->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  l_def->setPosition(230-100-fr.width/2, 480+96);
  l_def->setColor(sf::Color::Black);
  m_texts.push_back(l_def);
  

  sf::Text * r_health = new sf::Text("Health", *font, fontsize*2/3);
  fr = r_health->getLocalBounds();
  r_health->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  r_health->setPosition(570+125+fr.width/2, 480);
  r_health->setColor(sf::Color::Black);
  m_texts.push_back(r_health);
  sf::Text * r_stam = new sf::Text("Stamina", *font, fontsize*2/3);
  fr = r_stam->getLocalBounds();
  r_stam->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  r_stam->setPosition(570+125+fr.width/2, 480+32);
  r_stam->setColor(sf::Color::Black);
  m_texts.push_back(r_stam);
  sf::Text * r_atk = new sf::Text("Strength", *font, fontsize*2/3);
  fr = r_atk->getLocalBounds();
  r_atk->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  r_atk->setPosition(570+125+fr.width/2, 480+64);
  r_atk->setColor(sf::Color::Black);
  m_texts.push_back(r_atk);
  sf::Text * r_def = new sf::Text("Resistance", *font, fontsize*2/3);
  fr = r_def->getLocalBounds();
  r_def->setOrigin(fr.left+fr.width/2, fr.top+fr.height/2);
  r_def->setPosition(570+125+fr.width/2, 480+96);
  r_def->setColor(sf::Color::Black);
  m_texts.push_back(r_def);
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_container->add(b_back);
  m_container->add(b_play);
  m_buttons.push_back(b_back);
  m_buttons.push_back(b_play);
  m_window = Game::getInstance()->getGUI();
  m_window->setContentPane(m_container);
  return true;
}

bool CharacterState::exit(){
  Game::getInstance()->setUpdating(false);
  return true;
}

void CharacterState::deleteAll(){
  for(unsigned int i = 0; i < m_texts.size(); i++){
    delete m_texts[i];
  }
  m_texts.clear();
  delete m_buttons[1];
  m_buttons[1] = NULL;
  delete m_buttons[0];
  m_buttons[0] = NULL;
  delete m_container;
  m_container = NULL;
}
