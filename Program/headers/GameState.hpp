#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
namespace StateID{

  typedef enum{
    SPLASH,
    MAIN_MENU,
    OPTIONS_MENU,
    PROFILE_MENU,
    CHARACTER_MENU,
    MATCH,
    PAUSE
  } ID;
}

class GameState{

public:
  virtual ~GameState(){};
  virtual void update() = 0;
  virtual void render() = 0;
  virtual bool enter() = 0;
  virtual bool exit() = 0;
  virtual std::string getID() const = 0;
  virtual void deleteAll() = 0; // may be useless : do a "delete" delete also the members ?


};

#endif
