
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




 private:
  sf::RenderWindow& window;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* characterTextures = new sf::Texture[3];
  sf::Texture* passportTextures = new sf::Texture[3];


  bool loadTextures();

};

#endif // PLATFORMER_GAME_H
