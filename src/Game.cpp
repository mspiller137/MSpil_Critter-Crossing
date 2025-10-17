
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	character = new sf::Sprite;
	passport = new sf::Sprite;

	

	if (!loadTextures()) {
		return false;
	}


  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

}

bool Game::loadTextures() {
	//TODO - Rename files and remove hardcoding later
	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			characterTextures[i].loadFromFile("../Data/CritterCustoms/elephant.png");
			passportTextures[i].loadFromFile("../Data/CritterCustoms/elephant passport.png");
			break;
		case 1:
			characterTextures[i].loadFromFile("../Data/CritterCustoms/moose.png");
			passportTextures[i].loadFromFile("../Data/CritterCustoms/moose passport.png");
			break;
		case 2:
			characterTextures[i].loadFromFile("../Data/CritterCustoms/penguin.png");
			passportTextures[i].loadFromFile("../Data/CritterCustoms/penguin passport.png");
			break;
		}		
	}
}


