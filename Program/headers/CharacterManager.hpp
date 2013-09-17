#ifndef CHARACTERMANAGER_HPP
#define CHARACTERMANAGER_HPP

#include "../headers/CharacterManager.hpp"
#include "../headers/Character.hpp"
#include "../headers/Misc.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"

#include <string>
#include <vector>

class CharacterManager: public ResourceManager<Character>, public Singleton<CharacterManager>{

  //friend class ResourceManager<Character>;
private:
  std::vector<Character *> m_array;

public:
  CharacterManager(){ 
  };
  

public:
  std::string getClass(){ 
    return "CharacterManager"; 
  };

  std::map<std::string, Character > getData(){
    return mData;
  };
  void computeArray(){
    m_array.clear();
    for(std::map<std::string, Character >::iterator it = mData.begin() ; it != mData.end() ; ++it)
      {
	m_array.push_back(&(it->second) );
      }
  };

  std::vector<Character *> getArray(){
    return m_array;
  };
  
};



#endif
