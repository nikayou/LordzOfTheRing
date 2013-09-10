#ifndef ROUNDENDSTATE_HPP
#define ROUNDENDSTATE_HPP

#include "../headers/GameState.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <string>

class RoundEndState : public GameState{

public :
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual void deleteAll();
  virtual std::string getID() const{ return m_roundID; };

private:
  static const std::string m_roundID;
  sf::RenderTexture * m_render;
  GUIWindow * m_window;
  Container * m_container;
  float m_scale;
};

#endif
