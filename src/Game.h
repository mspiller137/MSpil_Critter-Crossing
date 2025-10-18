
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

  bool passportAccepted;
  bool passportRejected;
  bool shouldAccept;

  sf::Sprite* dragged = nullptr;

  sf::Sprite* background;
  sf::Texture backgroundTexture;
  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Texture* characterTextures = new sf::Texture[3];
  sf::Texture* passportTextures = new sf::Texture[3];


  bool loadTextures();
  void newCharacter();
  void dragSprite(sf::Sprite* sprite);

};

#endif // PLATFORMER_GAME_H
