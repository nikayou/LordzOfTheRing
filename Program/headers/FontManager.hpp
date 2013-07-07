#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>

#include "ResourceManager.hpp"

#define DEFAULT_FONT "ArialPixel.TTF"


class FontManager: public ResourceManager<sf::Font>{
private:
  bool loadFromFile(const std::string& path){
    sf::Font t;
    if(!t.loadFromFile(path) ){
      return false;
    }
    add(path, t);
    return true;
  }

};

#endif
