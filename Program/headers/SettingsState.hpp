#ifndef SETTINGSTATE_HPP
#define SETTINGSTATE_HPP

#include "../headers/GameState.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Checkbox.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/OptionState.hpp"

#include <string>
#include <vector>

class SettingsState: public OptionState{
public :
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual std::string getID() const{ return m_settingsID; };
  virtual void deleteAll();

private:
  static const std::string m_settingsID;
  sf::RenderTexture * m_render;
  Container * m_container;
  GUIWindow * m_window;
  std::vector<Button *> m_buttons;
  Checkbox * m_fullscreen;
  std::vector<sf::Text *> m_texts;

};

#endif
