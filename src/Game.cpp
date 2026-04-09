
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
	game_state = "menu";
	score = 0;
	lives = 3;
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
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}

	menuTitle.setFont(font);
	menuTitle.setString("Critters Crossing");
	menuTitle.setCharacterSize(75);
	menuTitle.setFillColor(sf::Color(0, 0, 255, 255));
	menuTitle.setPosition(
		window.getSize().x / 2 - menuTitle.getGlobalBounds().width / 2,
		(window.getSize().y / 4) - menuTitle.getGlobalBounds().height / 2);

	menuPlayOption.setFont(font);
	menuPlayOption.setString("> Play <");
	menuPlayOption.setCharacterSize(50);
	menuPlayOption.setFillColor(sf::Color(0, 0, 255, 255));
	menuPlayOption.setPosition(
		(window.getSize().x / 8 * 3) - menuPlayOption.getGlobalBounds().width / 2,
		(window.getSize().y / 8 * 5) - menuPlayOption.getGlobalBounds().height / 2);

	menuQuitOption.setFont(font);
	menuQuitOption.setString("Quit");
	menuQuitOption.setCharacterSize(50);
	menuQuitOption.setFillColor(sf::Color(0, 0, 255, 255));
	menuQuitOption.setPosition(
		(window.getSize().x / 8 * 5) - menuQuitOption.getGlobalBounds().width / 2,
		(window.getSize().y / 8 * 5) - menuQuitOption.getGlobalBounds().height / 2);

	scoreText.setFont(font);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color(0, 0, 255, 255));
	scoreText.setPosition(
		(window.getSize().x / 8 * 3) - scoreText.getGlobalBounds().width / 2,
		(window.getSize().y / 8 * 7) - scoreText.getGlobalBounds().height / 2 + 50);

	livesLeftText.setFont(font);
	livesLeftText.setString("Lives: 3");
	livesLeftText.setCharacterSize(50);
	livesLeftText.setFillColor(sf::Color(0, 0, 255, 255));
	livesLeftText.setPosition(
		(window.getSize().x / 8 * 5) - livesLeftText.getGlobalBounds().width / 2,
		(window.getSize().y / 8 * 7) - livesLeftText.getGlobalBounds().height / 2 + 50);

	countdownText.setFont(font);
	countdownText.setString("Lives: 3");
	countdownText.setCharacterSize(50);
	countdownText.setFillColor(sf::Color(0, 0, 255, 255));
	countdownText.setPosition(
		(window.getSize().x / 8 * 7) - countdownText.getGlobalBounds().width / 2,
		(window.getSize().y / 8 ) - countdownText.getGlobalBounds().height / 2);

	hasWonText.setFont(font);
	hasWonText.setString("");
	hasWonText.setCharacterSize(75);
	hasWonText.setFillColor(sf::Color(0, 0, 255, 255));
	hasWonText.setPosition(
		window.getSize().x / 2 - hasWonText.getGlobalBounds().width / 2,
		(window.getSize().y / 4) - hasWonText.getGlobalBounds().height / 2);

	endContinueOption.setFont(font);
	endContinueOption.setString("> Continue <");
	endContinueOption.setCharacterSize(50);
	endContinueOption.setFillColor(sf::Color(0, 0, 255, 255));
	endContinueOption.setPosition(
		(window.getSize().x / 8 * 3) - endContinueOption.getGlobalBounds().width / 2,
		(window.getSize().y / 8 * 5) - endContinueOption.getGlobalBounds().height / 2);

	endQuitOption.setFont(font);
	endQuitOption.setString("Quit");
	endQuitOption.setCharacterSize(50);
	endQuitOption.setFillColor(sf::Color(0, 0, 255, 255));
	endQuitOption.setPosition(
		(window.getSize().x / 8 * 5) - endQuitOption.getGlobalBounds().width / 2,
		(window.getSize().y / 8 * 5) - endQuitOption.getGlobalBounds().height / 2);


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
	if (game_state == "game") {
		countdownText.setString(std::to_string(static_cast<int>(60.0f - countdownClock.getElapsedTime().asSeconds())));
		if (lives == 0) {
			hasWon = false;
			endGame();
		}
		if (countdownClock.getElapsedTime().asSeconds() <= 0.0f) {
			hasWon = true;
			endGame();
		}
		dragSprite(dragged);
		if (stampVisible) {
			stamp->setPosition(passport->getPosition().x + 50, passport->getPosition().y + 50);
		}
	}	
}

