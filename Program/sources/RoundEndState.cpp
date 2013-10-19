#include "../headers/RoundEndState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/Config.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GameState.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/Match.hpp"
#include "../headers/MatchState.hpp"
#include "../headers/Player.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <sstream>
#include <functional>

const std::string RoundEndState::m_roundID = "ROUND";

void RoundEndState::update(){
  while(Game::getInstance()->getTime() < 5.){
    m_window->update();
  }
  if(Game::getInstance()->getMatch()->isFinished() ){
    Game::getInstance()->getStateHandler()->change(new CharacterState() );
  }else{
    Game::getInstance()->getStateHandler()->change(new MatchState() );
  }
}

void RoundEndState::render(){
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  //score displaying
  s.setTexture(*t);
  displayScore(&s);
  m_window->draw();
}

bool RoundEndState::enter(){
  m_render = Game::getInstance()->getRender();
  Game::getInstance()->setUpdating(true);
  m_container = new Container(m_render );
  m_window = Game::getInstance()->getGUI();
  m_window->setContentPane(m_container);
  sf::Sprite s, s2;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  //score displaying
  s2.setTexture(*t);
  displayScore(&s2);
  //collapse screen
  t = TextureManager::getInstance()->get("loading")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 800, 200) );
  s.setPosition(0, 400);
  m_render->draw(s);
  m_window->draw();
  int dec = 0;
  Game::getInstance()->getClock()->restart();
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    displayScore(&s2);
    s.setPosition(dec, 0);
    m_render->draw(s);
    s.setPosition(0, 200);
    m_render->draw(s);
    s.setPosition(0, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 0;
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    displayScore(&s2);
    s.setPosition(-dec, 200);
    m_render->draw(s);
    s.setPosition(0, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 0;
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    displayScore(&s2);
    s.setPosition(dec, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  return true;
}

bool RoundEndState::exit(){
  //if we already did the number of rounds, the match ends
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("loading")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 80, 200) );
  m_render->draw(s);
  m_window->draw();
  int dec = 0;
  Game::getInstance()->getClock()->restart();
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    s.setPosition(dec, 0);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 800;
  while(dec >= 0){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    s.setPosition(dec, 200);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec -= 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 0;
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    s.setPosition(dec, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  
  Game::getInstance()->setUpdating(false);
  // end displaying
  return true;
}

void RoundEndState::deleteAll(){
  delete m_container;
  m_container = NULL;
}

void RoundEndState::displayScore(sf::Sprite * s){
  m_render->clear(sf::Color(120, 120, 120) );
  std::ostringstream oss;
  Match * m = Game::getInstance()->getMatch();
  //frame
  static unsigned int fontsize = 80;
  static unsigned int left_border = 180, right_border = 780, up_border = 100, down_border = 580;
  static unsigned int y1 = up_border+120, y2 = y1+(down_border-y1)/2;
  static unsigned int x2 = left_border+(right_border-left_border)/2, x1 = left_border + (x2-left_border)/2, x3 = x2+(right_border-x2)/2;
  static unsigned int width = right_border-left_border, height = down_border-up_border;
  sf::RectangleShape r(sf::Vector2f(width, height) );
  r.setPosition(left_border, 100);
  r.setFillColor(sf::Color(40, 40, 40) );
  r.setOutlineThickness(4);
  r.setOutlineColor(sf::Color::Black );
  m_render->draw(r);
  r.setOutlineThickness(2);
  //vertical separator
  r.setSize(sf::Vector2f(0, height) );
  r.setPosition(x2 , up_border);
  m_render->draw(r);
  //1st line
  r.setSize(sf::Vector2f(width, 0) );
  r.setPosition(left_border, y1);
  m_render->draw(r);
  //2nde line
  r.setSize(sf::Vector2f(width, 0) );
  r.setPosition(left_border, y2);
  m_render->draw(r);
  //Round count, and socre description
  sf::Text t;
  t.setFont(*FontManager::getInstance()->get("../../resources/chubby_cheeks.ttf") );
  t.setColor(sf::Color::Black);
  t.setCharacterSize(60);
  t.setString("Wins" );
  sf::FloatRect box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(left_border/2, y1+(y2-y1)/2);
  m_render->draw(t);
  t.setString("Score" );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(left_border/2, y2+(down_border-y2)/2);
  m_render->draw(t);
  t.setCharacterSize(fontsize);
  oss.str("");
  oss.clear();
  oss << "Round " << m->getCurrentRound() << "/" << m->getRoundsNumber();
  t.setString(oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(400, up_border/2);
  m_render->draw(t);
  //players's names
  t.setFont(*FontManager::getInstance()->get("../../resources/charlie_dotted.ttf") );
  t.setColor(sf::Color::Yellow);
  t.setString(m->getPlayer1()->getName() );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(x1, up_border+(y1-up_border)/2 );
  m_render->draw(t);
  t.setString(m->getPlayer2()->getName());
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(x3, up_border+(y1-up_border)/2);
  m_render->draw(t);
  //global score
  oss.str("");
  oss.clear();
  oss << m->getPlayer1()->getVictories();
  t.setPosition(x1, y1+(y2-y1)/2);
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << m->getPlayer2()->getVictories();
  t.setString(oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(x3, y1+(y2-y1)/2); 
  m_render->draw(t);
  //local score
  t.setPosition(x1, y2+(down_border-y2)/2); 
  oss.str("");
  oss.clear();
  oss << m->getPlayer1()->getPoints();
  t.setString( oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  m_render->draw(t);
  oss.str("");
  oss.clear();
  oss << m->getPlayer2()->getPoints();
  t.setString(oss.str() );
  box = t.getLocalBounds();
  t.setOrigin(box.left + box.width/2.0f, box.top + box.height/2.0f);
  t.setPosition(x3, y2+(down_border-y2)/2);
  m_render->draw(t);
  
}
