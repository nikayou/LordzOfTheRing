#ifndef MISC_HPP
#define MISC_HPP

#define MAX(x, y) ( (x)>(y) )?(x):(y)
#define MIN(x,y) ( (x)>(y) )?(y):(x)
typedef char byte;

#include <string>

/**
   Cuts the given string from the given char to the end
 */
std::string cutFrom(const std::string&, char);

/** Does the first string contain the second string ? */
bool contains(const std::string&, const std::string&);

/** Retrieves first int after the first '=' */
unsigned int extractInt(const std::string&);

#endif
