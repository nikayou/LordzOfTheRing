#ifndef OPTIONSTATE_HPP
#define OPTIONSTATE_HPP

#include "../headers/GameState.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Checkbox.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/Match.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

class OptionState: public GameState{
public :
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual StateID::ID  getID() const{ return m_optionID; };
  virtual void deleteAll();

private:
  static const StateID::ID m_optionID = StateID::OPTIONS_MENU;
  sf::RenderTexture * m_render;
  Container * m_container;
  GUIWindow * m_window;
  std::vector<Button *> m_buttons;
  Checkbox * m_tko;
  std::vector<sf::Text *> m_texts;
  std::string typeToString(const MatchType&);

};

#endif
