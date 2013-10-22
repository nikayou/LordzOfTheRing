#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "../headers/GameState.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <string>
#include <vector>

class MainMenuState : public GameState{
public:
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual void deleteAll();
  virtual StateID::ID getID() const { return m_mainMenuID; }

private:
  sf::RenderTexture * m_render;
  static const StateID::ID m_mainMenuID = StateID::MAIN_MENU;
  std::vector<Button *> m_buttons;
  Container * m_container;
  GUIWindow * m_window;
};

#endif
