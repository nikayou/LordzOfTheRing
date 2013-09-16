/* Main menu gamestate */
#include "../headers/MainMenuState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/ProfileState.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

const std::string MainMenuState::m_mainMenuID = "MAIN_MENU";

void MainMenuState::update(){
  m_window->update();
}

void MainMenuState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  m_window->draw();
}

bool MainMenuState::enter(){
  sf::Font * font = FontManager::getInstance()->get("../../resources/ArialPixel.ttf");
  sf::Color c(100, 100, 100);
  Button * b_play = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 200), c );
  b_play->setBorderThickness(1);
  b_play->setText(sf::Text("Play", *font, 32 ) );
  b_play->setTextToCenter();
  b_play->setAction( [ this]() -> void{
      Game::getInstance()->getStateHandler()->change( new ProfileState() ) ;
    } );
  Button * b_net = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 300), c );
  b_net->setBorderThickness(1);
  b_net->setText(sf::Text("Net", *font, 32 ) );
  b_net->setTextToCenter();
  b_net->setAction( [&b_net, this]() ->void{
      //
    } );
  Button * b_options = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 400), c );
  b_options->setBorderThickness(1);
  b_options->setText(sf::Text("Options", *font, 32 ) );
  b_options->setTextToCenter();
  b_options->setAction( [this]()->void{
      //Game::getInstance()->getStateHandler()->change(new OptionMenu() );
    } );
  Button * b_quit = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 500), c );
  b_quit->setBorderThickness(1);
  b_quit->setText(sf::Text("Quit", *font, 32 ) );
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
