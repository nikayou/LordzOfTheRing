/* Main menu gamestate */
#include "../headers/MainMenuState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/OptionState.hpp"

#include <SFML/Graphics/RenderTexture.hpp>


const std::string MainMenuState::m_mainMenuID = "MAIN_MENU";

void MainMenuState::update(){
  m_window->update();
}

void MainMenuState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  sf::Font * f = FontManager::getInstance()->get("../../resources/chubby_cheeks.ttf");
  sf::Text t("Lordz Of The Ring", *f, 120);
  sf::FloatRect box = t.getLocalBounds();
  t.setOrigin(box.left+box.width/2.0f, box.top+box.height/2.0f);
  t.setPosition(400, 100);
  m_render->draw(t);
  m_window->draw();
}

bool MainMenuState::enter(){
  sf::Font * font = FontManager::getInstance()->get("../../resources/laff_riot.ttf");
  sf::Color c(100, 100, 100);
  unsigned int fontsize = 40;
  static float x = 500, y = 200, space = 30;
  static unsigned int button_w = 200, button_h = 70;
  Button * b_play = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x,y), c );
  b_play->setBorderThickness(1);
  b_play->setText(sf::Text("Play", *font, fontsize ) );
  b_play->setTextToCenter();
  b_play->setAction( [ this]() -> void{
      Game::getInstance()->getStateHandler()->change( new OptionState() ) ;
    } );
  Button * b_net = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x, y+button_h+space), c );
  b_net->setBorderThickness(1);
  b_net->setText(sf::Text("Net", *font, fontsize ) );
  b_net->setTextToCenter();
  b_net->setAction( [&b_net, this]() ->void{
      //
    } );
  Button * b_options = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x, y+(button_h+space)*2), c );
  b_options->setBorderThickness(1);
  b_options->setText(sf::Text("Options", *font, fontsize ) );
  b_options->setTextToCenter();
  b_options->setAction( [this]()->void{
      //Game::getInstance()->getStateHandler()->change(new OptionMenu() );
    } );
  Button * b_quit = new Button(sf::Vector2u(button_w, button_h) , sf::Vector2f(x, y+(button_h+space)*3), c );
  b_quit->setBorderThickness(1);
  b_quit->setText(sf::Text("Quit", *font, fontsize ) );
  b_quit->setTextToCenter();
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
  m_window = new GUIWindow(Game::getInstance()->getWindow(), m_container);
  return true;
}

bool MainMenuState::exit(){
  return true;
}

void MainMenuState::deleteAll(){
  delete m_buttons[3];
  delete m_buttons[2];
  delete m_buttons[1];
  delete m_buttons[0];
  m_buttons[3] = NULL;
  m_buttons[2] = NULL;
  m_buttons[1] = NULL;
  m_buttons[0] = NULL;
  m_buttons.clear();
  delete m_container;
  m_container = NULL;
  delete m_window;
  m_window = NULL;
}
