#ifndef ACTIONNABLE_HPP
#define ACTIONNABLE_HPP

#include <functional>
////////////////////
/// Actionnable interface
////////////////////
/// Useful for telling action to do when something can be clicked on.
///////////////////
class Actionnable{

protected:
  std::function<void ()> mAction; //Action to do when actionned
  bool m_closing; //tells if we are closing the window with this action
    
public:    
  /* change the action to perform. It has to be on the following format :
   [ captured variables ](args) -> return type{ ... }   */
  void setAction( std::function<void ()> f ){ 
    mAction = f; };
  /* performs the action */
  bool action(){ mAction (); return !m_closing; };
  /* change the value telling if we close the window with the action or not*/
  void setCloser(const bool& v){
    m_closing = v;
  }
};

#endif
