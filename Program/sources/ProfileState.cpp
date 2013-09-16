#include "../headers/ProfileState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/OptionState.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

const std::string ProfileState::m_profileID;

void ProfileState::update(){
  m_window->update();
}

void ProfileState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  m_window->draw();
}

bool ProfileState::enter(){
  //
  sf::Font * f = FontManager::getInstance()->get("../../resources/ArialPixel.ttf");
  //
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_window = new GUIWindow(Game::getInstance()->getWindow(), m_container);
// state buttons
  Button * b_back = new Button(sf::Vector2u(60, 40), sf::Vector2f(270, 540), sf::Color(200, 100, 100) );
  b_back->setText(sf::Text("<-", *f, 25) );
  b_back->setTextToCenter();
  b_back->setAction( [this]()->void{
      Game::getInstance()->getStateHandler()->change(new MainMenuState() );
    } );
  m_container->add(b_back);
  m_buttons.push_back(b_back);
  Button * b_ok = new Button(sf::Vector2u(60, 40), sf::Vector2f(530, 540), sf::Color(100,200,100) );
  b_ok->setText(sf::Text("->", *f, 25) );
  b_ok->setTextToCenter();
  b_ok->setAction( [this]()->void{
      Game::getInstance()->getStateHandler()->change(new OptionState() );
    } );
  m_container->add(b_ok);
  m_buttons.push_back(b_ok);
  return true;
}

bool ProfileState::exit(){
  return true;
}

void ProfileState::deleteAll(){

}
