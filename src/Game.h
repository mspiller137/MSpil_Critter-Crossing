
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void mousePressed(sf::Event event);
  void mouseReleased(sf::Event event);




 private:
  sf::RenderWindow& window;

  std::string game_state;

  bool playSelected = true;
  sf::Font font;
  sf::Text menuTitle;
  sf::Text menuPlayOption;
  sf::Text menuQuitOption;

  int lives;
  int score;
  sf::Text livesLeftText;
  sf::Text scoreText;
  sf::Text countdownText;

  bool hasWon = false;
  bool continueSelected = true;
  sf::Text hasWonText;
  sf::Text endContinueOption;
  sf::Text endQuitOption;

  sf::Clock countdownClock;

  bool passportAccepted;
  bool passportRejected;
  bool shouldAccept;
  bool buttonsVisible = false;
  bool stampVisible = false;

  sf::Sprite* dragged = nullptr;

  sf::Sprite* background;
  sf::Texture backgroundTexture;

  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Texture* characterTextures = new sf::Texture[3];
  sf::Texture* passportTextures = new sf::Texture[3];

  sf::Sprite* acceptButton;
  sf::Sprite* rejectButton;
  sf::Texture* buttonTextures = new sf::Texture[2];

  sf::Sprite* stamp;
  sf::Texture* stampTextures = new sf::Texture[2];

  bool loadTextures();
  void newCharacter();
  void dragSprite(sf::Sprite* sprite);
  void stampPassport(bool isAccepted);
  void returnPassport();
  void reset();
  void endGame();

};

#endif // PLATFORMER_GAME_H
