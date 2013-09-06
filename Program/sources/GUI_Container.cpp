#include <cstdio> //delete
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Checkbox.hpp"
#include "../headers/GUI_Container.hpp"

Container::Container(){
  mContent->create(1, 1);
  //mContent->setFramerateLimit(35);
  mContainer = NULL;
}

Container::Container(sf::RenderTexture* rt){
  mContent = rt;
  mContainer = NULL;
}

Container::~Container(){

}

bool Container::add(Component * c){
  mComponents.push_back(c);
  return true;
}

void Container::updateFocus(){
  /* sf::Vector2i pos = sf::Mouse::getPosition(*mWindow);
     unsigned int s = mButtons.size();
     for(unsigned int i = 0; i < s; i++){
     if(contains(mButtons[i], pos) ){
     mFocused = mButtons[i];
     return;
     }
     }   
     mFocused = NULL;
  */
}

void Container::click(const sf::Vector2i& pos){
  unsigned int nb = mComponents.size();
  for(unsigned int i = 0; i < nb; i++){
    if(i >= mComponents.size() || mComponents[i] == NULL)
      return;
    if(mComponents[i]->getClass().compare("Button") == 0){
      Button * b = (Button *) mComponents[i];
      if(b->contains(pos) )
	b->action();
    }else if(mComponents[i]->getClass().compare("Checkbox") == 0){
      Checkbox * c = (Checkbox *) mComponents[i];
      if(c->contains(pos) )
	c->changeState();
    }
  }
}

void Container::click(){
  click(getLocalMouse() );
}

sf::Vector2i Container::getLocalMouse(){
  sf::Vector2i mouse = mContainer->getMouse();
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
      if( b->contains( mouse ) ){
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
  //printf("Finished drawing in texture : %d vertices in quads\n", quads.getVertexCount() );
  mContent->draw(quads);
  mContent->draw(lines);
  drawTexts();
  mContent->display();
  unsigned int count = lines.getVertexCount();
  for(unsigned int j = 0; j < count; j++)
    quads.append( lines[j] );
  return quads;
}
