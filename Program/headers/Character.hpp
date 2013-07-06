#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

/** Defines all kinds of resistances/strengths that a character can deploy. **/
namespace Stats{
  typedef enum{
    WEAKEST = 0,
    WEAK,
    MEDIUM,
    STRONG,
    STRONGEST
  } stats;
}

class Character{

protected:
  unsigned short m_health;
  Stats::stats m_LResistance; //resistance to light punches
  Stats::stats m_HResistance; //resistance to hard punches
  Stats::stats m_LAttack; //Light punches strenght
  Stats::stats m_HAttack; //Hard punches strenght
  Stats::stats m_stamina; //recovery time when K.O
  Stats::stats m_dodging; //dodging speed and recovery time
  

public:
  //constructors
  Character();
  Character(const unsigned short&, const Stats::stats&, const Stats::stats&, const Stats::stats&, const Stats::stats&, const Stats::stats&, const Stats::stats&);
  ~Character();
  //getters
  unsigned short getHealth() const{ 
    return m_health; 
  };
  Stats::stats getLResistance() const{ 
    return m_LResistance; 
  };
  Stats::stats getHResistance() const{ 
    return m_HResistance; 
  };
  Stats::stats getLAttack() const{
    return m_LAttack; 
  };
  Stats::stats getHAttack() const{ 
    return m_HAttack; 
  };
  Stats::stats getStamina() const{ 
    return m_stamina; 
  };
  Stats::stats getDodging() const{ 
    return m_dodging; 
  };
  //setters  
  void setHealth(const unsigned short& value){  
    m_health = value; 
  };
  void setLResistance(const Stats::stats& value){  
    m_LResistance = value; 
  };
  void setHResistance(const Stats::stats& value){  
    m_HResistance = value; 
  };
  void setLAttack(const Stats::stats& value){  
    m_LAttack = value; 
  };
  void setHAttack(const Stats::stats& value){  
    m_HAttack = value; 
  };
  void setStamina(const Stats::stats& value){  
    m_stamina = value; 
  };
  void setDodging(const Stats::stats& value){  
    m_dodging = value; 
  };
  //others
  std::string toString();

};

#endif
