/*
* An SFML application using a vector list to store point data - Darryl Charles
* SFML Documentation https://www.sfml-dev.org/documentation/2.5.1/
* Set up your own VS2019 project https://www.youtube.com/watch?v=lFzpkvrscs4
*/

#include <iostream>                                                     
#include <SFML/Graphics.hpp> 
#include "cells.h"
// define render window size constants
#define winWidth 800
#define winHeight 800

int main()
{
#pragma region ~ Initialise render window ~
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Assignment 2");                            
    // pixel.setOrigin(pixel.getSize().x/2, pixel.getSize().y/2);
#pragma endregion

#pragma region ~ Create a square pixel (SFML graphics object), size it, and give it a color ~
    sf::RectangleShape pixel(sf::Vector2f(4.0f, 4.0f));
    pixel.setFillColor(sf::Color::White);
    int num_xCells = int(winWidth / pixel.getSize().x);                         // get pixel width and height of the 2d grid (based on pixel size)
    int num_yCells = int(winHeight / pixel.getSize().y);
#pragma endregion

#pragma region ~ Create 2d vector array for holding pixel values (integers) ~
    std::vector<std::vector<int>> cellsGrid2D;                                  // vector list of co-ordinates  
    int default_value = 0;
    cellsGrid2D.resize(num_xCells, std::vector<int>(num_yCells, default_value));
#pragma endregion

#pragma region ~ Randomise the seed for the random number generator so the numbers are different every time ~
    srand(time(NULL));
    randomiseCells(num_xCells, num_yCells, cellsGrid2D, 2);                        // defined in cells.cpp and cells.h - randomises 2d vector array with 1 and 0s
#pragma endregion
    sf::Clock clock;
    sf::Time elapsedTime;
    while (window.isOpen())                                                     // This is the Windows application loop - infinite loop until closed
    {
#pragma region ~ Check for a close window event ~
        sf::Event event;                                                // Windows is event driven - this code closes the Window properly
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
#pragma endregion

        window.clear();                                                 

        // For every row (num_xCells) and column (num_yCells) in our grid (cellsGrid2D) draw a pixel. 
        // Defined in cells.cpp and cells.h. cellsGrid2D is a reference to our 2d array/vector. 
        drawCells(num_xCells, num_yCells, cellsGrid2D, pixel, window); 
        elapsedTime = clock.getElapsedTime();
        if (elapsedTime.asMilliseconds() % 5 == 0) updateCells(num_xCells, num_yCells, cellsGrid2D);

        // std::cout << elapsedTime.asMilliseconds() << std::endl;
        window.display();                                               
    }

    return 0;
}

