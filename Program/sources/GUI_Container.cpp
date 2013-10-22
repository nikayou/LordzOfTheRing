#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Checkbox.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/Game.hpp"

Container::Container(){
  mContent->create(1, 1);
  //mContent->setFramerateLimit(35);
  mContainer = NULL;
  mFocused = 0;
}

Container::Container(sf::RenderTexture* rt){
  mContent = rt;
  mContainer = NULL;
  mFocused = 0;
}

Container::~Container(){

}

bool Container::add(Component * c){
  mComponents.push_back(c);
  return true;
}

void Container::updateFocus(){
  if(Game::getInstance()->updating() && mContainer == NULL)
    return;
  sf::Vector2i pos = getLocalMouse();
  unsigned int s = mComponents.size();
  for(unsigned int i = 0; i < s; i++){
    if(mComponents[i]->getClass().compare("Button") && mComponents[i]->contains(pos) ){
      mFocused = i+1;
      return;
    }
  }   
  mFocused = 0;
  
}

void Container::focusUp(){
  if(mFocused)
    mFocused = (mFocused == 1)?(unsigned int)mComponents.size()-1:mFocused-1;
}

void Container::focusDown(){
  mFocused = (mFocused == (unsigned int)mComponents.size() )?0:mFocused+1;
}

/** the return value indicate if we close the window(false) or not (true)*/
bool Container::click(const sf::Vector2i& pos){
  unsigned int nb = mComponents.size();
  for(unsigned int i = 0; i < nb; i++){
    if(i >= mComponents.size() || mComponents[i] == NULL)
      return true;
    if(mComponents[i]->getClass().compare("Button") == 0){
      Button * b = (Button *) mComponents[i];
      if( (mFocused != 0 && mComponents[mFocused-1] == b ) 
	  || b->contains(pos) )
	if(b == NULL)
	  return true;
	else
	  return( b->action() );
	
    }else if(mComponents[i]->getClass().compare("Checkbox") == 0){
      Checkbox * c = (Checkbox *) mComponents[i];
      if(c->contains(pos) )
	return(c->changeState() );
    }
  }
  return true;
}

bool Container::click(){
  return click(getLocalMouse() );
}

sf::Vector2i Container::getLocalMouse(){
  sf::Vector2i mouse;
  if(mContainer == NULL){
    mouse.x = -1;
    mouse.y = -1;
    return mouse;
  }
  mouse = mContainer->getMouse();
  mouse.x -= getX();
  mouse.y -= getY();
  return mouse;
}

void Container::drawTexts(){
  unsigned int csize = mComponents.size();
  for(unsigned int i = 0; i < csize; i ++){
    if(mComponents[i]->getClass().compare("TextComponent") == 0
       ||
       mComponents[i]->getClass().compare("Button") == 0
       ||
       mComponents[i]->getClass().compare("Checkbox") == 0
       ){
      TextComponent * t = (TextComponent *) mComponents[i];
      mContent->draw( t->getText()  );
    }
  }
}

sf::VertexArray Container::draw(){
  //mContent->clear( getBackground() );
  sf::VertexArray quads;
  quads.setPrimitiveType(sf::Quads);
  sf::VertexArray lines;
  lines.setPrimitiveType(sf::Lines);
  sf::VertexArray va;
  sf::Vector2i mouse = getLocalMouse();
  unsigned int csize = mComponents.size();
  for(unsigned int i = 0; i < csize; i++){
    if(mComponents[i]->getClass().compare("Container") == 0){
      Container * c = (Container *) mComponents[i];
      va = c->draw();
      
    }
    else if(mComponents[i]->getClass().compare("Button") == 0){
      Button * b = (Button *) mComponents[i];
      va = b->draw();
      for(unsigned int j = 0; j < 16; j++){
	quads.append( va[j] );
      }
      if( (mFocused && mComponents[mFocused-1] == b) || b->contains( mouse ) ){
	for(unsigned int j = 16; j < 20; j++){
	  va[j].color = b->getFocus();
	  quads.append( va[j] );
	}
      }else{
	for(unsigned int j = 16; j < 20; j++){
	  quads.append( va[j] );
	}
      }
    }else if(mComponents[i]->getClass().compare("Checkbox") == 0){
      Checkbox * c = (Checkbox *) mComponents[i];
      va = c->draw();
      //drawing border
      for(unsigned int j = 0; j < 16; j++){
	quads.append( va[j] );
      }
      //drawing box of checking
      if( c->contains( mouse )  ){
	for(unsigned int j = 16; j < 20; j++){
	  va[j].color = c->getFocus();
	  quads.append( va[j] );
	}
      }else{
	for(unsigned int j = 16; j < 20; j++){
	  quads.append( va[j] );
	}
      }
      //drawing check mark
      for(unsigned int j = 20; j < 28; j++){
	quads.append( va[j] );
      }
      //drawing box border
      for(unsigned int j = 28; j < 36; j++){
	lines.append( va[j] );
      }
    }
  }
 
  mContent->draw(quads);
  mContent->draw(lines);
  drawTexts();
  mContent->display();
  unsigned int count = lines.getVertexCount();
  for(unsigned int j = 0; j < count; j++)
    quads.append( lines[j] );
  return quads;
}
