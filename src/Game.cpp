
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
	delete[] buttonTextures;
	delete[] stampTextures;
	delete background;
	delete character;
	delete passport;
	delete acceptButton;
	delete rejectButton;
	delete stamp;
}

bool Game::init()
{
	character = new sf::Sprite;
	passport = new sf::Sprite;
	background = new sf::Sprite;
	acceptButton = new sf::Sprite;
	rejectButton = new sf::Sprite;
	stamp = new sf::Sprite;

	if (!loadTextures()) {
		return false;
	}

	newCharacter();

	return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
	if (stampVisible) {
		stamp->setPosition(passport->getPosition().x + 50, passport->getPosition().y + 50);
	}
}

void Game::render()
{
	window.draw(*background);
	window.draw(*character);
	window.draw(*passport);
	window.draw(*stamp);
	if (buttonsVisible) {
		window.draw(*acceptButton);
		window.draw(*rejectButton);
	}	
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);

}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event) {

}

void Game::mousePressed(sf::Event event) {
	std::cout << "press ping \n";
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
	if (event.mouseButton.button == sf::Mouse::Left) {
		//std::cout << "left ping";

		if (passport->getGlobalBounds().contains(clickf)) {
			dragged = passport;
		}

		if (acceptButton->getGlobalBounds().contains(clickf)) {
			//Trigger Accept
			stampPassport(true);
		}
		else if (rejectButton->getGlobalBounds().contains(clickf)) {
			//Trigger Accept
			stampPassport(false);
		}
		else {
			buttonsVisible = false;
			acceptButton->setPosition(-100, -100);
			rejectButton->setPosition(-100, -100);
		}
	}
	else if (event.mouseButton.button == sf::Mouse::Right) {
		//if right clicking passport, bring up contextual
		if (passport->getGlobalBounds().contains(clickf)) {
			buttonsVisible = true;
			acceptButton->setPosition(clickf.x + 50, clickf.y - 50);
			rejectButton->setPosition(clickf.x + 50, clickf.y + 50);
		}
		else {
			buttonsVisible = false;
			acceptButton->setPosition(-100, -100);
			rejectButton->setPosition(-100, -100);
		}
	}
}

void Game::mouseReleased(sf::Event event) {
	std::cout << "release ping\n";
	if (event.mouseButton.button == sf::Mouse::Left) {		
		dragged = nullptr;
	}
}

bool Game::loadTextures() {
	//TODO - Rename files and remove hardcoding later

	if (!backgroundTexture.loadFromFile("../Data/WhackaMole Worksheet/background.png")) {
		std::cout << "Error: texture failed to load at ../Data/WhackaMole Worksheet/background.png \n ";
		return false;
	}
	background->setTexture(backgroundTexture);
	background->setScale(
		window.getSize().x / background->getGlobalBounds().width,
		window.getSize().y / background->getGlobalBounds().height);

	//TODO - Tweak button position
	if (!buttonTextures[0].loadFromFile("../Data/CritterCustoms/accept button.png")) {
		std::cout << "Error: texture failed to load at ../Data/CritterCustoms/accept button.png \n ";
		return false;
	}
	acceptButton->setTexture(buttonTextures[0]);
	acceptButton->setPosition(-100, -100);
	acceptButton->setScale(0.5, 0.5);
	if (!buttonTextures[1].loadFromFile("../Data/CritterCustoms/reject button.png")) {
		std::cout << "Error: texture failed to load at ../Data/CritterCustoms/reject button.png \n ";
		return false;
	}
	rejectButton->setTexture(buttonTextures[1]);
	rejectButton->setPosition(-100,-100);
	rejectButton->setScale(0.5, 0.5);

	if (!stampTextures[0].loadFromFile("../Data/CritterCustoms/reject.png")) {
		std::cout << "Error: texture failed to load at ../Data/CritterCustoms/reject.png \n ";
		return false;
	}
	if (!stampTextures[1].loadFromFile("../Data/CritterCustoms/accept.png")) {
		std::cout << "Error: texture failed to load at ../Data/CritterCustoms/accept.png \n ";
		return false;
	}	

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
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 4);
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

void Game::stampPassport(bool isAccepted) {
	buttonsVisible = false;
	acceptButton->setPosition(-100, -100);
	rejectButton->setPosition(-100, -100);
	stampVisible = true;
	stamp->setTexture(stampTextures[static_cast<int>(isAccepted)]);
	stamp->setPosition(passport->getPosition().x + 50, passport->getPosition().y + 50);
}


