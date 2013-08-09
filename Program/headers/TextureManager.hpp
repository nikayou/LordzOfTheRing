#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "../headers/ResourceManager.hpp"

class TextureManager: public ResourceManager<sf::Texture>, public Singleton<TextureManager>{

public:
  TextureManager(){};
  std::string getClass(){
    return "TextureManager";
  };

};


#endif
