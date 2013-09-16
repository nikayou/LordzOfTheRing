#ifndef PROFILESTATE_HPP
#define PROFILESTATE_HPP

#include "../headers/GameState.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <string>
#include <vector>

class ProfileState : public GameState{

public:
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual std::string getID() const{ return m_profileID; };
  virtual void deleteAll();

private:
  static const std::string m_profileID;
  Container * m_container;
  GUIWindow * m_window;
  sf::RenderTexture * m_render;
  std::vector<Button * > m_buttons;

};

#endif
