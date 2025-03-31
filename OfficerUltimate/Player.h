#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class player {
public:
	sf::Sprite pSprite;

	player() {

	}

	player(std::string imgDirectory) {
		if (!pTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		pSprite.setTexture(pTexture);
	}

	void drawTo(sf::RenderWindow &window)
	{
		window.draw(pSprite);
	}

	void move(sf::Vector2f distance)
	{
		pSprite.move(distance);
	}

	void setPos(sf::Vector2f newPos) {
		pSprite.setPosition(newPos);
	}

	int getY() {
		return pSprite.getPosition().y;
	}

	//void update() {
	//	if (!onGround) dy = dy + 0.0005*time;
	//	rect.top += dy*time;
	//	onGround = false;



	//}



private:
	sf::Texture pTexture;


};