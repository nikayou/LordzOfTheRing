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

void SettingsState::updateInputButtons(){
  unsigned int fontsize = 30;
  action a;
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  a = actionToByte(Action::ATTACK_LEFT, Action::PLAYER1, Action::PLAYER2);
  m_inputButtons[0]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[0]->setTextToCenter();
  a = actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER1, Action::PLAYER2);
  m_inputButtons[1]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[1]->setTextToCenter();
  a = actionToByte(Action::ATTACK_RIGHT, Action::PLAYER1, Action::PLAYER2);
  m_inputButtons[2]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[2]->setTextToCenter();
  a = actionToByte(Action::DODGE_LEFT, Action::PLAYER1, Action::PLAYER1);
  m_inputButtons[3]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[3]->setTextToCenter();
  a = actionToByte(Action::DODGE_MIDDLE, Action::PLAYER1, Action::PLAYER1);
  m_inputButtons[4]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[4]->setTextToCenter();
  a = actionToByte(Action::DODGE_RIGHT, Action::PLAYER1, Action::PLAYER1);
  m_inputButtons[5]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[5]->setTextToCenter();
  //
  a = actionToByte(Action::ATTACK_LEFT, Action::PLAYER2, Action::PLAYER1);
  m_inputButtons[6]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[6]->setTextToCenter();
  a = actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER2, Action::PLAYER1);
  m_inputButtons[7]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[7]->setTextToCenter();
  a = actionToByte(Action::ATTACK_RIGHT, Action::PLAYER2, Action::PLAYER1);
  m_inputButtons[8]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[8]->setTextToCenter();
  a = actionToByte(Action::DODGE_LEFT, Action::PLAYER2, Action::PLAYER2);
  m_inputButtons[9]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[9]->setTextToCenter();
  a = actionToByte(Action::DODGE_MIDDLE, Action::PLAYER2, Action::PLAYER2);
  m_inputButtons[10]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[10]->setTextToCenter();
  a = actionToByte(Action::DODGE_RIGHT, Action::PLAYER2, Action::PLAYER2);
  m_inputButtons[11]->setText(sf::Text(Config::getInstance()->keyToString(Config::getInstance()->getKey(a) ), *(f->getFont() ), fontsize) );
  m_inputButtons[11]->setTextToCenter();
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
  r.setSize(sf::Vector2f(730, 160 ) );
  m_render->draw(r);
  r.setPosition(35, 370);
  m_render->draw(r);
  for(unsigned int i = 0; i < m_texts.size(); i++)
    m_render->draw(*m_texts[i]);
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  unsigned int fontsize = 40;
  std::string s = "800x600";
  static std::ostringstream oss;
  oss.str("");
  oss.clear();
  oss << Config::getInstance()->getWindowWidth();
  oss << "x";
  oss << Config::getInstance()->getWindowHeight();
  sf::Text t( oss.str(), *(f->getFont() ), fontsize);
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
  panel1();
  panel2();
  panel3();
  updateInputButtons();
  // state buttons
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

void SettingsState::panel1(){
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  unsigned int fontsize = 56;
  sf::FloatRect fr;
  sf::Color c(110, 110, 110);
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
  m_fullscreen->setPosition(sf::Vector2f(660, 125) );
  m_fullscreen->setTextToCenter();
  //m_fullscreen->setChecked(Game::getInstance()->getMatch()->getFULLSCREEN() );
  m_container->add(m_fullscreen);
}

void SettingsState::panel2(){
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  unsigned int fontsize = 56;
  sf::FloatRect fr;
  sf::Color c(110, 110, 110);
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
}

