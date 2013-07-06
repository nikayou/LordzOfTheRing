#ifndef ACTION_HPP
#define ACTION_HPP

#include "../headers/Misc.hpp"

#include <string>
#include <vector>

typedef byte action;
/** An action can be described in one byte:
 ABCDEFGH with
A = 0-1 for action's maker (see typedef enum subject)
B= 0-1 for action's target (optionnal, see enum subject)
CDEFGH = 000000-111111 for action term (up to 64 actions), see enum Type.
*/

namespace Action{
  typedef enum{
    UNKNOWN = 0,
    NORMAL = 1,
    ATTACK_LEFT,
    ATTACK_MIDDLE,
    ATTACK_RIGHT,
    DODGE_LEFT,
    DODGE_MIDDLE,
    DODGE_RIGHT,
    STROKE,
    KO,
    SUPER_STRIKE,
    PAUSE,
    ACTIONS_COUNT
  } Type;
  
  typedef enum{
    PLAYER1 = 0,
    PLAYER2
  } Subject;

 
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


  // Here begin all the framing stuff, for synchro of actions (and animations)
  
  typedef struct{
    unsigned short nb_frames;
    //animation
  } Framing_t;

  extern std::vector< Framing_t > Framing_AttackL;
  extern std::vector< Framing_t > Framing_AttackM;
  extern std::vector< Framing_t > Framing_AttackR;
  extern std::vector< Framing_t > Framing_DodgeL;
  extern std::vector< Framing_t > Framing_DodgeM;
  extern std::vector< Framing_t > Framing_DodgeR;
  extern std::vector< Framing_t > Framing_Stroke;
  std::vector< Framing_t > initFramingAL();
  std::vector< Framing_t > initFramingAM();
  std::vector< Framing_t > initFramingAR();
  std::vector< Framing_t > initFramingDL();
  std::vector< Framing_t > initFramingDM();
  std::vector< Framing_t > initFramingDR();
  std::vector< Framing_t > initFramingStroke();
}



#endif
