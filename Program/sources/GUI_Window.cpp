
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

GUIWindow::~GUIWindow(){
  //mContentPane->~Container();
}

void GUIWindow::setContentPane(Container * c ){
  mContentPane = c;
  if(mContentPane != NULL)
    mContentPane->setContainer(this);
}

void GUIWindow::update(){
  //if(sf::Mouse::isButtonPressed(sf::Mouse::Left) )
  //  mContentPane->click( );
  sf::Event event;
  if(mWindow->isOpen() ){
    //controls
    while(mWindow && mWindow->pollEvent(event) ){
      if (event.type == sf::Event::Closed){
	mWindow->close();
	continue;
      }
      if (event.type == sf::Event::MouseMoved){
	mContentPane->updateFocus();
      }
      if (event.type == sf::Event::MouseButtonPressed){
	if(event.mouseButton.button == sf::Mouse::Left){
	  mContentPane->click( );
	  continue;
	}
      }
      if (event.type == sf::Event::KeyPressed){
	if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Left){
	  mContentPane->focusUp();
	  continue;
	}
	if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Right){
	  mContentPane->focusDown();
	  continue;
	}
	if(event.key.code == sf::Keyboard::Space){
	  mContentPane->click();
	  continue;
	}
      }
    }
  }
}

void GUIWindow::draw(){
  sf::Sprite s;
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
