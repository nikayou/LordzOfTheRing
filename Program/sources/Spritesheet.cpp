/**
   Here we define a spritesheet (extracted from a file) as :
   -image
   -list of sprites (posX, posY, width, height, hotpointX hotpointY)
   -list of animations (indexes refering to sprites)
*/

#include "../headers/Spritesheet.hpp"
#include "../headers/Misc.hpp"

#include <iostream> //delete ?
#include <fstream>
#include <string>
#include <vector>

Sprite::Sprite(const unsigned short& x,
	       const unsigned short& y,
	       const unsigned short& w,
	       const unsigned short& h,
	       const unsigned short& hx,
	       const unsigned short& hy){
  m_position.x = x;
  m_position.y = y;
  m_dimensions.x = w;
  m_dimensions.y = h;
  m_hotpoint.x = hx;
  m_hotpoint.y = hy;
}

bool Spritesheet::loadFromFile(const std::string& f){
  std::ifstream ifs;
  std::string file = SPRITESHEET_DIR + f;
  ifs.open(file.c_str() );
  if( !ifs.good() ){
    return false;
  }
  std::string line = "";
  bool maxsprt = false, nbanim = false;
  while( !ifs.eof() ){
    getline(ifs, line);
    if( line[0] == '#' )
      continue;
    if(!maxsprt && contains(line, "maxsprt=") ){
      m_sprites.resize(extractInt(line)+1 ); //+1 beacause the max indice has to be accessed
      maxsprt = true;
      continue;
    }
    if(!nbanim && contains(line, "nbanim=") ){
      m_animations.resize(extractInt(line) );
      nbanim = true;
      continue;
    }
    if(contains(line, "s:") ){
      unsigned int id = extractInt(line, ':');
      getline(ifs, line);
      unsigned short px = 0, py = 0, w = 0, h = 0, hx = 0, hy = 0;
      size_t separator = 0;
      px = std::stoi(line, &separator);
      py = std::stoi(line.substr(separator+1) );
      getline(ifs, line); 
     
      w = std::stoi(line, &separator);
      h = std::stoi(line.substr(separator+1) );
      getline(ifs, line);
      hx = std::stoi(line, &separator);
      hy = std::stoi(line.substr(separator+1) );

      m_sprites[id] = Sprite(px, py, w, h, hx, hy);
      continue;
    }
  }
  return true;
}
