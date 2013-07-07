#ifndef CHARACTERMANAGER_HPP
#define CHARACTERMANAGER_HPP

#include <string>


#include "../headers/ResourceManager.hpp"
#include "../headers/Character.hpp"

class CharacterManager: public ResourceManager<Character>{
private:
  bool loadFromFile(const std::string&);

};

#endif
