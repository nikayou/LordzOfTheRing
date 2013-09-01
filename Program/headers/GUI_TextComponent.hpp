#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <string>

#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Component.hpp"
#include "../headers/GUI_Textual.hpp"

class TextComponent : public Component, public Textual{
public:
  inline std::string getClass(){ return "TextComponent"; };
  /* Sets the text in the center of the component */
  void setTextToCenter();
  void setPosition(const sf::Vector2f&);
};

#endif
