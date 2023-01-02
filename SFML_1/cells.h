#pragma once
#include <iostream>                                                     
#include <SFML/Graphics.hpp> 

void randomiseCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells, int randNum);
void drawCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells, sf::RectangleShape _pixel, sf::RenderWindow& _window);
void updateCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells);