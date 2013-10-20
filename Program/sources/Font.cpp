#include "../headers/Font.hpp"
#include "../headers/ResourcesDirectories.hpp"

#include <SFML/Graphics/Font.hpp>

#include <string>

sf::Font * Font::getFont(){
  return &(m_font);
}


bool Font::loadFromFile(const std::string& n){
    return m_font.loadFromFile(ResDir::getInstance()->getFontDir()+n );
}
