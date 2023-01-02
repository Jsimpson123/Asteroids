/*
* An SFML application using a vector list to store point data - Darryl Charles
* SFML Documentation https://www.sfml-dev.org/documentation/2.5.1/
* Set up your own VS2019 project https://www.youtube.com/watch?v=lFzpkvrscs4
*/

#include <iostream>  
#include <fstream>
#include <sstream>
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
    sf::RectangleShape pixel(sf::Vector2f(16.0f, 16.0f));
    pixel.setFillColor(sf::Color::Green);
    int num_xCells = int(winWidth / pixel.getSize().x);                         // Get pixel width and height of the 2d grid (based on pixel size)
    int num_yCells = int(winHeight / pixel.getSize().y);
#pragma endregion

#pragma region ~ Create 2d vector array for holding pixel values (integers) ~
    std::vector<std::vector<int>> cellsGrid2D;                                  // Vector list of map tiles  

#pragma endregion

#pragma region ~ Load map from file ~
    std::ifstream dataStream;
    std::string line;

    dataStream.open(".\\map.csv");
    if (dataStream.is_open())
    {
        while (std::getline(dataStream, line))
        {
            std::stringstream lineStream(line);
            std::string character;
            std::vector<int> parsedRow;
            while (std::getline(lineStream, character, ','))
            {
                parsedRow.push_back(std::stoi(character));
                std::cout << std::stoi(character);
            }
            std::cout << std::endl;
            cellsGrid2D.push_back(parsedRow);
        }
    }
#pragma endregion  

    while (window.isOpen())                                                    
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

        drawCells(num_xCells, num_yCells, cellsGrid2D, pixel, window);          
                                                               
        window.display();                                               
    }

    return 0;
}

