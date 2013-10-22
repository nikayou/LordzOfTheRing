#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <string>


#include "../headers/ResourcesDirectories.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"
#include "../headers/Font.hpp"

class FontManager: public ResourceManager<Font>, public Singleton<FontManager>{

private:
  std::string m_defaultFont;


public :
  FontManager(){ m_defaultFont = "chubby_cheeks.ttf";
  };

  ~FontManager(){
    m_defaultFont.clear();
  };

  std::string getClass(){ 
    return "FontManager";
  }
  std::string getDefaultFont() const{
    return m_defaultFont;
  }
  /**
     Remove all elements and clears the default font
  */
  virtual void clear(){
    std::cout<<"clearing "<<getClass()<<" at "<<this<<std::endl;
    mData.clear();
    m_defaultFont.clear();
  }

};

#endif
