#include "../headers/OptionState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Checkbox.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/Match.hpp"

#include <sstream>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>

const std::string OptionState::m_optionID = "OPTION_MENU";

void OptionState::update(){
  m_window->update();
  //Game::getInstance()->getMatch()->setTKO(m_tko->isChecked() );
}

void OptionState::render(){
  m_render->clear(sf::Color(120, 120, 120) );
  sf::Color c(100, 100, 100);
  sf::RectangleShape r(sf::Vector2f(730, 80) );
  r.setPosition(35, 100);
  r.setFillColor(c );
  r.setOutlineThickness(1);
  r.setOutlineColor(sf::Color::Black );
  m_render->draw(r);
  r.setPosition(35, 200);
  r.setSize(sf::Vector2f(730, 150 ) );
  m_render->draw(r);
  r.setPosition(35, 370);
  m_render->draw(r);
  for(unsigned int i = 0; i < m_texts.size(); i++)
    m_render->draw(*m_texts[i]);
  sf::Font * f = FontManager::getInstance()->get(DEFAULT_FONT);
  MatchOptions opt = Game::getInstance()->getMatch()->getOptions();
  std::string s = typeToString(opt.mo_type);
  std::ostringstream oss;
  sf::Text t( s, *f, 40);
  t.setColor(sf::Color::Black);
  unsigned int x_arg = 390+(610-390)/2;
  sf::FloatRect box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f+box.left, box.top/2);
  t.setPosition(x_arg, 120);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << opt.mo_roundsNumber;
  t.setString( oss.str() );
   box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f+box.left, box.top/2);
  t.setPosition(x_arg, 220);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << opt.mo_timePerRound;
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f + box.left, box.top/2);
  t.setPosition(x_arg, 290);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << opt.mo_strengthModifier << '%';
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f + box.left, box.top/2);
  t.setPosition(x_arg, 390);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << opt.mo_fatigueModifier << '%';
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.width/2.0f - box.left, box.top/2);
  t.setPosition(x_arg, 460);
  m_render->draw(t);
  m_window->draw();
}

