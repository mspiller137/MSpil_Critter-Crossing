
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete[] characterTextures;
	delete[] passportTextures;
	delete background;
	delete character;
	delete passport;
}

bool Game::init()
{
	character = new sf::Sprite;
	passport = new sf::Sprite;
	background = new sf::Sprite;


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
	window.draw(*background);
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
	
	backgroundTexture.loadFromFile("../Data/WhackaMole Worksheet/background.png");
	background->setTexture(backgroundTexture);
	background->setScale(
		window.getSize().x / background->getGlobalBounds().width,
		window.getSize().y / background->getGlobalBounds().height);

	std::string characterPath;
	std::string passportPath;
	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			characterPath = "../Data/CritterCustoms/elephant.png";
			passportPath = "../Data/CritterCustoms/elephant passport.png";
			break;
		case 1:
			characterPath = "../Data/CritterCustoms/moose.png";
			passportPath = "../Data/CritterCustoms/moose passport.png";
			break;
		case 2:
			characterPath = "../Data/CritterCustoms/penguin.png";
			passportPath = "../Data/CritterCustoms/penguin passport.png";
			break;
		}
		if (!characterTextures[i].loadFromFile(characterPath))
		{
			std::cout << "Error: texture failed to load at " << characterPath << "\n ";
			return false;
		}
		if (!passportTextures[i].loadFromFile(passportPath))
		{
			std::cout << "Error: texture failed to load at " << passportPath << "\n ";
			return false;
		}
	}
	return true;
}


