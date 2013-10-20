#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <string>


#include "../headers/ResourcesDirectories.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"
#include "../headers/Font.hpp"


const std::string DEFAULT_FONT = "chubby_cheeks.ttf";

class FontManager: public ResourceManager<Font>, public Singleton<FontManager>{

private:
std::string m_defaultFont;


public :
FontManager(){ m_defaultFont = DEFAULT_FONT;
};

std::string getClass(){ 
return "FontManager";
}
std::string getDefaultFont() const{
return m_defaultFont;
}

};

#endif