void Game::render()
{
	window.draw(*background);
	if (game_state == "menu") {
		window.draw(menuTitle);
		window.draw(menuPlayOption);
		window.draw(menuQuitOption);
	}
	else if (game_state == "game") {
		window.draw(scoreText);
		window.draw(livesLeftText);
		window.draw(*character);
		window.draw(*passport);
		if (stampVisible) {
			window.draw(*stamp);
		}		
		if (buttonsVisible) {
			window.draw(*acceptButton);
			window.draw(*rejectButton);
		}
		window.draw(countdownText);
	}
	else if (game_state == "end") {
		window.draw(hasWonText);
		window.draw(endContinueOption);
		window.draw(endQuitOption);
	}	
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);

}

void Game::keyPressed(sf::Event event)
{
	if (game_state == "menu") {
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			if (playSelected) {
				menuPlayOption.setString("Play");
				menuQuitOption.setString("> Quit <");
				playSelected = false;
			}
			else {
				menuPlayOption.setString("> Play <");
				menuQuitOption.setString("Quit");
				playSelected = true;
			}
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (playSelected) {
				countdownClock.restart();
				game_state = "game";
			}
			else {
				window.close();
			}
		}
	}
	else if (game_state == "end") {
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			if (continueSelected) {
				endContinueOption.setString("Continue");
				endQuitOption.setString("> Quit <");
				continueSelected = false;
			}
			else {
				endContinueOption.setString("> Continue <");
				endQuitOption.setString("Quit");
				continueSelected = true;
			}
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (continueSelected) {
				reset();
				game_state = "menu";
			}
			else {
				window.close();
			}
		}
	}
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
			passportAccepted = true;
		}
		else if (rejectButton->getGlobalBounds().contains(clickf)) {
			//Trigger Accept
			stampPassport(false);
			passportRejected = true;
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

	sf::IntRect passportRect(passport->getPosition().x, passport->getPosition().y, passport->getGlobalBounds().getSize().x, passport->getGlobalBounds().getSize().y);
	sf::IntRect characterRect(character->getPosition().x, character->getPosition().y, character->getGlobalBounds().getSize().x, character->getGlobalBounds().getSize().y);
	if (passportRect.intersects(characterRect)) {
		returnPassport();
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
	rejectButton->setPosition(-100, -100);
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
	stampVisible = false;	

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
	//TODO - Update to not move passport to be centred on mouse
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

void Game::returnPassport() {
	if (stampVisible) {
		if ((shouldAccept && passportAccepted) || (!shouldAccept && passportRejected)) {
			//correct option, increment score and spawn new set
			score++;
			std::string newString = "Score: " + std::to_string(score);
			scoreText.setString(newString);
		}
		else {
			//wrong option, decrease score and spawn new set
			lives--;
			std::string newString = "Lives: " + std::to_string(lives);
			livesLeftText.setString(newString);
		}
		stampVisible = false;
		newCharacter();
	}
	else {
		//Has not been stamped, return to player
		std::cout << "return to player";
		passport->setPosition(window.getSize().x / 2, window.getSize().y / 4);
	}

}

void Game::reset() {
	playSelected = true;
	hasWon = false;
	continueSelected = true;
	score = 0;
	lives = 3;
	scoreText.setString("Score: 0");
	livesLeftText.setString("Lives: 3");
	dragged = nullptr;
	countdownClock.restart();
}

void Game::endGame() {
	std::string newString = "";
	if (hasWon) {
		newString = "You win with a score of " + std::to_string(score) + "!";
	}
	else {
		newString = "You lose with a score of " + std::to_string(score) + "!";
	}
	hasWonText.setString(newString);
	hasWonText.setPosition(
		window.getSize().x / 2 - hasWonText.getGlobalBounds().width / 2,
		(window.getSize().y / 4) - hasWonText.getGlobalBounds().height / 2);
	game_state = "end";
}


