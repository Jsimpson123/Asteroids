// A C++ SFML program with snowfall and a moving spaceship - Justin Simpson

#include <iostream>  
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <String>
#include <cstdlib>
#include <windows.h>
#include "Collision.hpp"

using namespace std;
using namespace sf;

// define render window size constants
#define winWidth 736
#define winHeight 552


const int NUM_FRAMES = 8; // Number of frames in the explosion animation
const int FRAME_WIDTH = 64; // Width of each frame in the explosion sprite sheet
const int FRAME_HEIGHT = 64; // Height of each frame in the explosion sprite sheet

void displayGameOverScreen(sf::RenderWindow& window)
{

	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Clear the window to black
	window.clear(Color::Black);

	// Set the game over text
	Text gameOverText;
	gameOverText.setFont(font); // Set the font for the text
	gameOverText.setString("Game Over!");
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setStyle(sf::Text::Bold);

	// Set the position of the texts
	sf::Vector2u windowSize = window.getSize();
	gameOverText.setPosition((windowSize.x - gameOverText.getLocalBounds().width) / 2, (windowSize.y - gameOverText.getLocalBounds().height) / 2);
	
	// Draw the texts
	window.draw(gameOverText);

	// Display the window
	window.display();

	// Wait for the player to press space
	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}
	}
}

void displayWinScreen(sf::RenderWindow& window)
{

	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Clear the window to black
	window.clear(Color::Black);

	// Set the game over text
	Text gameOverText;
	gameOverText.setFont(font); // Set the font for the text
	gameOverText.setString("You Won!");
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::Blue);
	gameOverText.setStyle(sf::Text::Bold);

	// Set the position of the texts
	sf::Vector2u windowSize = window.getSize();
	gameOverText.setPosition((windowSize.x - gameOverText.getLocalBounds().width) / 2, (windowSize.y - gameOverText.getLocalBounds().height) / 2);

	// Draw the texts
	window.draw(gameOverText);

	// Display the window
	window.display();

	// Wait for the player to press space
	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}
	}
}


