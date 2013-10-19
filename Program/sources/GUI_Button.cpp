#include <string>
#include <functional>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Button.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Misc.hpp"

////////////////////
/// Button class
////////////////////
/// Can have a text, a border, colors, and an action
///////////////////


Button::Button(const sf::Vector2u& d, const sf::Vector2f& p){
  resize(d);
  setPosition(p);
  setFont( *FontManager::getInstance()->get(DEFAULT_FONT) );
  setBackground(sf::Color(185, 185, 185) );
  setFocus( Color::brighter(getBackground() ) );
  setBorder(sf::Color(0,0,0,255) );
  setForeground(sf::Color::Black);
  setBorderThickness(1);
  setAction( [this]()->void{} );
  m_closing = false;
}

Button::Button(const sf::Vector2u& d, const sf::Vector2f& p, const sf::Color& c){
  resize(d);
  setPosition(p);
  setFont( *FontManager::getInstance()->get(DEFAULT_FONT) );
  setBackground(c);
  if( (c.r + c.g + c.b) < LUMINESCENCE )
    setFocus( Color::brighter(getBackground() ) );
  else
    setFocus( Color::darker(getBackground() ) );
  setBorder(sf::Color(0,0,0,255) );
  setForeground(sf::Color::Black);
  setBorderThickness(1);
  setAction( [this]()->void{} );
  m_closing = false;
}

Button::Button(const sf::Vector2u& d, const sf::Vector2f& p, const sf::Text& t){
  resize(d);
  setPosition(p);
  setText(t);
  setFont( *FontManager::getInstance()->get(DEFAULT_FONT) );
  setBackground(sf::Color(185, 185, 185) );
  setFocus( Color::brighter(getBackground() ) );
  setBorder(sf::Color(0,0,0,255) );
  setForeground(sf::Color::Black);
  setBorderThickness(1);
  setAction( [this]()->void{} );
  m_closing = false;
}

Button::Button(const sf::Vector2u& d, const sf::Vector2f& p, const sf::Text& t, const sf::Color& c){
  resize(d);
  setPosition(p);
  setText(t);
  setFont( *FontManager::getInstance()->get(DEFAULT_FONT) );
  setBackground(c);
  if( (c.r + c.g + c.b) < LUMINESCENCE )
    setFocus( Color::brighter(getBackground() ) );
  else
    setFocus( Color::darker(getBackground() ) );
  setBorder(sf::Color(0,0,0,255) );
  setForeground(sf::Color::Black);
  setBorderThickness(1);
  setAction( [this]()->void{} );
  m_closing = false;
}


/* sets vertices in position for displaying and returns them. 
   The drawing gollows this order : 
   0-15 : borders (north, south, west, east)
   16-19 : background quad
*/
sf::VertexArray Button::draw(){
  sf::VertexArray va;
  va.resize( 20 );
  sf::Vertex * border = &(va[0]);
  for(unsigned int i = 0; i < 16; i++){
    border[i].color = getBorder();
  }
  if(getBorderThickness() > 0 ){
    //north border
    border[0].position = sf::Vector2f( getX(), getY() );
    border[1].position = sf::Vector2f( getX()+getWidth(), getY() );
    border[2].position = sf::Vector2f( getX()+getWidth(), getY()+getBorderThickness() );
    border[3].position = sf::Vector2f( getX(), getY()+getBorderThickness() );
    //south border
    border[4].position = sf::Vector2f( getX(), getY()+getHeight() );
    border[5].position = sf::Vector2f( getX()+getWidth(), getY()+getHeight() );
    border[6].position = sf::Vector2f( getX()+getWidth(), getY()+getHeight()-getBorderThickness() );
    border[7].position = sf::Vector2f( getX(), getY()+getHeight()-getBorderThickness() );
    //west border
    border[8].position = sf::Vector2f( getX(), getY()+getBorderThickness() );
    border[9].position = sf::Vector2f( getX()+getBorderThickness(), getY()+getBorderThickness() );
    border[10].position = sf::Vector2f( getX()+getBorderThickness(), getY()+getHeight()-getBorderThickness() );
    border[11].position = sf::Vector2f( getX(), getY()+getHeight()-getBorderThickness() );
    //east border
    border[12].position = sf::Vector2f( getX()+getWidth()-getBorderThickness(), getY()+getBorderThickness() );
    border[13].position = sf::Vector2f( getX()+getWidth(), getY()+getBorderThickness() );
    border[14].position = sf::Vector2f( getX()+getWidth(), getY()+getHeight()-getBorderThickness() );
    border[15].position = sf::Vector2f( getX()+getWidth()-getBorderThickness(), getY()+getHeight()-getBorderThickness() );
  }else{
  for(unsigned int i = 0; i < 16; i++)
    border[i].position = sf::Vector2f(-1, -1);
  }
  sf::Vertex * inside = &(va[16]);
  sf::Color c = getBackground();
  /*if(contains(this, sf::Mouse::getPosition() ) ){
    printf("Button focused\n");
    c = getFocus();
    }*/
  for(unsigned int i = 0; i < 4; i++)
    inside[i].color = c;
  unsigned int t = getBorderThickness();
  inside[0].position = sf::Vector2f( getX()+t, getY()+t );
  inside[1].position = sf::Vector2f( getX()+getWidth()-t, getY()+t );
  inside[2].position = sf::Vector2f( getX()+getWidth()-t, getY()+getHeight()-t );
  inside[3].position = sf::Vector2f( getX()+t, getY()+getHeight()-t );
  return va;
}
