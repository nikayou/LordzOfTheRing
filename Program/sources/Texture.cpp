#include "../headers/Texture.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <iostream> //delete
#include <string>

Texture::Texture(const std::string& f){
  loadFromFile(f);
}

bool Texture::loadFromFile(const std::string& f){
  std::string file = IMG_DIR+f;
  std::cout<<"loading image "<<file<<" in "<<&m_texture<<std::endl;
  if(!m_texture.loadFromFile(file))
    return false;
  return true;
}
