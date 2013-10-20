#include <SFML/Graphics/Color.hpp>

#include "../headers/GUI_Bordered.hpp"

////////////////////
/// Border interface
////////////////////
/// Useful for objects which can have a border
///////////////////


// getters
sf::Color Bordered::getBorder() const{ 
  return mBorder; 
}

unsigned short Bordered::getBorderThickness() const{ 
  return mBorderThickness; 
}

// setters

void Bordered::setBorder(const sf::Color& c){ 
  mBorder = c; 
}

void Bordered::setBorderThickness(const unsigned short& v){
  mBorderThickness = v; 
}

