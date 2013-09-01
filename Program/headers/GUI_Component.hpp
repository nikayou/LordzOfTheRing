#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Bordered.hpp"
#include "../headers/GUI_Colorful.hpp"
#include "../headers/GUI_Positionable.hpp"
#include "../headers/GUI_Resizable.hpp"

class Component: public Bordered, public Colorful, public Positionable, public Resizable{

public :
  Component();
  // getters
  virtual inline std::string getClass(){ return "Component"; };
  // setters

  // misc
  /* tells if the given point is inside the component */
  bool contains(const sf::Vector2i&);
  /* sets the vertices in position/color and returns them */
  virtual sf::VertexArray draw() = 0;
};


#endif
