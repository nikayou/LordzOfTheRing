#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include <string>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GUI_TextComponent.hpp"

////////////////////
/// Checkboxes
////////////////////
/// Can have an associated text, and a border
////////////////////

#define CHECKBOX_WIDTH 16
#define MARGIN_BOX 4 //space around the box
#define PADDING_BOX 2 // space around the text

class Checkbox : public TextComponent{
private:
  bool mChecked; // tells if the checkbox is checked

public:
  Checkbox();
  Checkbox(const sf::Text&);
  Checkbox(const std::string&);
  inline bool changeState(){ 
    return (mChecked = !mChecked);
  };
  // getters
  inline std::string getClass(){ return "Checkbox"; };
  inline bool isChecked() const { return mChecked; };
  // setters
  void setChecked(const bool& b){ mChecked = b; };
  void setPosition(const sf::Vector2f&);
  // misc
  void setTextToCenter();
	/* tells if the point is inside the checkbox */
  bool contains(const sf::Vector2i&);
  /* Sets all the vertices in position/color and return them. */
  sf::VertexArray draw();
};

#endif
