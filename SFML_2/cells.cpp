#include <iostream>  
#include <SFML/Graphics.hpp> 

void randomiseCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells)
{
    for (int row = 0; row < num_xCells; ++row)
    {
        for (int col = 0; col < num_xCells; ++col)
        {
            cells[row][col] = rand() % 2;
        }
    }
};

void drawCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells, sf::RectangleShape _pixel, sf::RenderWindow& _window)
{
    for (int row = 0; row < num_xCells; ++row)
    {
        for (int col = 0; col < num_yCells; ++col)
        {
            if (cells[row][col] == 1)
            {
                _pixel.setPosition(col * _pixel.getSize().x, row * _pixel.getSize().y);
                _window.draw(_pixel);
            }
        }
    }
}