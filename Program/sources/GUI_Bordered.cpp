#include <SFML/Graphics/Color.hpp>

#include "../headers/GUI_Bordered.hpp"
#include "../headers/Misc.hpp"

////////////////////
/// Border interface
////////////////////
/// Useful for objects which can have a border
///////////////////


// getters
sf::Color Bordered::getBorder() const{ 
  return mBorder; 
};

unsigned short Bordered::getBorderThickness() const{ 
  return MAX(0, mBorderThickness); 
};

// setters

void Bordered::setBorder(const sf::Color& c){ 
  mBorder = c; 
};

void Bordered::setBorderThickness(const unsigned short& v){
  mBorderThickness = MAX(0, v); 
};  

