#include "../headers/Misc.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cstdlib>
#include <string>

/**
   Cuts the given string from the given char to the end
 */
std::string cutFrom(const std::string& s, char c){
  return s.substr( s.find_first_of(c)+1, std::string::npos);
}

/** Does the first string contain the second string ? */
bool contains(const std::string& s, const std::string& sub){
  return ( s.find(sub) != std::string::npos);
}

/** Retrieves first int after the first '=' */
unsigned int extractInt(const std::string& s){
  return atoi( cutFrom(s, '=').c_str() );
}


/** Retrieves first int after the first c */
unsigned int extractInt(const std::string& s, const char& c){
  return atoi( cutFrom(s, c).c_str() );
}


namespace Color{
  
  sf::Color brighter(const sf::Color& i){
    sf::Color o(
		MIN(255, i.r+38),
		MIN(255, i.g+38),
		MIN(255, i.b+38),
		i.a
		);
    return o;
  }

  sf::Color darker(const sf::Color& i){
    sf::Color o(
		MAX(0, i.r-38),
		MAX(0, i.g-38),
		MAX(0, i.b-38),
		i.a
		);
    return o;
  }

  sf::Color gauzier(const sf::Color& i){
    sf::Color o(
		i.r, i.g, i.b, 
		MAX(0, i.a-38)
		);
    return o;
  }

  sf::Color denser(const sf::Color& i){
    sf::Color o(
		i.r, i.g, i.b, 
		MIN(255, i.a+38)
		);
    return o;
  }
}
