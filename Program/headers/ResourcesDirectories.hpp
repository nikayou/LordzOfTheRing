#ifndef RESDIR_HPP
#define RESDIR_HPP

#include <string>

/* repertories all the resources directories */

class ResDir{

private:
  ResDir();
  ~ResDir();

public:
  static std::string m_resDir;
  static std::string m_imgDir;
  static std::string m_charDir;
  static std::string m_spritesheetDir;
  static std::string m_fontDir;
  static void recompute_resdir(const std::string n){
    ResDir::m_resDir = n;
    ResDir::m_imgDir = n;
    ResDir::m_imgDir.append("images/");
    ResDir::m_charDir = n;
    ResDir::m_charDir.append("characters/");
    ResDir::m_spritesheetDir = n;
    ResDir::m_spritesheetDir.append("spritesheets/");
    ResDir::m_fontDir = n;
    ResDir::m_fontDir.append("fonts/");
  };
  static std::string getResDir(){
    return ResDir::m_resDir;
  };
  static std::string getImgDir(){
    return ResDir::m_imgDir;
  };
  static std::string getCharDir(){
    return ResDir::m_charDir;
  };
  static std::string getSpritesheetDir(){
    return ResDir::m_spritesheetDir;
  };
  static std::string getFontDir(){
    return ResDir::m_fontDir;
  };

};


#endif
