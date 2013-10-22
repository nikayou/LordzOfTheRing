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

#include <sstream>
#include <string>
#include <vector>
#include <functional>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>

void SettingsState::update(){
  m_window->update();
}

void SettingsState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  sf::Color c(100, 100, 100);
  sf::RectangleShape r(sf::Vector2f(730, 80) );
  r.setPosition(35, 100);
  r.setFillColor(c );
  r.setOutlineThickness(1);
  r.setOutlineColor(sf::Color::Black );
  m_render->draw(r);
  r.setPosition(35, 200);
  r.setSize(sf::Vector2f(730, 150 ) );
  m_render->draw(r);
  r.setPosition(35, 370);
  m_render->draw(r);
  for(unsigned int i = 0; i < m_texts.size(); i++)
    m_render->draw(*m_texts[i]);
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  std::string s = "800x600";
  std::ostringstream oss;
  sf::Text t( s, *(f->getFont() ), 40);
  t.setColor(sf::Color::Black);
  unsigned int x_arg = 390+(610-390)/2;
  sf::FloatRect box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f+box.left, box.top/2);
  t.setPosition(x_arg, 120);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << (unsigned int)Config::getInstance()->getMusicVolume();
  oss <<"%";
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f+box.left, box.top/2);
  t.setPosition(x_arg, 220);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << (unsigned int)Config::getInstance()->getSoundVolume();
  oss << "%";
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f + box.left, box.top/2);
  t.setPosition(x_arg, 290);
  m_render->draw(t);

  m_window->draw();
}

bool SettingsState::enter(){
  m_render = Game::getInstance()->getRender();
  Game::getInstance()->setUpdating(true);
  m_container = new Container(m_render );
  m_window = Game::getInstance()->getGUI();
  m_window->setContentPane(m_container);
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  unsigned int fontsize = 56;
  sf::FloatRect fr;
  sf::Color c(110, 110, 110);
  //title
  sf::Text * l_title = new sf::Text("Settings", *(f->getFont() ), fontsize);
  fr = l_title->getLocalBounds();
  l_title->setPosition(400-fr.width/2, 10);
  l_title->setColor(sf::Color::Black);
  m_texts.push_back(l_title);
  //resolution
  sf::Text * l_res = new sf::Text("Resolution", *(f->getFont() ), fontsize);
  fr = l_res->getLocalBounds();
  l_res->setPosition(70, 140-fr.top-fr.height/2.0);
  l_res->setColor(sf::Color::Black);
  m_texts.push_back(l_res);
  Button * b_lres = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 120), c);
  b_lres->setText(sf::Text("<", *(f->getFont() ), fontsize) );
  b_lres->setTextToCenter();
  //b_lres->setAction();
  m_container->add(b_lres);
  m_buttons.push_back(b_lres);
  Button * b_rres = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 120), c);
  b_rres->setText(sf::Text(">", *(f->getFont() ), fontsize) );
  b_rres->setTextToCenter();
  // b_rres->setAction();
  m_container->add(b_rres);
  m_buttons.push_back(b_rres);
  m_fullscreen = new Checkbox(sf::Text("Fullscreen", *(f->getFont() ), fontsize*1/3) );
  m_fullscreen->setPosition(sf::Vector2f(660, 120) );
  m_fullscreen->setTextToCenter();
  //m_fullscreen->setChecked(Game::getInstance()->getMatch()->getFULLSCREEN() );
  m_container->add(m_fullscreen);
  //volume buttons
  sf::Text * l_music = new sf::Text("Music", *(f->getFont() ), fontsize);
  fr = l_music->getLocalBounds();
  l_music->setPosition(70, 240-fr.top-fr.height/2.0);
  l_music->setColor(sf::Color::Black);
  m_texts.push_back(l_music);
  Button * b_lmusic = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 220), c);
  b_lmusic->setText(sf::Text("-", *(f->getFont() ), fontsize) );
  b_lmusic->setTextToCenter();
  b_lmusic->setAction(  [this]()->void{Config::getInstance()->lessMusic(5);} );
  m_container->add(b_lmusic);
  m_buttons.push_back(b_lmusic);
  Button * b_rmusic = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 220), c);
  b_rmusic->setText(sf::Text("+", *(f->getFont() ), fontsize) );
  b_rmusic->setTextToCenter();  
  b_rmusic->setAction( [this]()->void{ Config::getInstance()->addMusic(5); } );
  m_container->add(b_rmusic);
  m_buttons.push_back(b_rmusic);
  // sound
  sf::Text * l_sound = new sf::Text("Sound", *(f->getFont() ), fontsize);
  fr = l_sound->getLocalBounds();
  l_sound->setPosition(70, 310-fr.top-fr.height/2.0);
  l_sound->setColor(sf::Color::Black);
  m_texts.push_back(l_sound);
  Button * b_lsound = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 290), c);
  b_lsound->setText(sf::Text("-", *(f->getFont() ), fontsize) );
  b_lsound->setTextToCenter();
  b_lsound->setAction(  [this]()->void{Config::getInstance()->lessSound(5);} );
  m_container->add(b_lsound);
  m_buttons.push_back(b_lsound);
  Button * b_rsound = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 290), c);
  b_rsound->setText(sf::Text("+", *(f->getFont() ), fontsize) );
  b_rsound->setTextToCenter();
  b_rsound->setAction( [this]()->void{ Config::getInstance()->addSound(5); } );
  m_container->add(b_rsound);
  m_buttons.push_back(b_rsound);
  // inputs 
  fontsize = 30;

  // state buttons
  fontsize = 56;
  Button * b_back = new Button(sf::Vector2u(60, 40), sf::Vector2f(270, 540), sf::Color(200, 100, 100) );
  b_back->setText(sf::Text("<-", *(f->getFont() ), fontsize) );
  b_back->setTextToCenter();
  b_back->setAction( [this]()->void{
      Config::getInstance()->loadFromFile(CONFIG_FILE);
      Game::getInstance()->getStateHandler()->change(new MainMenuState() );
    } );
  m_container->add(b_back);
  m_buttons.push_back(b_back);
  Button * b_ok = new Button(sf::Vector2u(60, 40), sf::Vector2f(530, 540), sf::Color(100,200,100) );
  b_ok->setText(sf::Text("OK", *(f->getFont() ), fontsize) );
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
  m_buttons.clear();
  s = m_texts.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_texts[i];
    m_texts[i] = NULL;
  }
  m_texts.clear();
  delete m_container;
  m_container = NULL;

}
