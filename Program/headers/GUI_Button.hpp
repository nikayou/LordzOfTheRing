#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Actionnable.hpp"
#include "../headers/GUI_TextComponent.hpp"

////////////////////
/// Button class
////////////////////
/// Can have a text, a border, colors, and an action
///////////////////

class Button : public Actionnable, public TextComponent{

public:
  Button(const sf::Vector2u&, const sf::Vector2f&);
  Button(const sf::Vector2u&, const sf::Vector2f&, const sf::Color&);
  Button(const sf::Vector2u&, const sf::Vector2f&, const sf::Text&); 
  Button(const sf::Vector2u&, const sf::Vector2f&, const sf::Text&, const sf::Color&);    
  /* sets vertices in position for displaying and returns them */
  sf::VertexArray draw();
  inline std::string getClass(){ return "Button"; };
};

#endif