int main()
{

	int score = 0;

	// Create the window
	RenderWindow window(VideoMode(winWidth, winHeight), "Asteroids!");

	// Set the framerate limit to 60 FPS
	window.setFramerateLimit(60);

	// Texture set up
	Texture tex_background, tex_spaceship, tex_asteroid, tex_bullet, tex_scrapMetal, explosionTexture;
	tex_background.loadFromFile("winter_night.jpg");
	tex_spaceship.loadFromFile("spaceship.png");
	tex_asteroid.loadFromFile("asteroid.png");
	tex_bullet.loadFromFile("bullet.png");
	tex_scrapMetal.loadFromFile("scrapMetal.png");
	explosionTexture.loadFromFile("explosion.png");


	// Set up each sprite (Position, scale etc.)
	Sprite spr_background, spr_asteroid, spr_bullet, spr_spaceship, spr_scrapMetal, explosionSprite;

	
	Sprite* Selected_Piece;
	Selected_Piece = &spr_spaceship;



	spr_background.setTexture(tex_background);

	spr_spaceship.setTexture(tex_spaceship);
	spr_spaceship.scale(Vector2f(0.15f, 0.15f));
	spr_spaceship.setPosition(Vector2f(winWidth / 3, winHeight / 1.5)); // absolute position

	spr_asteroid.setTexture(tex_asteroid);
	spr_asteroid.scale(Vector2f(0.15f, 0.15f));
	spr_asteroid.setPosition(Vector2f(winWidth / 2, winHeight / 2));

	spr_bullet.setTexture(tex_bullet);
	spr_bullet.scale(Vector2f(0.15f, 0.15f));

	spr_scrapMetal.setTexture(tex_scrapMetal);
	spr_scrapMetal.scale(Vector2f(0.1f, 0.1f));

	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT / 2); // Set the origin to the center of the sprite


	// Create a clock to track the elapsed time for the animation
	Clock clock;


	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Set up CircleShape vector

	vector<Sprite> octagon;
	vector<Sprite> bullets;
	vector<Sprite> scrapMetal;

	// Gets the size of the window
	Vector2f spritePosition = spr_bullet.getPosition();

	// Set the time value to 0
	Time elapsedTime;

	// Run the program as long as the window is open
	while (window.isOpen())
	{
		// Check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		// spaceship moves left when left key is pressed and is set to a certain scale
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			//spr_spaceship.setScale(0.15f, 0.15f);
			//spr_spaceship.move(-4.0f, 0.0f);
			spr_spaceship.setPosition(spr_spaceship.getPosition().x - 4, spr_spaceship.getPosition().y);
		}

		// spaceship moves right when right key is pressed and is set to a certain scale
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			//spr_spaceship.setScale(-0.15f, 0.15f);
			//spr_spaceship.move(4.0f, 0.0f);
			spr_spaceship.setPosition(spr_spaceship.getPosition().x + 4, spr_spaceship.getPosition().y);
		}

		// spaceship moves up when up key is pressed and is set to a certain scale
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			//spr_spaceship.setScale(-0.15f, 0.15f);
			spr_spaceship.move(0.0f, -4.0f);
		}

		// spaceship moves down when down key is pressed and is set to a certain scale
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			//spr_spaceship.setScale(-0.15f, 0.15f);
			spr_spaceship.move(0.0f, 4.0f);
		}

		sf::Vector2f spaceshipPos = spr_spaceship.getPosition();
		const float spaceshipWidth = spr_spaceship.getGlobalBounds().width;
		const float spaceshipHeight = spr_spaceship.getGlobalBounds().height;
		if (spaceshipPos.x < 0) {
			spr_spaceship.setPosition(0, spaceshipPos.y);
		}

		// Check if the spaceship is outside the right side of the screen
		if (spaceshipPos.x + spaceshipWidth > winWidth) {
			spr_spaceship.setPosition(winWidth - spaceshipWidth, spr_spaceship.getPosition().y);
		}

		if (spaceshipPos.y < 0) {
			spr_spaceship.setPosition(spaceshipPos.x, 0);
		}

		// Check if the spaceship is outside the right side of the screen
		if (spaceshipPos.y + spaceshipHeight > winHeight) {
			spr_spaceship.setPosition(spr_spaceship.getPosition().x, winHeight - spaceshipHeight);
		}
	
		 // clear the window with black color
		window.clear(Color::Black);

		// Draw everything here...
		window.draw(spr_background);
		window.draw(*Selected_Piece);
		//window.draw(spr_asteroid);


		float min = 10;
		float max = 25;

		// Adds a new element at the end of the vector, after its current last element
		octagon.push_back(Sprite(spr_asteroid));


		float size = 0.1 + (rand() / (float)RAND_MAX) * 0.2;

		// Sets the next octagons in the vectors radius to less than 6
		octagon.back().setScale(size, size);

		float bulletSize = 6;

		int lastBulletIndex = -1;

		bullets.push_back(Sprite(spr_bullet));



		// Allows octagons to constantly fall
		for (size_t i = 0; i < octagon.size(); i++)
		{
			size_t removed = 0;
			while (octagon.size() - removed > 75)
			{
				// Remove a quarter of the octagons from the vector
				octagon.erase(octagon.begin() + octagon.size() / 4, octagon.end());
				removed += octagon.size() / 4;
			}

			// Allows the octagons to have the swaying motion 
			octagon[i].rotate(rand() % 3);

			// Sets the position of the next octagons randomly across the top of the screen
			octagon.back().setPosition(rand() % winWidth, -200);

			// Allows the octagons to move down
			octagon[i].move(0, 1);

			if (octagon[i].getPosition().y > winHeight + 50) {
				// Remove the octagon from the vector
				octagon.erase(octagon.begin() + i);

			}

			// Draws the octagons according to the positon of i
			window.draw(octagon[i]);



		
	
		
		


			// Allows bullets to constantly shoot
			for (size_t j = lastBulletIndex + 1; j < bullets.size(); j++)
			{
					// Sets the position of the next bullets to shoot from the ship
					bullets.back().setPosition(spr_spaceship.getPosition().x + 45, spr_spaceship.getPosition().y);

					// Draws the bullets according to j and allows the bullets to move

					window.draw(bullets[j]);
					bullets[j].move(0, -4);

				if (Collision::PixelPerfectTest(bullets[j], octagon[i])) {

					cout << "BulletCollision" << endl;

					// Add a new scrap metal sprite to the vector
					scrapMetal.push_back(Sprite(spr_scrapMetal));
					// Set the position of the scrap metal sprite to the position of the destroyed octagon
					scrapMetal.back().setPosition(octagon[i].getPosition());

					octagon.erase(octagon.begin() + i);
					j--;

				}

				bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
					[&](const sf::Sprite& spr_bullet)
					{
						sf::Vector2u screenSize = window.getSize();
						sf::Vector2f spritePosition = spr_bullet.getPosition();
						return spritePosition.x > screenSize.x || spritePosition.y > screenSize.y ||
							spritePosition.x < 0 || spritePosition.y < 0;
					}), bullets.end()); 

			


				if (Collision::PixelPerfectTest(spr_spaceship, octagon[i])) {

					cout << "Collision" << endl;
					//spr_spaceship.setColor(Color::Transparent);
					//delete &Selected_Piece;

					displayGameOverScreen(window);

				}
			}
		}

		lastBulletIndex = bullets.size() - 1; // Update the index of the last bullet added to the game

		for (int i = 0; i < scrapMetal.size(); i++) {
			scrapMetal[i].move(0, 2); // Move the scrap metal downwards
			window.draw(scrapMetal[i]);

			// Check for a collision between the spaceship and the scrap metal
			if (Collision::PixelPerfectTest(spr_spaceship, scrapMetal[i])) {

				score++; // Increment the score
				cout << "Scrap metal collected!" << endl;

				// Remove the scrap metal from the game
				scrapMetal.erase(scrapMetal.begin() + i);
				i--;
			}
		}

		if (score == 50) {

			displayWinScreen(window);
		
		}


		
		// Display the score on the screen
		sf::Text text;
		text.setFont(font); // Set the font for the text
		text.setString("Score: " + std::to_string(score)); // Set the text to display the current score
		text.setCharacterSize(45.0f); // Set the character size
		text.setFillColor(sf::Color::Black); // Set the text color
		window.draw(text); // Draw the text on the screen
	

		// end the current frame
		window.display();

		elapsedTime = clock.getElapsedTime();
	}
	return 0;
}