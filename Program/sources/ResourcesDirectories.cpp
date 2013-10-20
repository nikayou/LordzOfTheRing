
#include "../headers/ResourcesDirectories.hpp"
#include "../headers/FontManager.hpp"


#include <string>

void ResDir::recompute_resdir(const std::string& n){
  m_resDir = n;
  m_imgDir = m_resDir+"images/";
  m_charDir = m_resDir+"characters/";
  m_spritesheetDir = m_resDir+"spritesheets/";
  m_fontDir = m_resDir+"fonts/";
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
