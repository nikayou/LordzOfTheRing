#include <cstdio> //DELETE

#include "../headers/Action.hpp"

#include <sstream>
#include <string>
#include <vector>

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
    case PAUSE: return "Pause"; break;
    default: return "Unknown"; break;
    }
    return "Unknown";
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

  Framing initFramingN(){ 
    Framing _f;
    _f.nb_frames = 4;
    _f.change_state = -1;
    _f.return_state = -1;
    return _f;
  }

  Framing initFramingAL(){
    Framing _f;
    _f.nb_frames = 9;
    _f.change_state = 5;
    _f.return_state = 6;
    _f.state = ATTACKING;
    //preparing -2
    //striking -4
    //pausing -2
    //recovering -1
    return _f;
  }

  Framing initFramingAM(){
    Framing _f;
    _f.nb_frames = 11;
    _f.change_state = 5;
    _f.return_state = 6;
    _f.state = ATTACKING;
    //preparing -3
    //striking -3
    //pausing -3
    //recovering -2
    return _f;
  }

  Framing initFramingAR(){
    Framing _f;
    _f.nb_frames = 9;
    _f.change_state = 5;
    _f.return_state = 6;
    _f.state = ATTACKING;
    //preparing -2
    //striking -4
    //pausing -2
    //recovering -1
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


}
