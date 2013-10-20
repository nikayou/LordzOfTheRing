#ifndef RESDIR_HPP
#define RESDIR_HPP

#include <string>

#include "../headers/Singleton.hpp"

/* repertories all the resources directories */

class ResDir: public Singleton<ResDir>{

private:
  std::string m_resDir;
  std::string m_imgDir;
  std::string m_charDir;
  std::string m_spritesheetDir;
  std::string m_fontDir;

public:
  ~ResDir();
  void recompute_resdir(const std::string);
  std::string getResDir() const;
  std::string getImgDir() const;
  std::string getCharDir() const;
  std::string getSpritesheetDir() const;
  std::string getFontDir() const;
  
};

#endif