void SettingsState::panel3(){
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  unsigned int fontsize = 56;
  sf::FloatRect fr;
  sf::Color c(110, 110, 110);
  // inputs - subrect :680*100, dim : 730*150, dec : 35,370
  fontsize = 15;
  sf::Text * l_p1 = new sf::Text("Player 1", *(f->getFont() ), fontsize);
  fr = l_p1->getLocalBounds();
  l_p1->setPosition(60, 380-fr.top-fr.height/2.0-3);
  l_p1->setColor(sf::Color::Black);
  m_texts.push_back(l_p1);
  sf::Text * l_p2 = new sf::Text("Player 2", *(f->getFont() ), fontsize);
  fr = l_p2->getLocalBounds();
  l_p2->setPosition(400, 380-fr.top-fr.height/2.0-3);
  l_p2->setColor(sf::Color::Black);
  m_texts.push_back(l_p2);
  fontsize = 25;
  Button * b_1al = new Button(sf::Vector2u(30, 30), sf::Vector2f(60, 388), c);
  b_1al->setText(sf::Text("7", *(f->getFont() ), fontsize) );
  b_1al->setTextToCenter();
  b_1al->setAction( [this]()->void{ } );
  m_container->add(b_1al);
  m_inputButtons.push_back(b_1al);
  sf::Text * l_1al = new sf::Text("Left Attack", *(f->getFont() ), fontsize);
  fr = l_1al->getLocalBounds();
  l_1al->setPosition(60+35, 388+15-fr.top-fr.height/2.0);
  l_1al->setColor(sf::Color::Black);
  m_texts.push_back(l_1al);
  Button * b_1am = new Button(sf::Vector2u(30, 30), sf::Vector2f(60, 438), c);
  b_1am->setText(sf::Text("8", *(f->getFont() ), fontsize) );
  b_1am->setTextToCenter();
  b_1am->setAction( [this]()->void{ } );
  m_container->add(b_1am);
  m_inputButtons.push_back(b_1am);
  sf::Text * l_1am = new sf::Text("Middle Attack", *(f->getFont() ), fontsize);
  fr = l_1am->getLocalBounds();
  l_1am->setPosition(60+35, 438+15-fr.top-fr.height/2.0);
  l_1am->setColor(sf::Color::Black);
  m_texts.push_back(l_1am);
  Button * b_1ar = new Button(sf::Vector2u(30, 30), sf::Vector2f(60, 488), c);
  b_1ar->setText(sf::Text("9", *(f->getFont() ), fontsize) );
  b_1ar->setTextToCenter();
  b_1ar->setAction( [this]()->void{ } );
  m_container->add(b_1ar);
  m_inputButtons.push_back(b_1ar);
  sf::Text * l_1ar = new sf::Text("Right Attack", *(f->getFont() ), fontsize);
  fr = l_1ar->getLocalBounds();
  l_1ar->setPosition(60+35, 488+15-fr.top-fr.height/2.0);
  l_1ar->setColor(sf::Color::Black);
  m_texts.push_back(l_1ar);
  Button * b_1dl = new Button(sf::Vector2u(30, 30), sf::Vector2f(230, 388), c);
  b_1dl->setText(sf::Text("4", *(f->getFont() ), fontsize) );
  b_1dl->setTextToCenter();
  b_1dl->setAction( [this]()->void{ } );
  m_container->add(b_1dl);
  m_inputButtons.push_back(b_1dl);
  sf::Text * l_1dl = new sf::Text("Left Dodge", *(f->getFont() ), fontsize);
  fr = l_1dl->getLocalBounds();
  l_1dl->setPosition(230+35, 388+15-fr.top-fr.height/2.0);
  l_1dl->setColor(sf::Color::Black);
  m_texts.push_back(l_1dl);
  Button * b_1dm = new Button(sf::Vector2u(30, 30), sf::Vector2f(230, 438), c);
  b_1dm->setText(sf::Text("5", *(f->getFont() ), fontsize) );
  b_1dm->setTextToCenter();
  b_1dm->setAction( [this]()->void{ } );
  m_container->add(b_1dm);
  m_inputButtons.push_back(b_1dm);
  sf::Text * l_1dm = new sf::Text("Middle Dodge", *(f->getFont() ), fontsize);
  fr = l_1dm->getLocalBounds();
  l_1dm->setPosition(230+35, 438+15-fr.top-fr.height/2.0);
  l_1dm->setColor(sf::Color::Black);
  m_texts.push_back(l_1dm);
  Button * b_1dr = new Button(sf::Vector2u(30, 30), sf::Vector2f(230, 488), c);
  b_1dr->setText(sf::Text("6", *(f->getFont() ), fontsize) );
  b_1dr->setTextToCenter();
  b_1dr->setAction( [this]()->void{ } );
  m_container->add(b_1dr);
  m_inputButtons.push_back(b_1dr);
  sf::Text * l_1dr = new sf::Text("Right Dodge", *(f->getFont() ), fontsize);
  fr = l_1dr->getLocalBounds();
  l_1dr->setPosition(230+35, 488+15-fr.top-fr.height/2.0);
  l_1dr->setColor(sf::Color::Black);
  m_texts.push_back(l_1dr);
  //p2
  Button * b_2al = new Button(sf::Vector2u(30, 30), sf::Vector2f(400, 388), c);
  b_2al->setText(sf::Text("1", *(f->getFont() ), fontsize) );
  b_2al->setTextToCenter();
  b_2al->setAction( [this]()->void{ } );
  m_container->add(b_2al);
  m_inputButtons.push_back(b_2al);
  sf::Text * l_2al = new sf::Text("Left Attack", *(f->getFont() ), fontsize);
  fr = l_2al->getLocalBounds();
  l_2al->setPosition(400+35, 388+15-fr.top-fr.height/2.0);
  l_2al->setColor(sf::Color::Black);
  m_texts.push_back(l_2al);
  Button * b_2am = new Button(sf::Vector2u(30, 30), sf::Vector2f(400, 438), c);
  b_2am->setText(sf::Text("2", *(f->getFont() ), fontsize) );
  b_2am->setTextToCenter();
  b_2am->setAction( [this]()->void{ } );
  m_container->add(b_2am);
  m_inputButtons.push_back(b_2am);
  sf::Text * l_2am = new sf::Text("Middle Attack", *(f->getFont() ), fontsize);
  fr = l_2am->getLocalBounds();
  l_2am->setPosition(400+35, 438+15-fr.top-fr.height/2.0);
  l_2am->setColor(sf::Color::Black);
  m_texts.push_back(l_2am);
  Button * b_2ar = new Button(sf::Vector2u(30, 30), sf::Vector2f(400, 488), c);
  b_2ar->setText(sf::Text("3", *(f->getFont() ), fontsize) );
  b_2ar->setTextToCenter();
  b_2ar->setAction( [this]()->void{ } );
  m_container->add(b_2ar);
  m_inputButtons.push_back(b_2ar);
  sf::Text * l_2ar = new sf::Text("Right Attack", *(f->getFont() ), fontsize);
  fr = l_2ar->getLocalBounds();
  l_2ar->setPosition(400+35, 488+15-fr.top-fr.height/2.0);
  l_2ar->setColor(sf::Color::Black);
  m_texts.push_back(l_2ar);
  Button * b_2dl = new Button(sf::Vector2u(30, 30), sf::Vector2f(570, 388), c);
  b_2dl->setText(sf::Text("0", *(f->getFont() ), fontsize) );
  b_2dl->setTextToCenter();
  b_2dl->setAction( [this]()->void{ } );
  m_container->add(b_2dl);
  m_inputButtons.push_back(b_2dl);
  sf::Text * l_2dl = new sf::Text("Left Dodge", *(f->getFont() ), fontsize);
  fr = l_2dl->getLocalBounds();
  l_2dl->setPosition(570+35, 388+15-fr.top-fr.height/2.0);
  l_2dl->setColor(sf::Color::Black);
  m_texts.push_back(l_2dl);
  Button * b_2dm = new Button(sf::Vector2u(30, 30), sf::Vector2f(570, 438), c);
  b_2dm->setText(sf::Text("w", *(f->getFont() ), fontsize) );
  b_2dm->setTextToCenter();
  b_2dm->setAction( [this]()->void{ } );
  m_container->add(b_2dm);
  m_inputButtons.push_back(b_2dm);
  sf::Text * l_2dm = new sf::Text("Middle Dodge", *(f->getFont() ), fontsize);
  fr = l_2dm->getLocalBounds();
  l_2dm->setPosition(570+35, 438+15-fr.top-fr.height/2.0);
  l_2dm->setColor(sf::Color::Black);
  m_texts.push_back(l_2dm);
  Button * b_2dr = new Button(sf::Vector2u(30, 30), sf::Vector2f(570, 488), c);
  b_2dr->setText(sf::Text("x", *(f->getFont() ), fontsize) );
  b_2dr->setTextToCenter();
  b_2dr->setAction( [this]()->void{ } );
  m_container->add(b_2dr);
  m_inputButtons.push_back(b_2dr);
  sf::Text * l_2dr = new sf::Text("Right Dodge", *(f->getFont() ), fontsize);
  fr = l_2dr->getLocalBounds();
  l_2dr->setPosition(570+35, 488+15-fr.top-fr.height/2.0);
  l_2dr->setColor(sf::Color::Black);
  m_texts.push_back(l_2dr);
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
s = m_inputButtons.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_inputButtons[i];
    m_inputButtons[i] = NULL;
  }
  m_inputButtons.clear();
  s = m_texts.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_texts[i];
    m_texts[i] = NULL;
  }
  m_texts.clear();
  delete m_container;
  m_container = NULL;

}
