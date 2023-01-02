#include <iostream>  
#include <SFML/Graphics.hpp> 

void randomiseCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells, int randNum)
{
    for (int row = 0; row < num_xCells; ++row)
    {
        for (int col = 0; col < num_xCells; ++col)
        {
            if (rand() % randNum == 0) cells[row][col] = 1;
            else cells[row][col] = 0;
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

void updateCells(int num_xCells, int num_yCells, std::vector< std::vector<int> >& cells)
{
    int neighbourHoodSize = 2;
    for (int row = 0; row < num_xCells; ++row)
    {
        for (int col = 0; col < num_yCells; ++col)
        {
            // count neighnours that are alive (alive = 1)
            int countNeighbours = 0;
            int neighbourHoodSize = 2;
            for (int i = -1; i < neighbourHoodSize; ++i) // rows
                for (int j = -1; j < neighbourHoodSize; ++j) // cols
                {
                        if ((row + i > 0) && (row + i < num_xCells) && (col + j > 0) && (col + j < num_yCells))
                        {
                            if ((i != 0) && (j != 0))  if ((cells[row + i][col + j] == 1)) countNeighbours++;  
                        }       
                }
            if (cells[row][col] == 1) {
                if ((countNeighbours < 2) || (countNeighbours > 3)) cells[row][col] = 0;
            }
            else {
                if (countNeighbours == 3) cells[row][col] = 1;
            }
 
        }
    }
}