#include "../headers/CharacterManager.hpp"
#include "../headers/Character.hpp"
#include "../headers/Misc.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>



bool CharacterManager::loadFromFile(const std::string& path){
  std::ifstream ifs;
  ifs.open(path.c_str() );
  if( !ifs.good() ){
    return false;
  }
  Character c;
  bool defn = false, defh = false, defr = false, defa = false, defs = false;
  std::string line = "";
  while( !ifs.eof() ){
    getline(ifs, line);
    if(line[0] == '#' )
      continue;
    if(!defn && contains(line, "name=") ){
      c.setName( cutFrom(line, '=') );
      defn = true;
      continue;
    }
    if(!defh && contains(line, "health=") ){
      c.setHealth( extractInt(line)  );
      defh = true;
      continue;
    }
    if(!defr && contains(line, "resistance=") ){
      c.setResistance( Stats::fromString( cutFrom(line, '=') )  );
      defr = true;
      continue;
    }
    if(!defa && contains(line, "attack=") ){
      c.setAttack( Stats::fromString( cutFrom(line, '=') )  );
      defa = true;
      continue;
    }
    if(!defs && contains(line, "stamina=") ){
      c.setStamina( Stats::fromString( cutFrom(line, '=') )  );
      defs = true;
      continue;
    }

  }
  if(defn && defh && defr && defa && defs){
    add(path, c);
    return true;
  } else{
    std::cout <<"Error : incomplete character file \""<< path<<"\""<< std::endl;
    return false;
  }
}
