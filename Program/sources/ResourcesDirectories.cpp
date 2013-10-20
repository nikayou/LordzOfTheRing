#include "../headers/ResourcesDirectories.hpp"

std::string ResDir::m_resDir = "";
std::string ResDir::m_imgDir = "";
std::string ResDir::m_charDir = "";
std::string ResDir::m_spritesheetDir = "";
std::string ResDir::m_fontDir = "";  

ResDir::~ResDir(){
  ResDir::m_resDir.clear();
  ResDir::m_imgDir.clear();
  ResDir::m_charDir.clear();
  ResDir::m_fontDir.clear();
  ResDir::m_spritesheetDir.clear();
}

