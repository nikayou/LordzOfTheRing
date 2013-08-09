/** Here we define a character. They are kind of constants, because these are not those who "play", just the general attributes.
 */

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

  stats fromString(const std::string&);
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
  Character(const std::string& = "Unknown",
		     const unsigned short& = 100, 
		     const Stats::stats& = Stats::MEDIUM, 
		     const Stats::stats& = Stats::MEDIUM, 
		     const Stats::stats& = Stats::MEDIUM);
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
  static std::string getClass(){
    return "Character";
  };
  std::string toString();
  bool loadFromFile(const std::string&);

};

#endif
