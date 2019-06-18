#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameContainer
{
public:
	int snakeLength;
	std::vector <Sprite> snake;
	Sprite apple;
	std::vector <Vector2f> taken_squares; 

	void setStartValues(Texture* snake_tex, Texture* apple_tex);
	bool isTaken(int x, int y);
	Vector2f findFreeSpace();
};