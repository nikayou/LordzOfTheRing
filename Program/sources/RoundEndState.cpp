#include "../headers/RoundEndState.hpp"
#include "../headers/Config.hpp"
#include "../headers/Game.hpp"
#include "../headers/GameState.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream> //delete

const std::string RoundEndState::m_roundID = "ROUND";

void RoundEndState::update(){
  if(m_scale < 1){
    m_scale += 0.1;
    std::cout<<"new scale : "<<m_scale<<std::endl;
  }
}

void RoundEndState::render(){
  m_render->clear(sf::Color::Green);
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(8, 52, 8, 6) );
  s.scale(m_scale*5, m_scale*5);
  s.setOrigin(4, 3);
  //s.setPosition(Config::getInstance()->getWindowWidth()/2, Config::getInstance()->getWindowHeight()/2);
  s.setPosition(400, 300);
  m_render->draw(s);
  s.setTextureRect(sf::IntRect(128, 68, 16, 16) );
  s.setScale(m_scale, m_scale);
  s.setOrigin(8, 8);
  m_render->draw(s);
  m_window->draw();
}

bool RoundEndState::enter(){
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_window = new GUIWindow (Game::getInstance()->getWindow(), m_container);
  // play sound

  //collapse screen
  m_scale = 0;
  return true;
}

bool RoundEndState::exit(){
  //if we already did the number of rounds, the match ends
  return true;
}

 void RoundEndState::deleteAll(){
   delete m_container;
   m_container = NULL;
   delete m_window;
   m_window = NULL;
 }
