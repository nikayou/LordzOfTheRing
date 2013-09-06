#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "../headers/Singleton.hpp"

class Random:public Singleton<Random>{

private:
  unsigned int m_randoms[100];

public:
  Random(){ init(); };
  void init();
  unsigned int get();
  unsigned int get(const unsigned int& inf, const unsigned int& sup);

};

#endif
