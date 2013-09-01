#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../headers/FontManager.hpp"
#include "../headers/GUI_Textual.hpp"

void Textual::setText(const sf::Text& t){ 
  mText = t; 
  setForeground(sf::Color::Black);
  //setTextToCenter(); 
}

void Textual::setFont(const std::string& s){ 
  mText.setFont(*FontManager::getInstance()->get(s) ); 
  //setTextToCenter();
}
