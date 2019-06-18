#include "GameContainer.h"

bool GameContainer::isTaken(int x, int y) {
	for (int i = 0; i < taken_squares.size(); i++)
		if (taken_squares[i].x == x && taken_squares[i].y == y)
			return true;
	return false;
}

Vector2f GameContainer::findFreeSpace()
{
	int n = (std::rand() % (225 - snakeLength)) + 1;
	int x, y, counter = 0;
	for (x = 20; x <= 580; x = x + 40)
		for (y = 20; y <= 580; y = y + 40) {
			if (!isTaken(x, y)) counter++;
			if (counter == n) {
				goto end;
			}
		}
	end:
	return Vector2f(x, y);
}

void GameContainer::setStartValues(Texture* snake_tex, Texture* apple_tex)
{
	snakeLength = 3;
	Sprite tail, body, head;
	tail.setTexture(snake_tex[4]);
	tail.setOrigin(20, 20);
	tail.setPosition(100,380);
	snake.push_back(tail);
	taken_squares.push_back(Vector2f(100, 380));
	body.setTexture(snake_tex[1]);
	body.setOrigin(20, 20);
	body.setPosition(100, 340);
	snake.push_back(body);
	taken_squares.push_back(Vector2f(100, 340));

	head.setTexture(snake_tex[0]);
	head.setOrigin(20, 20);
	head.setPosition(100, 300);
	snake.push_back(head);
	taken_squares.push_back(Vector2f(100, 300));
	int randomX;
	int randomY;
	do {
		randomX = ((std::rand() % 15) * 40) + 20;
		randomY = ((std::rand() % 15) * 40) + 20;
	} while (isTaken(randomX, randomY));
	apple.setTexture(*apple_tex);
	apple.setOrigin(20, 20);
	apple.setPosition(randomX, randomY);
}

