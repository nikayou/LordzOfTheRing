/* Main menu gamestate */
#include "../headers/MainMenuState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/SettingsState.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <functional>

void MainMenuState::update(){
  m_window->update();
}

void MainMenuState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  Font * f = FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() );
  sf::Text t("Lordz Of The Ring", *(f->getFont()), 120);
  sf::FloatRect box = t.getLocalBounds();
  t.setOrigin(box.left+box.width/2.0f, box.top+box.height/2.0f);
  t.setPosition(400, 100);
  m_render->draw(t);
  m_window->draw();
}

bool MainMenuState::enter(){
  Game::getInstance()->setUpdating(true);
  Font * font = FontManager::getInstance()->get("laff_riot.ttf");
  sf::Color c(100, 100, 100);
  unsigned int fontsize = 40;
  static float x = 500, y = 200, space = 30;
  static unsigned int button_w = 200, button_h = 70;
  Button * b_play = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x,y), c );
  b_play->setBorderThickness(1);
  b_play->setText(sf::Text("Play", *(font->getFont() ), fontsize ) );
  b_play->setTextToCenter();
  b_play->setAction( [ this]() -> void{
      Game::getInstance()->getStateHandler()->change( new OptionState() ) ;
    } );
  Button * b_net = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x, y+button_h+space), c );
  b_net->setBorderThickness(1);
  b_net->setText(sf::Text("Net", *(font->getFont() ), fontsize ) );
  b_net->setTextToCenter();
  b_net->setAction( [&b_net, this]() ->void{
      //
    } );
  Button * b_options = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x, y+(button_h+space)*2), c );
  b_options->setBorderThickness(1);
  b_options->setText(sf::Text("Options", *(font->getFont() ), fontsize ) );
  b_options->setTextToCenter();
  b_options->setAction( [this]()->void{
      Game::getInstance()->getStateHandler()->change(new SettingsState() );
    } );
  Button * b_quit = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x, y+(button_h+space)*3), c );
  b_quit->setBorderThickness(1);
  b_quit->setText(sf::Text("Quit", *(font->getFont() ), fontsize ) );
  b_quit->setTextToCenter();
  b_quit->setCloser(true);
  b_quit->setAction( [this]()->void{
      Game::getInstance()->close();
    }
    );
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_container->add(b_play);
  m_container->add(b_net);
  m_container->add(b_options);
  m_container->add(b_quit);
  m_buttons.push_back(b_play);
  m_buttons.push_back(b_net);
  m_buttons.push_back(b_options);
  m_buttons.push_back(b_quit);
  m_window = Game::getInstance()->getGUI();
  m_window->setContentPane(m_container);
  return true;
}

bool MainMenuState::exit(){
  Game::getInstance()->setUpdating(false);
  return true;
}

void MainMenuState::deleteAll(){
  delete m_container;
  m_container = NULL;
  unsigned int s = m_buttons.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_buttons[i];
    m_buttons[i] = NULL;
  }
  m_buttons.clear();
}
