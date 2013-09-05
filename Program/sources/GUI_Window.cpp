
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/System/Thread.hpp>

#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"


//////////////////////////////
/// INTERFACE
//////////////////////////////

GUIWindow::GUIWindow(){
  if(mWindow != NULL)
    mWindow->create(sf::VideoMode(800,600), "Window", sf::Style::Titlebar|sf::Style::Close);
  if(mContentPane != NULL)
    mContentPane->setContainer(this);
}

GUIWindow::GUIWindow(sf::RenderWindow * w){
  mWindow = w;
  if(mContentPane != NULL)
    mContentPane->setContainer(this);
}

GUIWindow::GUIWindow(sf::RenderWindow * w, Container * c){
  mWindow = w;
  mContentPane = c;
  mContentPane->setContainer(this);
}

void GUIWindow::setContentPane(Container * c ){
  mContentPane = c;
  if(mContentPane != NULL)
    mContentPane->setContainer(this);
}

void GUIWindow::draw(){
  sf::Sprite s;
    //controls
    sf::Event event;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) )
	  mContentPane->click( );
    mContentPane->draw();
    s.setTexture( mContentPane->getContent()->getTexture()  );
    s.setPosition( sf::Vector2f(mContentPane->getX(), mContentPane->getY() )  );
    mWindow->draw(s);
  }


/* opens the window and gives it forced focus (or not) */
void GUIWindow::open(const bool& focus){
  if(focus){
    //sf::Thread t( &loop(this) );
    //t.launch();
  }else{
    draw();
  }
}
