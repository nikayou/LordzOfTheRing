#ifndef BORDERED_HPP
#define BORDERED_HPP

#include <SFML/Graphics/Color.hpp>

////////////////////
/// Border interface
////////////////////
/// Useful for objects which can have a border
///////////////////
class Bordered{
protected:
  sf::Color mBorder;
  unsigned short mBorderThickness;

public:
  // getters
  void setBorder(const sf::Color&);
  virtual void setBorderThickness(const unsigned short&);  
  // setters
  sf::Color getBorder() const;
  unsigned short getBorderThickness() const;
};

#endif
