#include "../headers/Misc.hpp"

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
