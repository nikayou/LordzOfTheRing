#ifndef GUIWINDOW_HPP
#define GUIWINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "../headers/GUI_Container.hpp"

class Container;
////////////////////
/// GUIWindow
////////////////////
/// Global container for all sub-elements
////////////////////

class GUIWindow{

private:
  Container * mContentPane; // main container of components
  sf::RenderWindow * mWindow; // window to display
    
public:
  GUIWindow();
  GUIWindow(sf::RenderWindow *);
  GUIWindow(sf::RenderWindow *, Container *);
  // getters
  inline Container * getContentPane() const { return mContentPane; }
  inline sf::RenderWindow * getWindow() const { return mWindow; };
  // setters
  void setContentPane(Container * c );
  void setWindow(sf::RenderWindow * w){ mWindow = w; };
  // misc
  /* opens the window and gives it forced focus (or not) */
  void open(const bool&);
  sf::Vector2i getMouse() const { return sf::Mouse::getPosition(*mWindow); }; 
  /* running drawings and displaying */
  void draw();


};

#endif
