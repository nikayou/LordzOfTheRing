#ifndef COLORFUL_HPP
#define COLORFUL_HPP

#include <SFML/Graphics/Color.hpp>

#include "../headers/Misc.hpp"

class Colorful{
private:
  sf::Color mBackground; //regular color
  sf::Color mFocus; //color when mouse is on

public:
  // getters
  inline sf::Color getBackground() const{ return mBackground; };
  inline sf::Color getFocus() const{ return mFocus; };
  // setters
  void setBackground(const sf::Color& c){ 
    mBackground = c; 
  mFocus = Color::brighter(c); };
  void setFocus(const sf::Color& c){ mFocus = c; };
};

#endif
