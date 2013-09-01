#ifndef RESIZABLE_HPP
#define RESIZABLE_HPP

#include <SFML/System/Vector2.hpp>

#include "../headers/Misc.hpp"

////////////////////
/// Resizable interface
////////////////////
/// Useful for objects which can be resized (or set-sized)
///////////////////
class Resizable{
protected:
  sf::Vector2u mDimensions; //dimensions (IN PIXELS)

public:   
  // getters
  inline sf::Vector2u getDimension() const { return mDimensions; };
  inline unsigned int getWidth() const { return mDimensions.x; };
  inline unsigned int getHeight() const { return mDimensions.y; };
  // setters
  virtual void resize(const sf::Vector2u& v){ 
    mDimensions.x = MAX(1, v.x); 
    mDimensions.y = MAX(1, v.y);
    //setTextToCenter();
  };
  
};

#endif
