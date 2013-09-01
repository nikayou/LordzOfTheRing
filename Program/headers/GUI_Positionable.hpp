#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include <SFML/System/Vector2.hpp>

////////////////////
/// Positionnable interface
////////////////////
/// Useful for objects possessing a position
///////////////////
class Positionable{
protected:
  sf::Vector2f mPosition; //position (IN PIXELS)
 
public:
  // getters
  inline sf::Vector2f getPosition() const { return mPosition; } ;
  inline float getX() const { return mPosition.x; } ;
  inline float getY() const { return mPosition.y; } ;
  // setters
  void setPosition(const sf::Vector2f& v){ 
    mPosition.x = v.x; 
    mPosition.y = v.y;
  };
  void setPosition(const float& x, const float& y){ 
    setPosition(sf::Vector2f(x,y) );
  };
   
};

#endif
