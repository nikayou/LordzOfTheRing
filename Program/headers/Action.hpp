/** here we define actions : 
a doer, an action, and a target.
An action can be handled in one byte, so we provide functions to
convert all these elements from/to bytes.

To help with synchronisation, we also provides "states" : they can be
used to tell, for instance : "the action has began, but not performed yet".

The framing tells how many times does the "phase" of the action lasts
*/

#ifndef ACTION_HPP
#define ACTION_HPP

#include "../headers/Misc.hpp"

#include <string>
#include <vector>

typedef byte action;
/** An action can be described in one byte:
    ABCDEFGH with
    A = 0-1 for action's maker (see typedef enum subject)
    B = 0-1 for action's target (optionnal, see enum subject)
    CDEFGH = 000000-111111 for action term (up to 64 actions), see enum Type.
*/

namespace Action{
  typedef enum{
    UNKNOWN = 0,
    NONE = 1,
    ATTACK_LEFT,
    ATTACK_MIDDLE,
    ATTACK_RIGHT,
    DODGE_LEFT,
    DODGE_MIDDLE,
    DODGE_RIGHT,
    STROKE,
    KO,
    HAPPY,
    RAISING,
    STUN,
    BREATHING,
    PAUSE,
    ACTIONS_COUNT
  } Type; //all kind of actions, from the input to the end
  

  typedef enum{
    PLAYER1 = 0,
    PLAYER2 = 1
  } Subject; //who does/receives the action

 
  //retrieves in a Subject the first bit of the action
  Subject getDoer(const action&);

  //retrieves in a Subject the second bit of the action
  Subject getTarget(const action&);

  //retrieves in an action Type the last 6 bits of the action
  Type getType(const action&);

  //returns the number matching the given subject (1 or 0 shifted left 7)
  byte doerToByte(const Action::Subject&);

  //returns the number matching the given subject (1 or 0 shifted left 6)
  byte targetToByte(const Action::Subject&);

  //returns a complete action, with bit shifting
  byte actionToByte(const Action::Type&, const Action::Subject& doer = Action::PLAYER1, const Action::Subject& target = Action::PLAYER1);

  //returns a string in format DOER-TARGET-ACTION
  std::string actionToString(const action&);

  //returns a string in format ACTION
  std::string typeToString(const Action::Type&);

  //returns the action associated with the string given
  Action::Type stringToType(const std::string&);

  // Here begin all the framing stuff, for synchro of actions (and animations)
  
  typedef enum{
    NORMAL = 0,
    ATTACKING,
    DODGING,
    CRYING
  } State; //effective action (ex : the hit is not given when we press the key)

  typedef struct{
    unsigned short nb_frames; //number of frames of the action
    unsigned short change_state; //index of the frame where the state changes (or not if >= nb_frames)
    unsigned short return_state; //index where the situation gets back to normal
    State state;
  } Framing;

  extern Framing Framing_None;
  extern Framing Framing_AttackL;
  extern Framing Framing_AttackM;
  extern Framing Framing_AttackR;
  extern Framing Framing_DodgeL;
  extern Framing Framing_DodgeM;
  extern Framing Framing_DodgeR;
  extern Framing Framing_Stroke;
  extern Framing Framing_KO;
  extern Framing Framing_Raising;
  Framing initFramingN();
  Framing initFramingAL();
  Framing initFramingAM();
  Framing initFramingAR();
  Framing initFramingDL();
  Framing initFramingDM();
  Framing initFramingDR();
  Framing initFramingStroke();
  Framing initFramingKO();
  Framing initFramingRaising();
  Framing initFramingStun();
  Framing initFramingBreathing();
  //Framing * getFraming(const std::string&);
}



#endif
