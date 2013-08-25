/**
   Here we define a spritesheet (extracted from a file) as :
   -image
   -list of sprites (posX, posY, width, height, hotpointX hotpointY)
   -list of animations (indexes refering to sprites)
 */

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "../headers/Action.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>
#include <string>
#include <vector>

class Sprite{
private:
  sf::Vector2u m_position;
  sf::Vector2u m_dimensions;
  sf::Vector2u m_hotpoint;

public:
  Sprite(){ };
  Sprite(const unsigned short&, const unsigned short&, 
	 const unsigned short&, const unsigned short&, 
	 const unsigned short& = 0, const unsigned short& = 0);
  sf::Vector2u getPosition(){
    return m_position;
  };
  unsigned short getPositionX(){
    return m_position.x;
  };
  unsigned short getPositionY(){
    return m_position.y;
  };
  sf::Vector2u getDimension(){
    return m_dimensions;
  };
  unsigned short getWidth(){
    return m_dimensions.x;
  };
  unsigned short getHeight(){
    return m_dimensions.y;
  };  
  sf::Vector2u getHotpoint(){
    return m_hotpoint;
  };
  unsigned short getHotpointX(){
    return m_hotpoint.x;
  };
  unsigned short getHotpointY(){
    return m_hotpoint.y;
  };
};

class Animation{
private:
  std::vector<unsigned short> m_indexes;

public:
  Animation(){};
  std::vector<unsigned short> getIndexes() const{
    return m_indexes;
  };
  unsigned short get(const unsigned int& i) const{
    return m_indexes[i];
  };
  void add(const unsigned short& v){
    m_indexes.push_back(v);
  };

};

#define SPRITESHEET_DIR "../../resources/spritesheets/"

class Spritesheet{
private:
  std::vector<Sprite> m_sprites;
  std::map<Action::Type, Animation> m_animations;

public:
  Spritesheet(){ };
  Spritesheet(const std::string& n){
    loadFromFile(n);
  };
  bool loadFromFile(const std::string& n);
  std::vector<Sprite> getSprites(){
    return m_sprites;
  };
  Sprite * getSprite(const unsigned int& i){
    if(i < m_sprites.size() )
      return &m_sprites[i];
    else
      return NULL;
  };
  std::map<Action::Type, Animation> getAnimations(){
    return m_animations;
  };
  Animation getAnimation(const Action::Type& i){
    return m_animations[i];
  };

};

#endif