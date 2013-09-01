#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Component.hpp"


Component::Component(){

}


/* tells if the given point is inside the component */
bool Component::contains(const sf::Vector2i& v){
  return ( getPosition().x <= v.x
	   && getPosition().y <= v.y
	   && getPosition().x+getWidth() > v.x
	   && getPosition().y+getHeight() > v.y );
}