bool OptionState::enter(){
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_window = Game::getInstance()->getGUI();
  m_window->setContentPane(m_container);
  sf::Font * f = FontManager::getInstance()->get(DEFAULT_FONT);
  unsigned int fontsize = 56;
  sf::FloatRect fr;
  sf::Color c(110, 110, 110);
  // title
  sf::Text * l_title = new sf::Text("Match options", *f, fontsize);
  fr = l_title->getLocalBounds();
  l_title->setPosition(400-fr.width/2, 10);
  l_title->setColor(sf::Color::Black);
  m_texts.push_back(l_title);
  // type
  sf::Text * l_type = new sf::Text("Type", *f, fontsize);
  fr = l_type->getLocalBounds();
  l_type->setPosition(70, 140-fr.top-fr.height/2.0);
  l_type->setColor(sf::Color::Black);
  m_texts.push_back(l_type);
  Button * b_ltype = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 120), c);
  b_ltype->setText(sf::Text("<", *f, fontsize) );
  b_ltype->setTextToCenter();
  b_ltype->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getType() == MatchType::KO)
	m->setType( MatchType::DAMAGE);
      else
	m->setType( (MatchType) ( (unsigned int)m->getType()-1) );
    } );
  m_container->add(b_ltype);
  m_buttons.push_back(b_ltype);
  Button * b_rtype = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 120), c);
  b_rtype->setText(sf::Text(">", *f, fontsize) );
  b_rtype->setTextToCenter();
  b_rtype->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getType() == MatchType::DAMAGE)
	m->setType( MatchType::KO);
      else
	m->setType( (MatchType) ( (unsigned int)m->getType()+1) );
    } );
  m_container->add(b_rtype);
  m_buttons.push_back(b_rtype);
  m_tko = new Checkbox(sf::Text("TKO", *f, fontsize*2/3) );
  m_tko->setPosition(sf::Vector2f(660, 120) );
  m_tko->setTextToCenter();
  m_tko->setChecked(Game::getInstance()->getMatch()->getTKO() );
  //m_container->add(m_tko);
  // rounds
  sf::Text * l_rounds = new sf::Text("Rounds", *f, fontsize);
  fr = l_rounds->getLocalBounds();
  l_rounds->setPosition(70, 240-fr.top-fr.height/2.0);
  l_rounds->setColor(sf::Color::Black);
  m_texts.push_back(l_rounds);
  Button * b_lrounds = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 220), c);
  b_lrounds->setText(sf::Text("-", *f, fontsize) );
  b_lrounds->setTextToCenter();
  b_lrounds->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getRoundsNumber() > 1)
	m->setRoundsNumber( m->getRoundsNumber()-1);
    } );
  m_container->add(b_lrounds);
  m_buttons.push_back(b_lrounds);
  Button * b_rrounds = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 220), c);
  b_rrounds->setText(sf::Text("+", *f, fontsize) );
  b_rrounds->setTextToCenter();  
  b_rrounds->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getRoundsNumber() < 30)
	m->setRoundsNumber( m->getRoundsNumber()+1);
    } );
  m_container->add(b_rrounds);
  m_buttons.push_back(b_rrounds);
  // time/round
  sf::Text * l_time = new sf::Text("Time", *f, fontsize);
  fr = l_time->getLocalBounds();
  l_time->setPosition(70, 310-fr.top-fr.height/2.0);
  l_time->setColor(sf::Color::Black);
  m_texts.push_back(l_time);
  Button * b_ltime = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 290), c);
  b_ltime->setText(sf::Text("-", *f, fontsize) );
  b_ltime->setTextToCenter();
  b_ltime->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getTimePerRound() > 10)
	m->setTimePerRound( m->getTimePerRound()-5);
      if(m->getTimePerRound() > 300)
	m->setTimePerRound( m->getTimePerRound()-5);
    } );
  m_container->add(b_ltime);
  m_buttons.push_back(b_ltime);
  Button * b_rtime = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 290), c);
  b_rtime->setText(sf::Text("+", *f, fontsize) );
  b_rtime->setTextToCenter();
  b_rtime->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getTimePerRound() >= 300)
	m->setTimePerRound( m->getTimePerRound()+5);
      if(m->getTimePerRound() < 600)
	m->setTimePerRound( m->getTimePerRound()+5);
    } );
  m_container->add(b_rtime);
  m_buttons.push_back(b_rtime);
  // strength mod
  sf::Text * l_str = new sf::Text("Strength", *f, fontsize);
  fr = l_str->getLocalBounds();
  l_str->setColor(sf::Color::Black);
  l_str->setPosition(70, 410-fr.top-fr.height/2.0);
  m_texts.push_back(l_str);
  Button * b_lstr = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 390), c);
  b_lstr->setText(sf::Text("-", *f, fontsize) );
  b_lstr->setTextToCenter();
  b_lstr->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getStrengthModifier() > 5)
	m->setStrengthModifier( m->getStrengthModifier()-5 );
      if(m->getStrengthModifier() > 200)
	m->setStrengthModifier( m->getStrengthModifier()-5 );
    } );
  m_container->add(b_lstr);
  m_buttons.push_back(b_lstr);
  Button * b_rstr = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 390), c);
  b_rstr->setText(sf::Text("+", *f, fontsize) );
  b_rstr->setTextToCenter();
  b_rstr->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getStrengthModifier() < 300){
	m->setStrengthModifier( m->getStrengthModifier()+5 );
	if(m->getStrengthModifier() > 200)
	  m->setStrengthModifier( m->getStrengthModifier()+5 );
      }
    } );
  m_container->add(b_rstr);
  m_buttons.push_back(b_rstr);
  // fatigue mod
  sf::Text * l_fat = new sf::Text("Fatigue", *f, fontsize);
  fr = l_fat->getLocalBounds();
  l_fat->setPosition(70, 480-fr.top-fr.height/2.0);
  l_fat->setColor(sf::Color::Black);
  m_texts.push_back(l_fat);
  Button * b_lfat = new Button(sf::Vector2u(40, 40), sf::Vector2f(350, 460), c);
  b_lfat->setText(sf::Text("-", *f, fontsize) );
  b_lfat->setTextToCenter();
  b_lfat->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getFatigueModifier() > 5)
	m->setFatigueModifier( m->getFatigueModifier()-5 );
      if(m->getFatigueModifier() > 200)
	m->setFatigueModifier( m->getFatigueModifier()-5 );
    } );
  m_container->add(b_lfat);
  m_buttons.push_back(b_lfat);
  Button * b_rfat = new Button(sf::Vector2u(40, 40), sf::Vector2f(610, 460), c);
  b_rfat->setText(sf::Text("+", *f, fontsize) );
  b_rfat->setTextToCenter();
  b_rfat->setAction( [this]()->void{
      Match * m = Game::getInstance()->getMatch();
      if(m->getFatigueModifier() < 300){
	m->setFatigueModifier( m->getFatigueModifier()+5 );
	if(m->getFatigueModifier() > 200)
	  m->setFatigueModifier( m->getFatigueModifier()+5 );
      }
    } );
  m_container->add(b_rfat);
  m_buttons.push_back(b_rfat);
  // state buttons
  Button * b_back = new Button(sf::Vector2u(60, 40), sf::Vector2f(270, 540), sf::Color(200, 100, 100) );
  b_back->setText(sf::Text("<-", *f, fontsize) );
  b_back->setTextToCenter();
  b_back->setAction( [this]()->void{
      Game::getInstance()->getStateHandler()->change(new MainMenuState() );
    } );
  m_container->add(b_back);
  m_buttons.push_back(b_back);
  Button * b_ok = new Button(sf::Vector2u(60, 40), sf::Vector2f(530, 540), sf::Color(100,200,100) );
  b_ok->setText(sf::Text("- >", *f, fontsize) );
  b_ok->setTextToCenter();
  b_ok->setAction( [this]()->void{
      Game::getInstance()->getStateHandler()->change(new CharacterState() );
    } );
  m_container->add(b_ok);
  m_buttons.push_back(b_ok);
  return true;
}

bool OptionState::exit(){

  return true;
}

void OptionState::deleteAll(){
  unsigned int s = m_buttons.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_buttons[i];
    m_buttons[i] = NULL;
  }
  delete m_tko;
  m_tko = NULL;
  s = m_texts.size();
  for(unsigned int i = 0; i < s; i++){
    delete m_buttons[i];
    m_buttons[i] = NULL;
  }
  delete m_container;
  m_container = NULL;
 
}

std::string OptionState::typeToString(const MatchType& m){
  if(m == MatchType::KO)
    return "KO";
  if(m == MatchType::ROUND)
    return "Rounds";
  if(m == MatchType::DAMAGE)
    return "Damages";
  return "???";
}
