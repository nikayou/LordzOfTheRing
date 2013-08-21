#ifndef SPRITESHEETMANAGER_HPP
#define SPRITESHEETMANAGER_HPP

#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"
#include "../headers/Spritesheet.hpp"

#include <string>

class SpritesheetManager : public ResourceManager<Spritesheet>, public Singleton<SpritesheetManager>{

public:
  SpritesheetManager(){ };

public:
  std::string getClass(){
    return "SpritesheetManager";
  };
};

#endif
