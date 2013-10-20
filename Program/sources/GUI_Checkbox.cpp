#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_Checkbox.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Misc.hpp"

////////////////////
/// Checkboxes
////////////////////
/// Can have an associated text, and a border
////////////////////


Checkbox::Checkbox(){
  setChecked(false);
  setBorder( sf::Color::Black );
  setBorderThickness(0);
  setBackground(sf::Color(240, 240, 240) );
  setFocus( sf::Color(180, 180, 180) );
  resize( sf::Vector2u( CHECKBOX_WIDTH+(MARGIN_BOX*2), (CHECKBOX_WIDTH+(MARGIN_BOX*2) ) )   );
  //setPosition(0, 0);
}

Checkbox::Checkbox(const sf::Text& t){
  setChecked(false);
  setText(t);
  unsigned int w, h;
  if(!t.getString().toAnsiString().compare("") ){
    w = CHECKBOX_WIDTH;
    h = CHECKBOX_WIDTH;
  }else{
    w = MAX(CHECKBOX_WIDTH, CHECKBOX_WIDTH + (t.getGlobalBounds().width) + 2*MARGIN_BOX + PADDING_BOX);
    h = MAX(CHECKBOX_WIDTH, t.getGlobalBounds().height);
  }
  resize( sf::Vector2u(w+PADDING_BOX+MARGIN_BOX, h+(PADDING_BOX*2) ) );
  setBorder( sf::Color::Black );
  setTextToCenter();
  setBorderThickness(0);
  setBackground(sf::Color(240, 240, 240) );
  setFocus( sf::Color(180, 180, 180) );
}

Checkbox::Checkbox(const std::string& s){
  setChecked(false);
  sf::Text t(s, *(FontManager::getInstance()->get(FontManager::getInstance()->getDefaultFont() ) ) );
  setText( t );
  unsigned int w, h;  
  if(!s.compare("") ){
    w = CHECKBOX_WIDTH;
    h = CHECKBOX_WIDTH;
  }else{
    w = MAX(CHECKBOX_WIDTH, CHECKBOX_WIDTH + (t.getGlobalBounds().width) + 2*MARGIN_BOX + PADDING_BOX);
    h = MAX(CHECKBOX_WIDTH, t.getGlobalBounds().height);
  }
  resize( sf::Vector2u(w+PADDING_BOX+MARGIN_BOX, h+(PADDING_BOX*2) ) );
  setTextToCenter();
  setBorder( sf::Color::Black );
  setBorderThickness(0);
  setBackground(sf::Color(240, 240, 240) );
  setFocus( Color::darker(getBackground() ) );
}

void Checkbox::setPosition(const sf::Vector2f& v){
  mPosition.x = v.x; 
  mPosition.y = v.y;
  setTextToCenter();
}

/* Sets the text in the center of the component */
void Checkbox::setTextToCenter(){
  sf::Text t = getText();
  unsigned int w, h;
  sf::FloatRect fr = t.getLocalBounds();
  w = CHECKBOX_WIDTH + (fr.left+fr.width/2);
  h = fr.height/2-fr.top;
  mText.setOrigin( (w-CHECKBOX_WIDTH) /2, h);
  mText.setPosition( getX()+w, getY()+h);
}

/* checks if the point is in the checkbox */
bool Checkbox::contains(const sf::Vector2i& v){
  int t = getBorderThickness();
  int h = getHeight();
  int x = getX()+t+MARGIN_BOX;
  int y = getY()+t+ h/2 - CHECKBOX_WIDTH/2;
  return ( x <= v.x
	   && y <= v.y
	   && x + CHECKBOX_WIDTH > v.x
	   && y + CHECKBOX_WIDTH > v.y );
}

