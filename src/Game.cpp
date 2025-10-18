
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

	newCharacter();

	return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
}

void Game::render()
{
	window.draw(*background);
	window.draw(*character);
	window.draw(*passport);
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	std::cout << "click ping";
	sf::Vector2i click = sf::Mouse::getPosition(window);

}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event) {

}

void Game::mousePressed(sf::Event event) {
	std::cout << "press ping";
	if (event.mouseButton.button == sf::Mouse::Left) {
		std::cout << "left ping";
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport->getGlobalBounds().contains(clickf)) {
			dragged = passport;
		}
	}
}

void Game::mouseReleased(sf::Event event) {
	if (event.mouseButton.button == sf::Mouse::Left) {		
		dragged = nullptr;
	}
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

void Game::newCharacter() {
	passportAccepted = false;
	passportRejected = false;

	int characterIndex = rand() % 3;
	int passportIndex = rand() % 3;

	if (characterIndex == passportIndex) {
		shouldAccept = true;
	}
	else {
		shouldAccept = false;
	}

	character->setTexture(characterTextures[characterIndex], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passportTextures[passportIndex], true);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

void Game::dragSprite(sf::Sprite* sprite) {
	if (sprite != nullptr) {
		sf::Vector2f dragOffset(sf::Vector2f(sprite->getGlobalBounds().getSize().x / 2, sprite->getGlobalBounds().getSize().y / 2));

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f mousePositionf = static_cast<sf::Vector2f>(mousePosition);

		sf::Vector2f dragPosition = mousePositionf - dragOffset;
		sprite->setPosition(dragPosition.x, dragPosition.y);
	}
}


