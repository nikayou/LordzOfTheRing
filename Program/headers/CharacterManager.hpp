#ifndef CHARACTERMANAGER_HPP
#define CHARACTERMANAGER_HPP

#include <iostream> //delete
#include <string>
#include "../headers/CharacterManager.hpp"
#include "../headers/Character.hpp"
#include "../headers/Misc.hpp"
#include "../headers/ResourceManager.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "../headers/ResourceManager.hpp"
#include "../headers/Character.hpp"


class CharacterManager: public ResourceManager<Character>, public Singleton<CharacterManager>{

  //friend class ResourceManager<Character>;

public:
  CharacterManager(){ std::cout<<"Character manager" <<std::endl; };
  

public:
  std::string getClass(){ return "CharacterManager"; };
};



#endif
