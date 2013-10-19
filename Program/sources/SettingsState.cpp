#include "../headers/SettingsState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/Config.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Checkbox.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/MainMenuState.hpp"

#include <string>
#include <vector>
#include <functional>

const std::string SettingsState::m_settingsID = "SETTINGS";

void SettingsState::update(){
  m_window->update();
}

void SettingsState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  m_window->draw();
}

bool SettingsState::enter(){
  m_render = Game::getInstance()->getRender();
  Game::getInstance()->setUpdating(true);
  m_container = new Container(m_render );
  m_window = Game::getInstance()->getGUI();
  m_window->setContentPane(m_container);
  sf::Font * f = FontManager::getInstance()->get(DEFAULT_FONT);
  unsigned int fontsize = 56;
 // state buttons
  fontsize = 56;
  Button * b_back = new Button(sf::Vector2u(60, 40), sf::Vector2f(270, 540), sf::Color(200, 100, 100) );
  b_back->setText(sf::Text("<-", *f, fontsize) );
  b_back->setTextToCenter();
  b_back->setAction( [this]()->void{
      Config::getInstance()->loadFromFile(CONFIG_FILE);
      Game::getInstance()->getStateHandler()->change(new MainMenuState() );
    } );
  m_container->add(b_back);
  m_buttons.push_back(b_back);
  Button * b_ok = new Button(sf::Vector2u(60, 40), sf::Vector2f(530, 540), sf::Color(100,200,100) );
  b_ok->setText(sf::Text("OK", *f, fontsize) );
  b_ok->setTextToCenter();
  b_ok->setAction( [this]()->void{
      Config::getInstance()->saveFile(CONFIG_FILE);
      Game::getInstance()->getStateHandler()->change(new MainMenuState() );
    } );
  m_container->add(b_ok);
  m_buttons.push_back(b_ok);
  return true;
}

bool SettingsState::exit(){

  Game::getInstance()->setUpdating(false);
  return true;
}

void SettingsState::deleteAll(){
  delete m_fullscreen;
  m_fullscreen = NULL;
  unsigned int s = m_buttons.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_buttons[i];
    m_buttons[i] = NULL;
  }
  s = m_texts.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_texts[i];
    m_texts[i] = NULL;
  }
  delete m_container;
  m_container = NULL;

}
