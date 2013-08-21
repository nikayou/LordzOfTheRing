#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "../headers/ResourceManager.hpp"
#include "../headers/Singleton.hpp"
#include "../headers/Texture.hpp"

class TextureManager: public ResourceManager<Texture>, public Singleton<TextureManager>{

public:
  TextureManager(){};
  std::string getClass(){
    return "TextureManager";
  };

};


#endif
