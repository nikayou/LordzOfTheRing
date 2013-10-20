#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>

#include "../headers/ResourcesDirectories.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"


const std::string DEF_FONT = "chubby_cheeks.ttf";

class FontManager: public ResourceManager<sf::Font>, public Singleton<FontManager>{

private:
std::string m_defaultFont;


public :
FontManager(){ m_defaultFont = ResDir::getInstance()->getFontDir()+DEF_FONT;
};
std::string getClass(){ 
return "FontManager";
}
std::string getDefaultFont() const{
return m_defaultFont;
}
void refreshDefaultFont(const std::string& n){
m_defaultFont = n+DEF_FONT;
}

};

#endif
