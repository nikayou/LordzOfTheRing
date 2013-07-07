#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

/** Defines all kinds of resistances/strengths that a character can deploy. **/
namespace Stats{
  typedef enum{
    WEAKEST = 0,
    WEAKER,
    WEAK,
    MEDIUM,
    STRONG,
    STRONGER,
    STRONGEST
  } stats;
}

class Character{

protected:
  std::string m_name;
  unsigned short m_health;
  Stats::stats m_resistance; //amount of hits he can get before stunning
  Stats::stats m_attack; //Light punches strenght
  Stats::stats m_stamina; //recovery time when K.O
  

public:
  //constructors
  Character();
  Character(const std::string&, const unsigned short&, const Stats::stats&, const Stats::stats&, const Stats::stats&);
  ~Character();
  //getters
  std::string getName() const{ 
    return m_name; 
  };
  unsigned short getHealth() const{ 
    return m_health; 
  };
  Stats::stats getResistance() const{ 
    return m_resistance; 
  };
  Stats::stats getAttack() const{
    return m_attack; 
  };
  Stats::stats getStamina() const{ 
    return m_stamina; 
  };
  //setters
  void setName(const std::string& value){  
    m_name = value; 
  };
  void setHealth(const unsigned short& value){  
    m_health = value; 
  };
  void setResistance(const Stats::stats& value){  
    m_resistance = value; 
  };
  void setAttack(const Stats::stats& value){  
    m_attack = value; 
  };
  void setStamina(const Stats::stats& value){  
    m_stamina = value; 
  };
  //others
  std::string toString();

};

#endif
