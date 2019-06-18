#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameContainer.h"
#include "Direction.h"
using namespace sf;

class MainUtil
{
public:
	static bool loadTextures(Texture* snake_tex, Texture* apple_tex);
	static std::string getTime(float currentTime);
	static bool moveSnake(Direction change, Direction oldDirection, Direction newDirection, GameContainer* gc, Texture* snake_tex, Texture* apple_tex, Sound* appl);
private:
	static bool moveHead(Direction dir, Sprite* head, bool* isAppleEaten, Sprite* apple, Vector2f* headPosition, GameContainer* gc);
	static Sprite createNeck(Direction change, Direction oldDirection, Direction newDirection, Texture* snake_tex, Vector2f headPos);
	static void adjustTail(Sprite* newTail, Sprite* nextElement);
	static void reallocateApple(GameContainer* gc);
};

