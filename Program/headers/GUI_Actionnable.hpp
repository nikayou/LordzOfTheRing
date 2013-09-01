#ifndef ACTIONNABLE_HPP
#define ACTIONNABLE_HPP

////////////////////
/// Actionnable interface
////////////////////
/// Useful for telling action to do when something can be clicked on.
///////////////////
class Actionnable{
protected:
  std::function<void ()> mAction; //Action to do when actionned
    
public:    
  /* change the action to perform. It has to be on the following format :
   [ captured variables ]() -> void{ ... }   */
  void setAction( std::function<void ()> f ){ 
    mAction = f; };
  /* performs the action */
  virtual void action(){ mAction (); };
};

#endif
