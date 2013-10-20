#ifndef FONT_HPP
#define FONT_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>

class Font{

private:
  sf::Font m_font;

public:
  Font(){};
  ~Font(){};
  Font(const std::string&);
  bool loadFromFile(const std::string& n);
  sf::Font * getFont();
  static std::string getClass(){
    return "Font";
  };
};


#endif
