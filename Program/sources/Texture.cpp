#include "../headers/Texture.hpp"
#include "../headers/ResourcesDirectories.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <string>


Texture::Texture(const std::string& f){
  loadFromFile(f);
}

bool Texture::loadFromFile(const std::string& f){
  std::string file = ResDir::getImgDir()+f;
  if(!m_texture.loadFromFile(file))
    return false;
  m_texture.setSmooth(false);
  return true;
}
