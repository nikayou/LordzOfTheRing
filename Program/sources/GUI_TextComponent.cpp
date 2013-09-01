#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Positionable.hpp"
#include "../headers/GUI_Resizable.hpp"
#include "../headers/GUI_TextComponent.hpp"

/* Sets the text in the center of the component */
void TextComponent::setTextToCenter(){
  if(mText.getOrigin().x == 0 && mText.getOrigin().y == 0){
    sf::FloatRect fr = mText.getLocalBounds();
    float x = mText.getOrigin().x + fr.width/2;
    float y = mText.getOrigin().y + fr.height/2;
    mText.setOrigin(x, y);
    x = getX()+(getWidth()/2);
    y = getY()+(getHeight()/2);
    mText.setPosition(x, y);
  }
}

void TextComponent::setPosition(const sf::Vector2f& v){
  mPosition.x = v.x; 
  mPosition.y = v.y;
  float x = getX()+(getWidth()/2);
  float y = getY()+(getHeight()/2);
  mText.setPosition(x, y);
  setTextToCenter();
}
