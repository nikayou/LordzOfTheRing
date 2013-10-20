
#include "../headers/ResourcesDirectories.hpp"
#include "../headers/FontManager.hpp"


#include <string>

ResDir::~ResDir(){
  m_resDir.clear();
  m_imgDir.clear();
  m_charDir.clear();
  m_spritesheetDir.clear();
}

void ResDir::recompute_resdir(const std::string n){
  m_resDir = n;
  m_imgDir = n;
  m_imgDir.append("images/");
  m_charDir = n;
  m_charDir.append("characters/");
  m_spritesheetDir = n;
  m_spritesheetDir.append("spritesheets/");
  m_fontDir = n;
  m_fontDir.append("fonts/");
}

std::string ResDir::getResDir() const{
  return m_resDir;
}

std::string ResDir::getImgDir() const{
  return m_imgDir;
}

std::string ResDir::getCharDir() const{
  return m_charDir;
}

std::string ResDir::getSpritesheetDir() const{
  return m_spritesheetDir;
}

std::string ResDir::getFontDir() const{
  return m_fontDir;
}
