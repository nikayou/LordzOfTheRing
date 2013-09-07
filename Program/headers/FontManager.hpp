#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>

#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"

#define FONT_DIR "../../resources/"
#define DEFAULT_FONT "../../resources/ArialPixel.ttf"


class FontManager: public ResourceManager<sf::Font>, public Singleton<FontManager>{
public :
  FontManager(){ };
  std::string getClass(){ 
    return "FontManager";
  }

};

#endif
