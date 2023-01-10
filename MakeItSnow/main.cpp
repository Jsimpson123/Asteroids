// A C++ SFML program with falling asteroids and a moving spaceship - Justin Simpson

// Imports
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

// Function to display the Game Over screen
void displayGameOverScreen(sf::RenderWindow& window)
{
	// Load font
	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Clear the window to black
	window.clear(Color::Black);

	// Create the game over text
	Text gameOverText;
	gameOverText.setFont(font); 
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

	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Closes the window
			if (event.type == Event::Closed)
				window.close();
		}
	}
}

// Function to display the Game Over screen
void displayWinScreen(sf::RenderWindow& window)
{

	// Load font
	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Clear the window to black
	window.clear(Color::Black);

	// Create the You Won text
	Text winText;
	winText.setFont(font); 
	winText.setString("You Won!");
	winText.setCharacterSize(40);
	winText.setFillColor(sf::Color::Blue);
	winText.setStyle(sf::Text::Bold);

	// Set the position of the texts
	sf::Vector2u windowSize = window.getSize();
	winText.setPosition((windowSize.x - winText.getLocalBounds().width) / 2, (windowSize.y - winText.getLocalBounds().height) / 2);

	// Draw the texts
	window.draw(winText);

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

void Asteroids() {

	// Defining the score and setting it to 0
	int score = 0;

	// Create the window
	RenderWindow window(VideoMode(winWidth, winHeight), "Asteroids!");

	// Set the framerate limit to 60 FPS
	window.setFramerateLimit(60);

	// Texture set up
	Texture tex_background, tex_spaceship, tex_asteroid, tex_bullet, tex_scrapMetal, explosionTexture;
	tex_background.loadFromFile("stars.png");
	tex_spaceship.loadFromFile("spaceship.png");
	tex_asteroid.loadFromFile("asteroid.png");
	tex_bullet.loadFromFile("bullet.png");
	tex_scrapMetal.loadFromFile("scrapMetal.png");

	// Set up each sprite (Position, scale etc.)
	Sprite spr_background, spr_asteroid, spr_bullet, spr_spaceship, spr_scrapMetal, explosionSprite;

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

	// Set up explosion sound
	SoundBuffer buffer;
	if (!buffer.loadFromFile("explosion.wav")) {
		// Error loading sound file
	}

	Sound explosionSound;
	explosionSound.setBuffer(buffer);

	// Set up dead sound
	SoundBuffer buffer1;
	if (!buffer1.loadFromFile("dead.wav")) {
		// Error loading sound file
	}

	Sound dead;
	dead.setBuffer(buffer1);

	// Set up metal sound
	SoundBuffer buffer2;
	if (!buffer2.loadFromFile("metal.wav")) {
		// Error loading sound file
	}

	Sound metal;
	metal.setBuffer(buffer2);


	// Set up custom font
	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		cout << "Error loading font!" << endl;
	}

	// Set up sprite vectors
	vector<Sprite> asteroid;
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

		// Spaceship moves left when left key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			spr_spaceship.setPosition(spr_spaceship.getPosition().x - 4, spr_spaceship.getPosition().y);
		}

		// Spaceship moves right when right key
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			spr_spaceship.setPosition(spr_spaceship.getPosition().x + 4, spr_spaceship.getPosition().y);
		}

		// Spaceship moves up when up key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			spr_spaceship.move(0.0f, -4.0f);
		}

		// Spaceship moves down when down key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			spr_spaceship.move(0.0f, 4.0f);
		}

		// Used to detect the width and height of the spaceship
		sf::Vector2f spaceshipPos = spr_spaceship.getPosition();
		const float spaceshipWidth = spr_spaceship.getGlobalBounds().width;
		const float spaceshipHeight = spr_spaceship.getGlobalBounds().height;

		// Check if the spaceship is outside the left side of the screen
		if (spaceshipPos.x < 0) {
			spr_spaceship.setPosition(0, spaceshipPos.y);
		}

		// Check if the spaceship is outside the right side of the screen
		if (spaceshipPos.x + spaceshipWidth > winWidth) {
			spr_spaceship.setPosition(winWidth - spaceshipWidth, spr_spaceship.getPosition().y);
		}

		// Check if the spaceship is outside the top side of the screen
		if (spaceshipPos.y < 0) {
			spr_spaceship.setPosition(spaceshipPos.x, 0);
		}

		// Check if the spaceship is outside the bottom side of the screen
		if (spaceshipPos.y + spaceshipHeight > winHeight) {
			spr_spaceship.setPosition(spr_spaceship.getPosition().x, winHeight - spaceshipHeight);
		}

		// clear the window with black color
		window.clear(Color::Black);

		// Draw everything here...
		window.draw(spr_background);
		window.draw(spr_spaceship);

		// Set the min and max
		float min = 10;
		float max = 25;

		// Adds a new element at the end of the vector, after its current last element
		asteroid.push_back(Sprite(spr_asteroid));

		// Used to generate random numbers between 0.1 and 0.3
		float size = 0.1 + (rand() / (float)RAND_MAX) * 0.2;

		// Sets the next asteroids in the vectors radius to less than 6
		asteroid.back().setScale(size, size);

		// Set lastBullet to -1
		int lastBullet = -1;

		// Adds a new element at the end of the vector, after its current last element
		bullets.push_back(Sprite(spr_bullet));

		// Allows asteroids to constantly fall
		for (size_t i = 0; i < asteroid.size(); i++)
		{
			// set removed to 0
			size_t removed = 0;

			// A while loop to remove asteroids to prevent them from all coming down at once
			while (asteroid.size() - removed > 75)
			{
				// Remove a quarter of the asteroids from the vector
				asteroid.erase(asteroid.begin() + asteroid.size() / 4, asteroid.end());
				removed += asteroid.size() / 4;
			}

			// Allows the asteroids to have the swaying motion 
			asteroid[i].rotate(rand() % 3);

			// Sets the position of the next asteroids randomly across the top of the screen
			asteroid.back().setPosition(rand() % winWidth, -200);

			// Allows the asteroids to move down
			asteroid[i].move(0, 1);

			// If asteroids exit the bottom of the screen, remove them
			if (asteroid[i].getPosition().y > winHeight + 50) {

				// Remove the asteroid from the vector
				asteroid.erase(asteroid.begin() + i);
			}

			// Draws the asteroids according to the positon of i
			window.draw(asteroid[i]);

			// Allows bullets to constantly shoot
			for (size_t j = lastBullet + 1; j < bullets.size(); j++)
			{
				// Sets the position of the next bullets to shoot from the ship
				bullets.back().setPosition(spr_spaceship.getPosition().x + 43, spr_spaceship.getPosition().y);

				// Draws the bullets according to j and allows the bullets to move
				window.draw(bullets[j]);
				bullets[j].move(0, -4);

				// If a bullet collides with an asteroid
				if (Collision::PixelPerfectTest(bullets[j], asteroid[i])) {

					// Add a new scrap metal sprite to the vector
					scrapMetal.push_back(Sprite(spr_scrapMetal));

					// Set the position of the scrap metal sprite to the position of the destroyed asteroid
					scrapMetal.back().setPosition(asteroid[i].getPosition());

					// Play the explosion sound
					explosionSound.play();

					// Erase an asteroid once destroyed and decrement
					asteroid.erase(asteroid.begin() + i);
					j--;
				}

				// Remove bullets if they exit the screen (prevents lag)
				bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
					[&](const sf::Sprite& spr_bullet)
					{
						sf::Vector2u screenSize = window.getSize();
						sf::Vector2f spritePosition = spr_bullet.getPosition();
						return spritePosition.x > screenSize.x || spritePosition.y > screenSize.y ||
							spritePosition.x < 0 || spritePosition.y < 0;
					}), bullets.end());

				// If spaceship collides with an asteroid
				if (Collision::PixelPerfectTest(spr_spaceship, asteroid[i])) {

					dead.play();

					// Displays game over screen
					displayGameOverScreen(window);
				}
			}
		}

		// Update the index of the last bullet added to the game
		lastBullet = bullets.size() - 1;

		// Creates pieces of scrap metal
		for (int i = 0; i < scrapMetal.size(); i++) {

			// Move the scrap metal downwards and draws it
			scrapMetal[i].move(0, 2);
			window.draw(scrapMetal[i]);

			// Check for a collision between the spaceship and the scrap metal
			if (Collision::PixelPerfectTest(spr_spaceship, scrapMetal[i])) {

				// Increment the score
				score++;

				metal.play();

				// Remove the scrap metal from the game and decrement
				scrapMetal.erase(scrapMetal.begin() + i);
				i--;
			}
		}

		// If the score reaches 50, Display the Win screen
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
}

int main()
{
	Asteroids();
	
	return 0;
}