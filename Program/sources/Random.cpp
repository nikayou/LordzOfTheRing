#include "../headers/Random.hpp"
#include <cstdlib>
#include <cstdlib>
#include <ctime>

void Random::init(){
  std::srand ( std::time(NULL) );
  for (unsigned char c =0; c < 100; c++)
    this->m_randoms[c] = rand();
}

unsigned int Random::get(const unsigned int& inf, const unsigned int& sup){
  unsigned int index = (int)(rand()%100);
  unsigned int res = this->m_randoms[index];
  this->m_randoms[index] = rand();
  return res%sup+inf;
}

unsigned int Random::get(){
 unsigned int index = (int)(rand()%100);
  unsigned int res = this->m_randoms[index];
  this->m_randoms[index] = rand();
  return res;
}
