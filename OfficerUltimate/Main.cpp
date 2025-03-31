#include <SFML/Graphics.hpp>
#include "player.h"

float offsetX = 0, offsetY = 0;

const int H = 17;
const int W = 150;

sf::String TileMap[H] = {
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	"0                                                                                                                                                    0",
	"0                                                                                    w                                                               0",
	"0                   w                                  w                   w                                                                         0",
	"0                                      w                                                                                                             0",
	"0                                                                                                                                                    0",
	"0                      c                                                                                                                             0",
	"0                                                                                                                                                    0",
	"0                                                                                                                                                    0",
	"0                                                                                                                                                    0",
	"0               c    rrrrrr                                                                                                                          0",
	"0                                                                        rrrrr                                                                       0",
	"0G                                                                  rrrrrrrrrr                                                                       0",
	"0                                                               rrrrrrrrrrrrrr                                                                       0",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};

int main()
{
	sf::Vector2i screen(1500, 700);
	sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

	sf::View view;
	view.reset(sf::FloatRect(0, 0, screen.x, screen.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f position(screen.x / 2, screen.y / 2);

	player myPlayer("1.png");
	myPlayer.setPos({ 100, 400 });

	//Grawitacja
	const int groundeHeight = 400;
	const float speed = 2;
	float gravitySpeed = 2.0f;
	const float jump = 3.0f;
	bool isJumping = false;
	sf::Vector2f velocity(sf::Vector2f(0, 0));

	enum Direction { Down, Left, Right, Up };
	sf::Vector2i source(1, Down);

	sf::RectangleShape shape(sf::Vector2f(48, 48));

	sf::Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;
		if (time > 20) time = 20;

		sf::Event event;
		//const float moveSpeed = 0.2;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		//	myPlayer.move;
		//}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			source.y = Left;
			velocity.x = -speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			source.y = Right;
			velocity.x = speed;
		}
		else
			velocity.x = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (myPlayer.getY() > 100)
			{
				myPlayer.move({ 0,-jump });
				isJumping = true;
			}

		}

		//TU JEST GRAWATACJA

		if (myPlayer.getY() < groundeHeight && isJumping == false)
		{
			myPlayer.move({ 0,gravitySpeed });
		}

		/*myPlayer.update(time);*/

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyReleased:
				isJumping = false;


			}


		}

		myPlayer.move({ velocity.x, velocity.y });


		window.clear(sf::Color::White);

		for (int i = 0; i<H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'k')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'c')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 't') shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'g')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'G')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'd')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'w')  shape.setFillColor(sf::Color::Black);

				if (TileMap[i][j] == 'r') { shape.setFillColor(sf::Color::Black);

				if (myPlayer.pSprite.getGlobalBounds().intersects(shape.getGlobalBounds()))
				{
					gravitySpeed = 0;
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					gravitySpeed = 2.0f;
				}
				}

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;


				shape.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(shape);
			}

		if (myPlayer.pSprite.getPosition().x + 10 > screen.x / 2)
			position.x = myPlayer.pSprite.getPosition().x + 10;
		else
			position.x = screen.x / 2;


		view.setCenter(position);
		window.setView(view);
		myPlayer.drawTo(window);
		window.display();
	}

	return 0;
}