/* Sets all the vertices in position/color and return them.
   The drawing follows the following order :
   0-15 : border (north, south, west, east)
   16-19 : checkbox
   20-27 : check mark
   28-35 : box border (4 lines)
*/ 
sf::VertexArray Checkbox::draw(){
  sf::VertexArray checkbox;
  checkbox.resize( 36 );
  unsigned int w = getWidth();
  unsigned int h = getHeight();
  unsigned int t = getBorderThickness();
  //box coordinates
  float x = getX()+MARGIN_BOX+1;
  float y = MAX( getY()+(h/2)-CHECKBOX_WIDTH/2, getY()+MARGIN_BOX) ;
  //BORDER
  sf::Vertex * border = &(checkbox[0]);
  for(unsigned int i = 0; i < 16; i++){
    border[i].color = getBorder();
  }
  if(t > 0 ){
    //north border
    border[0].position = sf::Vector2f( getX(), getY() );
    border[1].position = sf::Vector2f( getX()+w, getY() );
    border[2].position = sf::Vector2f( getX()+w, getY()+t );
    border[3].position = sf::Vector2f( getX(), getY()+t );
    //south border
    border[4].position = sf::Vector2f( getX(), getY()+h );
    border[5].position = sf::Vector2f( getX()+w, getY()+h );
    border[6].position = sf::Vector2f( getX()+w, getY()+h-t );
    border[7].position = sf::Vector2f( getX(), getY()+h-t );
    //west border
    border[8].position = sf::Vector2f( getX(), getY()+t );
    border[9].position = sf::Vector2f( getX()+t, getY()+t );
    border[10].position = sf::Vector2f( getX()+t, getY()+h-t );
    border[11].position = sf::Vector2f( getX(), getY()+h-t );
    //east border
    border[12].position = sf::Vector2f( getX()+w-t, getY()+t );
    border[13].position = sf::Vector2f( getX()+w, getY()+t );
    border[14].position = sf::Vector2f( getX()+w, getY()+h-t );
    border[15].position = sf::Vector2f( getX()+w-t, getY()+h-t );
  }else{
    for(unsigned int i = 0; i < 16; i++)
      border[i].position = sf::Vector2f(-1, -1);
  }
  //BOX
  sf::Vertex * box = &(checkbox[16]);
  for(unsigned int i = 0; i < 4; i++)
    box[i].color = getBackground();
  box[0].position = sf::Vector2f(x, y+1);
  box[1].position = sf::Vector2f(x+CHECKBOX_WIDTH-2, y+1 );
  box[2].position = sf::Vector2f(x+CHECKBOX_WIDTH-2, y+CHECKBOX_WIDTH-1 );
  box[3].position = sf::Vector2f(x, y+CHECKBOX_WIDTH-1 );
  //CHECK
  sf::Vertex * check = &(checkbox[20] );
  for(unsigned int i = 0; i < 8; i++){
    check[i].color = sf::Color::Black;
  }
  if(!isChecked() ){
    for(unsigned int i = 0; i < 8; i++){
      check[i].position = sf::Vector2f(-1, -1);
    }
  }else{
    unsigned int lheight = 4;
    check[0].position = sf::Vector2f( x+2, y+5);
    check[1].position = sf::Vector2f( x+2, y+5+lheight);
    check[2].position = sf::Vector2f( x+6, y+8+lheight);
    check[3].position = sf::Vector2f( x+6, y+8);
    check[4].position = sf::Vector2f( x+6, y+8+lheight);
    check[5].position = sf::Vector2f( x+6, y+8);
    check[6].position = sf::Vector2f( x+12, y+2);
    check[7].position = sf::Vector2f( x+12, y+2+lheight);
  }
  //BOX BORDER
  sf::Vertex * square = &(checkbox[28]);
  for(unsigned int i = 0; i < 8; i++)
    square[i].color = sf::Color::Black;
  square[0].position = sf::Vector2f( x-1, y );
  square[1].position = sf::Vector2f( x+CHECKBOX_WIDTH-2, y );
  square[2].position = sf::Vector2f( x+CHECKBOX_WIDTH-1, y );
  square[3].position = sf::Vector2f( x+CHECKBOX_WIDTH-1, y+CHECKBOX_WIDTH-1 );
  square[4].position = sf::Vector2f( x+CHECKBOX_WIDTH-1, y+CHECKBOX_WIDTH-1 );
  square[5].position = sf::Vector2f( x, y+CHECKBOX_WIDTH-1);
  square[6].position = sf::Vector2f( x, y+CHECKBOX_WIDTH);
  square[7].position = sf::Vector2f( x, y+1 );
  return checkbox;
}
