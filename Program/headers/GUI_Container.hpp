#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

#include "../headers/GUI_Component.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"

class GUIWindow;

class Container : public Component{
private:
  sf::RenderTexture * mContent; //where we are drawing the components
  std::vector< Component * > mComponents; //all the components
  unsigned int mFocused; //component on which mouse is positioned (0 for not)
  GUIWindow * mContainer; //reference to the container (parent)

public:
  Container();
  Container(sf::RenderTexture *);
  ~Container();
  // getters
  inline sf::RenderTexture * getContent() const { return mContent; };
  inline GUIWindow * getContainer() const { return mContainer; };
  // setters
  void setContent(sf::RenderTexture * rt){ mContent = rt; };
  void setContainer(GUIWindow * w){ mContainer = w; };
  // misc
  bool add(Component *);
  void updateFocus();
  void focusUp();
  void focusDown();
  /* Clicks on the given position, return value tells if we are closing the window (false) */
  bool click(const sf::Vector2i&);
  /* Clicks on the mouse position (relative) */
  bool click();
  /* returns relative position of mouse */
  sf::Vector2i getLocalMouse();
  /* displays all components' texts */
  void drawTexts();
  /* draw all the components in the content */
  sf::VertexArray draw();

};

#endif
