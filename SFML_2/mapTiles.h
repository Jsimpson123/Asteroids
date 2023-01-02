#pragma once
#include <vector>
#include <SFML/Graphics.hpp>																	// sf namespace 
class mapTiles
{
private:
	std::vector<sf::RectangleShape> points;
	std::vector<std::vector<std::string> > cords;
	int pointsGap = 2;																			// Horizontal gap between plotted points
public:
	mapTiles();
	mapTiles(sf::RectangleShape _shape);

	void loadPoints(std::string _fileName, sf::RenderWindow& _win);
	void addPoint(sf::Color clr, sf::Vector2u origin, sf::Vector2f position);
	void setPointColor(int index, sf::Color _color);
	void clearPointList();
	void drawPoints(sf::RenderWindow &_win);
};

