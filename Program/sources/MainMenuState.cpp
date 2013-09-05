#include "../headers/MainMenuState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/MatchState.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

const std::string MainMenuState::m_mainMenuID = "MAIN_MENU";

void MainMenuState::update(){
std::cout<<"update menu state"<<std::endl;
}

void MainMenuState::render(){
  std::cout<<"rendering menu state"<<std::endl;
  m_window->draw();
  std::cout<<"rendered menu state"<<std::endl;
}

bool MainMenuState::enter(){
  sf::Font * font = FontManager::getInstance()->get("../../resources/ArialPixel.ttf");
  Button * b_play = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 200), sf::Color(60, 60, 60) );
  b_play->setBorderThickness(1);
  b_play->setText(sf::Text("Play", *font, 32 ) );
  b_play->setTextToCenter();
  b_play->setAction( [ this]() -> void{
      Game::getInstance()->getStateHandler()->change( new CharacterState() ) ;
      std::cout<<"menu char"<<std::endl;
    } );
  Button * b_net = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 300), sf::Color(60, 60, 60) );
  b_net->setBorderThickness(1);
  b_net->setText(sf::Text("Net", *font, 32 ) );
  b_net->setTextToCenter();
  b_net->setAction( [&b_net, this]() ->void{
      
    } );
  Button * b_options = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 400), sf::Color(60, 60, 60) );
  b_options->setBorderThickness(1);
  b_options->setText(sf::Text("Options", *font, 32 ) );
  b_options->setTextToCenter();
  b_options->setAction( [this]()->void{
      //Game::getInstance()->getStateHandler()->change(new OptionMenu() );
    } );
  Button * b_quit = new Button(sf::Vector2u(200, 70) , sf::Vector2f(300, 500), sf::Color(60, 60, 60) );
  b_quit->setBorderThickness(1);
  b_quit->setText(sf::Text("Quit", *font, 32 ) );
  b_quit->setTextToCenter();
  b_quit->setAction( [this]()->void{
      Game::getInstance()->close();
    }
    );
  m_render = new sf::RenderTexture();
  m_render->create(800, 600);
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
  std::cout << "entering MenuState\n";
  return true;
}

bool MainMenuState::exit(){
  std::cout << "exiting MenuState\n"<<std::endl;
  /*delete m_window;
  delete m_container;
  delete m_buttons[3];
  delete m_buttons[2];
  delete m_buttons[1];
  delete m_buttons[0];*/
  std::cout<< "exited menustate"<<std::endl;
  return true;
}