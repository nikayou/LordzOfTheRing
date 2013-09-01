#ifndef MISC_HPP
#define MISC_HPP

#define MAX(x, y) ( (x)>(y) )?(x):(y)
#define MIN(x,y) ( (x)>(y) )?(y):(x)
typedef char byte;

#include <string>
#include <SFML/Graphics/Color.hpp>

#define LUMINESCENCE 3*128

namespace Color{
  sf::Color brighter(const sf::Color&);
  sf::Color darker(const sf::Color&);
  sf::Color denser(const sf::Color&);
  sf::Color gauzier(const sf::Color&);
}

/**
   Cuts the given string from the given char to the end
 */
std::string cutFrom(const std::string&, char);

/** Does the first string contain the second string ? */
bool contains(const std::string&, const std::string&);

/** Retrieves first int after the first '=' */
unsigned int extractInt(const std::string&);

/** Retrieves first int after the first c */
unsigned int extractInt(const std::string& s, const char& c);

#endif
