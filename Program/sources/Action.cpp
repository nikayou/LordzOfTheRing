/** Here we define actions : 
a doer, an action, and a target.
An action can be handled in one byte, so we provide functions to
convert all these elements from/to bytes.

To help with synchronisation, we also provides "states" : they can be
used to tell, for instance : "the action has began, but not performed yet".

The framing tells how many times does the "phase" of the action lasts, and has
to be sync with animations
*/

#include "../headers/Action.hpp"

#include <sstream>
#include <string>

namespace Action{

  Subject getDoer(const action& a){
    int f = (1<<7);
    return (Subject)( (a&f) == 0?0:1 );
  }

  Subject getTarget(const action& a){
    int f= 1<<6;
    return (Subject)( (a&f) == 0?0:1 );
  }

  Type getType(const action& a){
    int f = 1 + (1<<1) + (1<<2) + (1<<3) + (1<<4) + (1<<5);
    return (Type) (a&f);
  }


  byte doerToByte(const Subject& d){
    return d<<7;
  }

  byte targetToByte(const Subject& t){
    return t<<6;
  }

  byte actionToByte(const Type& a, const Subject& doer, const Subject& target){
    return a+(doer<<7)+(target<<6);
  }


  std::string actionToString(const action& a){
    std::ostringstream oss;
    if(getDoer(a) == PLAYER1){
      oss << "Player1 - ";
    }else{
      oss << "Player2 - ";
    }
    oss << typeToString(getType(a) );
    return oss.str();
  }

  std::string typeToString(const Type& t){
    switch( t ){
    case NONE: return "None"; break;
    case ATTACK_LEFT: return "Attack Left"; break;
    case ATTACK_MIDDLE: return "Uppercut"; break;
    case ATTACK_RIGHT: return "Attack Right"; break;
    case DODGE_LEFT: return "Dodge Left"; break;
    case DODGE_MIDDLE: return "Dodge Middle"; break;
    case DODGE_RIGHT: return "Dodge Right"; break;
    case STROKE: return "Stroke"; break;
    case KO: return "KO"; break;
    case HAPPY: return "Happy"; break;
    case STUN: return "Stun"; break;
    case BREATHING: return "Breathing"; break;
    case PAUSE: return "Pause"; break;
    default: return "Unknown"; break;
    }
    return "Unknown";
  }


  //returns the action associated with the string given
  Action::Type stringToType(const std::string& s){
    if(s.compare("stand") == 0)
      return NONE;
    if(s.compare("punchL") == 0 || s.compare("attackL") == 0)
      return ATTACK_LEFT;
    if(s.compare("punchR") == 0 || s.compare("attackR") == 0)
      return ATTACK_RIGHT;
    if(s.compare("punchM") == 0 || s.compare("attackM") == 0)
      return ATTACK_MIDDLE;
    if(s.compare("dodgeL") == 0)
      return DODGE_LEFT;
    if(s.compare("dodgeR") == 0)
      return DODGE_RIGHT;
    if(s.compare("dodgeM") == 0)
      return DODGE_MIDDLE;
    if(s.compare("stroke") == 0)
      return STROKE;
    if(s.compare("ko") == 0 || s.compare("KO") == 0)
      return KO;
    if(s.compare("stun") == 0 )
      return STUN;
    if(s.compare("breathing") == 0)
      return BREATHING;
    if(s.compare("happy") == 0)
      return HAPPY;
    if(s.compare("raising") == 0)
      return RAISING;
    return UNKNOWN;
  }


  // Here begin all the framing stuff, for synchro of actions (and animations)

  Framing Framing_None = initFramingN();
  Framing Framing_AttackL = initFramingAL();
  Framing Framing_AttackM = initFramingAM();
  Framing Framing_AttackR = initFramingAR();
  Framing Framing_DodgeL = initFramingDL();
  Framing Framing_DodgeM = initFramingDM();
  Framing Framing_DodgeR = initFramingDR();
  Framing Framing_Stroke = initFramingStroke();
  Framing Framing_KO = initFramingKO();
  Framing Framing_Raising = initFramingRaising();
  Framing Framing_Happy = initFramingHappy();
  Framing Framing_Stun = initFramingStun();
  Framing Framing_Breathing = initFramingBreathing();


  Framing initFramingN(){ 
    Framing _f;
    _f.nb_frames = 6;
    _f.change_state = 0;
    _f.return_state = -1;
    _f.state = NORMAL;
    return _f;
  }

  Framing initFramingAL(){
    Framing _f;
    _f.nb_frames = 10;
    _f.change_state = 4;
    _f.return_state = 5;
    _f.state = ATTACKING;
    //preparing -1
    //pausing - 2
    //launching - 1
    //striking - 1
    //pausing - 3
    //recovering -2
    return _f;
  }

  Framing initFramingAM(){
    Framing _f;
    _f.nb_frames = 14;
    _f.change_state = 6;
    _f.return_state = 7;
    _f.state = ATTACKING;
    //preparing -1
    //pausing - 4
    //launching - 1
    //striking - 1
    //pausing -4
    //recovering -3
    return _f;
  }

  Framing initFramingAR(){
    Framing _f;
    _f.nb_frames = 10;
    _f.change_state = 4;
    _f.return_state = 5;
    _f.state = ATTACKING;
    //preparing -1
    //pausing - 2
    //launching - 1
    //striking - 1
    //pausing - 3
    //recovering -2
    return _f;
  }

  Framing initFramingDL(){ 
    Framing _f;
    _f.nb_frames = 3; //moving, pausing, recovering
    _f.change_state = 0;
    _f.return_state = 2;
    _f.state = DODGING;
    return _f;
  }

  Framing initFramingDM(){ 
    Framing _f;
    _f.nb_frames = 3; //moving, pausing, recovering
    _f.change_state = 0;
    _f.return_state = 2;
    _f.state = DODGING;
    return _f;
  }

  Framing initFramingDR(){ 
    Framing _f;
    _f.nb_frames = 3; //moving, pausing, recovering
    _f.change_state = 0;
    _f.return_state = 2;
    _f.state = DODGING;
    return _f;
  }

  Framing initFramingStroke(){
    Framing _f;
    _f.nb_frames = 3; //crying (2) - recovering (1)
    _f.change_state = 0;
    _f.return_state = 2;
    _f.state = CRYING;
    return _f;
  }

  Framing initFramingKO(){
    Framing _f;
    _f.nb_frames = 15; //fallling (2+2+1+1+1) + 8 of pausing
    _f.change_state = 0;
    _f.return_state = -1;
    _f.state = CRYING;
    return _f;
  }

  Framing initFramingRaising(){
    Framing _f;
    _f.nb_frames = 10; // 3+3+1+1+1
    _f.change_state = 0;
    _f.return_state = 8;
    _f.state = CRYING;
    return _f;
  }

  Framing initFramingHappy(){
    Framing _f;
    _f.nb_frames = 25; //cycles of 6 (2+1+2+1)
    _f.change_state = 0;
    _f.return_state = 24;
    return _f;
  }

  Framing initFramingStun(){
    Framing _f;
    _f.nb_frames = 16;
    _f.change_state = 0;
    _f.return_state = 15;
    _f.state = NORMAL;
    return _f;
  }


  Framing initFramingBreathing(){
    Framing _f;
    _f.nb_frames = 16;
    _f.change_state = 0;
    _f.return_state = 15;
    _f.state = NORMAL;
    return _f;
  }


}
