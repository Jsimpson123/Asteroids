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


int main()
{   

    // Create the window
    RenderWindow window(VideoMode(winWidth, winHeight), "Asteroids!");
    
    // Set the framerate limit to 60 FPS
    window.setFramerateLimit(60);
    
    // Texture set up
    Texture tex_background, tex_spaceship, tex_asteroid;    
    tex_background.loadFromFile("winter_night.jpg");
    tex_spaceship.loadFromFile("spaceship.png");
    tex_asteroid.loadFromFile("asteroid.png");


    // Set up each sprite (Position, scale etc.)
    Sprite spr_background, spr_spaceship, spr_asteroid;
    
    spr_background.setTexture(tex_background);
    
    spr_spaceship.setTexture(tex_spaceship);
    spr_spaceship.scale(Vector2f(0.15f, 0.15f));
    spr_spaceship.setPosition(Vector2f(winWidth/3, winHeight/1.5)); // absolute position

    spr_asteroid.setTexture(tex_asteroid);
    spr_asteroid.scale(Vector2f(0.15f, 0.15f));
    spr_asteroid.setPosition(Vector2f(winWidth / 2, winHeight / 2));

 

    // Set up CircleShape vector

    vector<Sprite> octagon;
    vector<CircleShape> bullets;
   
    // Measures time
    Clock clock;

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
            spr_spaceship.setScale(0.15f, 0.15f);
            //spr_spaceship.move(-4.0f, 0.0f);
            spr_spaceship.setPosition(spr_spaceship.getPosition().x - 4, spr_spaceship.getPosition().y);
        }

        // spaceship moves right when right key is pressed and is set to a certain scale
         if (Keyboard::isKeyPressed(Keyboard::Right)) 
        {
            spr_spaceship.setScale(-0.15f, 0.15f);
            //spr_spaceship.move(4.0f, 0.0f);
            spr_spaceship.setPosition(spr_spaceship.getPosition().x + 4, spr_spaceship.getPosition().y);
        }

        // spaceship moves up when up key is pressed and is set to a certain scale
         if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            spr_spaceship.setScale(-0.15f, 0.15f);
            spr_spaceship.move(0.0f, -4.0f);
        }

        // spaceship moves down when down key is pressed and is set to a certain scale
         if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            spr_spaceship.setScale(-0.15f, 0.15f);
            spr_spaceship.move(0.0f, 4.0f);
        }

        /* if (1 == Keyboard::isKeyPressed(Keyboard::Space)) {

             for (int i = 0; i < bullets.size(); i++) {


                 bullets.push_back((CircleShape{ static_cast<short>(10) , winHeight - 2 * 10 }));

                 bullets.back().setPosition(rand() % winWidth, 50);

                 // Allows the bullets to move up
                 bullets[i].move(0, -1);

                 window.draw(bullets[i]);
             }
         } */

        // clear the window with black color
        window.clear(Color::Black);

        // Draw everything here...
        window.draw(spr_background);
        window.draw(spr_spaceship);
        //window.draw(spr_asteroid);


            float min = 10;
            float max = 25;
            // Constantly generates random numbers under 6 and sets snowSway to this, allowing the swaying motion
            float snowSway = min + (rand() * (int)(max - min) / RAND_MAX);

            // Adds a new element at the end of the vector, after its current last element
            octagon.push_back(Sprite(spr_asteroid));

            // Sets the next octagons in the vectors radius to less than 6
           // octagon.back();



            // Allows octagons to constantly fall
            for (int i = 0; i < octagon.size(); i++)
            {
                // Allows the octagons to have the swaying motion 
                octagon[i].rotate(rand() % 3);

                // Makes sway smoother
                snowSway *= -1;

                // Sets the position of the next octagons randomly across the top of the screen
                octagon.back().setPosition(rand() % winWidth, -50);

                // Allows the octagons to move down
                octagon[i].move(0, 1);

                // Draws the octagons according to the positon of i

                if (i % 100 == 0) {
                    window.draw(octagon[i]);

                }
                /*  if (Collision::PixelPerfectTest(spr_spaceship, octagon[i])) {

                      cout << "Collision" << endl;
                      spr_spaceship.setColor(Color::Transparent);

                  }
                  else {
                      cout << "None" << endl;
                  } */

                if (spr_spaceship.getGlobalBounds().intersects(octagon[i].getGlobalBounds())) {
                    //spr_spaceship.setColor(Color::Transparent);
                    cout << "Collision" << endl;
                }
            }


            float bulletSize = 6;

            bullets.push_back(CircleShape());

            // Sets the next bullets in the vectors radius 6
            bullets.back().setRadius(bulletSize);

            int i = 0;

            // Allows bullets to constantly shoot
            for (i; i < bullets.size(); i++)
            {
                if (i % 100 == 0) {
                    // Sets the position of the next bullets to shoot from the ship
                    bullets.back().setPosition(spr_spaceship.getPosition().x, spr_spaceship.getPosition().y);

                    // Allows the bullets to move down

                    bullets[i].setFillColor(sf::Color(0, 255, 0));

                    window.draw(bullets[i]);
                    bullets[i].move(0, -5);


                }

            }
        

   
        // end the current frame
        window.display();

        elapsedTime = clock.getElapsedTime();
    }
    return 0;
}
    