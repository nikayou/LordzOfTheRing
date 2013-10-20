#ifndef TEXTUAL_HPP
#define TEXTUAL_HPP

#include <string>

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../headers/Font.hpp"

////////////////////
/// Textual interface
////////////////////
/// Useful for objects whose a text is related
///////////////////
class Textual{
protected:
  sf::Text mText; //text displayed
  
public:  
  // getters
  inline sf::Text getText() const{ return mText; };
  inline std::string getString() const { return mText.getString().toAnsiString(); };
  inline sf::Color getForegroud() const{ return mText.getColor(); };
  // setters
  void setText(const sf::Text& t);
  void setText(const std::string& s){ setString(s); };
  void setForeground(const sf::Color& c){ mText.setColor(c); };
  void setFont(Font * f){ (mText.setFont(*f->getFont() ) ); //setTextToCenter(); 
  };
  void setFont(const std::string& s);
  void setString(const sf::String& s){ mText.setString(s); //setTextToCenter(); 
  };
  void setCharacterSize( const unsigned int& i){ mText.setCharacterSize(i); };
  void setStyle(const sf::Uint32& s){ mText.setStyle(s); //setTextToCenter(); 
  };
  
};

#endif
