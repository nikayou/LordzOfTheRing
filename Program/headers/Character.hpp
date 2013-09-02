/** Here we define a character. They are kind of constants, because these are not those who "play", just the general attributes.
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#define CHAR_DIR "../../resources/characters/"

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
  
  unsigned short toHealth(const Stats::stats& v);
  unsigned short toStamina(const Stats::stats& v);
  unsigned short toResistance(const Stats::stats& v);
  unsigned short toAttack(const Stats::stats& v);

  stats baseHealth(const unsigned short&);
  stats baseStamina(const unsigned short&);
  stats baseResistance(const unsigned short&);
  stats baseAttack(const unsigned short&);
}

class Character{

protected:
  std::string m_name;
  std::string m_basename; //basename for related files searching
  unsigned short m_health;
  unsigned short m_resistance; //amount of hits he can get before stunning
  unsigned short m_attack; //Light punches strenght
  unsigned short m_stamina; //number of hits/dodge he can do (1 hit = 2 dodges)

public:
  //constructors
  Character(const std::string& = "Unknown",
	    const unsigned short& = 100, 
	    const unsigned short& = 25, 
	    const unsigned short& = 3,
	    const unsigned short& = 70);
  ~Character();
  //getters
  std::string getName() const{ 
    return m_name; 
  };
  unsigned short getHealth() const{ 
    return m_health; 
  };
  unsigned short getResistance() const{ 
    return m_resistance; 
  };
  unsigned short getAttack() const{
    return m_attack; 
  };
  unsigned short getStamina() const{ 
    return m_stamina; 
  };
  std::string getBasename() const{
    return m_basename;
  };
  //setters
  void setName(const std::string& value){  
    m_name = value; 
  };
  void setHealth(const unsigned short& value){  
    m_health = value; 
  };
  void setResistance(const unsigned short& value){  
    m_resistance = value; 
  };
  void setAttack(const unsigned short& value){  
    m_attack = value; 
  };
  void setStamina(const unsigned short& value){  
    m_stamina = value; 
  };
  void setBasename(const std::string& value){
    m_basename = value;
  };
  //others
  static std::string getClass(){
    return "Character";
  };
  std::string toString();
  bool loadFromFile(const std::string&);

};

#endif
