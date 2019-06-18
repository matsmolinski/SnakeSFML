#include "MainUtil.h"



bool MainUtil::loadTextures(Texture* snake_tex, Texture* apple_tex) {
	if (!snake_tex[0].loadFromFile("textures/snake_head.jpg"))
		return 1;
	if (!snake_tex[1].loadFromFile("textures/snake_body.jpg"))
		return 1;
	if (!snake_tex[2].loadFromFile("textures/snake_turn_l.jpg"))
		return 1;
	if (!snake_tex[3].loadFromFile("textures/snake_turn_r.jpg"))
		return 1;
	if (!snake_tex[4].loadFromFile("textures/snake_tail.jpg"))
		return 1;
	if (!apple_tex->loadFromFile("textures/apple.jpg"))
		return 1;
	return 0;
}


std::string MainUtil::getTime(float currentTime) {
	std::string miliseconds(std::to_string(currentTime));
	std::string answer = "";
	int i;
	for (i = 0; i < miliseconds.length(); i++) {
		if (miliseconds[i] == '.') break;
		answer += miliseconds[i];
	}
	answer = answer + '.' + miliseconds[i + 1];
	return answer;
}


bool MainUtil::moveHead(Direction dir, Sprite* head, bool* isAppleEaten, Sprite* apple, Vector2f* headPosition, GameContainer* gc) {

	if (dir == RIGHT) {
		if (head->getPosition().x + 40 <= 580 && !gc->isTaken(head->getPosition().x + 40, head->getPosition().y)) {
			if (head->getPosition().x + 40 == apple->getPosition().x && head->getPosition().y == apple->getPosition().y)
				*isAppleEaten = true;
			head->move(40, 0);
			*headPosition = head->getPosition();
			return true;
		}
	}
	else if (dir == LEFT) {
		if (head->getPosition().x - 40 >= 0 && !gc->isTaken(head->getPosition().x - 40, head->getPosition().y)) {
			if (head->getPosition().x - 40 == apple->getPosition().x && head->getPosition().y == apple->getPosition().y)
				*isAppleEaten = true;
			head->move(-40, 0);
			*headPosition = head->getPosition();
			return true;

		}
	}
	else if (dir == UP) {
		if (head->getPosition().y - 40 >= 0 && !gc->isTaken(head->getPosition().x, head->getPosition().y - 40)) {
			if (head->getPosition().x == apple->getPosition().x && head->getPosition().y - 40 == apple->getPosition().y)
				*isAppleEaten = true;
			head->move(0, -40);
			*headPosition = head->getPosition();
			return true;
		}
	}
	else if (dir == DOWN)
		if(head->getPosition().y + 40 <= 580 && !gc->isTaken(head->getPosition().x, head->getPosition().y + 40)) {
			if(head->getPosition().x == apple->getPosition().x && head->getPosition().y + 40 == apple->getPosition().y)
				*isAppleEaten = true;
			head->move(0, 40);
			*headPosition = head->getPosition();
			return true;
		}
	return false;
}

Sprite MainUtil::createNeck(Direction change, Direction oldDirection, Direction newDirection, Texture* snake_tex, Vector2f headPos) {
	
	Sprite neck;
	if (oldDirection == newDirection) {
		neck.setTexture(snake_tex[1]);
	}
	else {
		if (change == LEFT)
			neck.setTexture(snake_tex[2]);
		else neck.setTexture(snake_tex[3]);
	}
	neck.setOrigin(20, 20);
	neck.setPosition(headPos);
	if (oldDirection == DOWN)
		neck.rotate(180);
	else if (oldDirection == LEFT)
		neck.rotate(-90);
	else if (oldDirection == RIGHT)
		neck.rotate(90);
	return neck;
}




bool MainUtil::moveSnake(Direction change, Direction oldDirection, Direction newDirection, GameContainer* gc, Texture* snake_tex, Texture* apple_tex, Sound* appl) {

	bool isAppleEaten = false;
	Sprite *head = &gc->snake[gc->snakeLength - 1];
	Vector2f* headPosition = &gc->taken_squares[gc->snakeLength - 1]; //position in vector
	Vector2f headPos = head->getPosition();//temporary position for creating neck
	
	if (moveHead(newDirection, head, &isAppleEaten, &gc->apple, headPosition, gc)) {

		if (oldDirection != newDirection)
			if (change == LEFT) head->rotate(-90);
			else head->rotate(90);
		Sprite neck = createNeck(change, oldDirection, newDirection, snake_tex, headPos);
		gc->snake.insert(gc->snake.end() - 1, neck);
		gc->taken_squares.insert(gc->taken_squares.end() -1, headPos);
		if (isAppleEaten) {
			gc->snakeLength++;
			reallocateApple(gc);
			appl->play();
			return true;
		}
		gc->snake[1].setTexture(snake_tex[4]);
		adjustTail(&gc->snake[1], &gc->snake[2]);
		gc->snake.erase(gc->snake.begin());
		gc->taken_squares.erase(gc->taken_squares.begin());
		return true;
	}
	return false;
}

void MainUtil::adjustTail(Sprite* newTail, Sprite* nextElement) {
	if (newTail->getPosition().y + 40 == nextElement->getPosition().y)
		newTail->setRotation(180);
	else if (newTail->getPosition().x + 40 == nextElement->getPosition().x)
		newTail->setRotation(90);
	else if (newTail->getPosition().x - 40 == nextElement->getPosition().x)
		newTail->setRotation(270);
	else if (newTail->getPosition().y - 40 == nextElement->getPosition().y)
		newTail->setRotation(0);
}

void MainUtil::reallocateApple(GameContainer* gc) {
	int randomX;
	int randomY;
	if (gc->snakeLength < 200) {
		do {
			randomX = ((std::rand() % 15) * 40) + 20;
			randomY = ((std::rand() % 15) * 40) + 20;
		} while (gc->isTaken(randomX, randomY));
		gc->apple.setPosition(randomX, randomY);
	}
	else gc->apple.setPosition(gc->findFreeSpace());
}