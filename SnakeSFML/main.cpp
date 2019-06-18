#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "GameContainer.h"
#include "MainUtil.h"
#include "Direction.h"
using namespace sf;



int main()
{
	srand(time(NULL));
	bool isGameOn = true, isGameFirst = true;
	int hiScore = 0, diffLevel = 3, fpsCounter = 0;
	Direction change = UP;
	Direction newDirection = UP;
	Direction oldDirection = UP;
	SoundBuffer applb;
	applb.loadFromFile("appl.wav");
	Sound appl;
	appl.setBuffer(applb);
	RenderWindow mainWindow(VideoMode(800, 600, 32), "Snake ver. 1.0");
	mainWindow.setVerticalSyncEnabled(true);
	Image icon;
	icon.loadFromFile("textures/snake_head.jpg");
	mainWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	GameContainer* gc = new GameContainer();
	Clock timerClock;
	Clock fpsClock;
	Font font;
	Texture snake_tex [5];
	Texture apple_tex;
	Text timer, points, GO, help, hiS, lvl, fps;
	if (MainUtil::loadTextures(snake_tex, &apple_tex))
		return -1;
	if (!font.loadFromFile("font.ttf"))
		return -1;
	timer.setFont(font);
	timer.setCharacterSize(24);
	timer.setFillColor(Color::Red);
	timer.setPosition(601, 10);
	lvl.setFont(font);
	lvl.setCharacterSize(24);
	lvl.setFillColor(Color::Red);
	lvl.setPosition(601, 110);
	lvl.setString("Difficulty\nlevel: 3");
	points.setFont(font);
	points.setCharacterSize(24);
	points.setFillColor(Color::Red);
	points.setPosition(601, 200);
	points.setString("Score:\n0");
	hiS.setFont(font);
	hiS.setCharacterSize(24);
	hiS.setFillColor(Color::Red);
	hiS.setPosition(601, 300);
	GO.setFont(font);
	GO.setCharacterSize(60);
	GO.setFillColor(Color::Red);
	GO.setPosition(200, 200);
	GO.setString("GAME\nOVER");
	help.setFont(font);
	help.setCharacterSize(24);
	help.setFillColor(Color::Red);
	help.setPosition(601, 450);
	help.setString("n - start\nnew game");
	fps.setFont(font);
	fps.setCharacterSize(24);
	fps.setFillColor(Color::Red);
	fps.setPosition(0, 0);
	mainWindow.clear(sf::Color::White);
	gc->setStartValues(snake_tex, &apple_tex);
	Clock gameClock;


	while (mainWindow.isOpen())
	{
		if(isGameOn)
			timer.setString("Timer:\n" + MainUtil::getTime(timerClock.getElapsedTime().asSeconds()));
		if (isGameOn  && gameClock.getElapsedTime().asMilliseconds() >= 100 * (5 - diffLevel ? 5 - diffLevel : 0.5) ) {
			isGameOn = MainUtil::moveSnake(change, oldDirection, newDirection, gc, snake_tex, &apple_tex, &appl);
			points.setString("Points:\n" + std::to_string(gc->snakeLength - 3));
			oldDirection = newDirection;
			gameClock.restart();
		}
		if (fpsClock.getElapsedTime().asSeconds() >= 1) {
			fps.setString("FPS: " + std::to_string(fpsCounter));
			fpsCounter = 0;
			fpsClock.restart();
		}
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				mainWindow.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
				if (oldDirection == UP) {
					newDirection = LEFT;
					change = LEFT;
				}
				else if (oldDirection == DOWN) {
					newDirection = LEFT;
					change = RIGHT;
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				if (oldDirection == UP) {
					newDirection = RIGHT;
					change = RIGHT;
				}
				else if (oldDirection == DOWN) {
					newDirection = RIGHT;
					change = LEFT;
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				if (oldDirection == LEFT) {
					newDirection = DOWN;
					change = LEFT;
				}
				else if (oldDirection == RIGHT) {
					newDirection = DOWN;
					change = RIGHT;
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				if (oldDirection == LEFT) {
					newDirection = UP;
					change = RIGHT;
				}
				else if (oldDirection == RIGHT) {
					newDirection = UP;
					change = LEFT;
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) {
				if (diffLevel < 5) {
					diffLevel++;
					lvl.setString("Difficulty\nlevel: " + std::to_string(diffLevel));
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) {
				if (diffLevel > 1) {
					diffLevel--;
					lvl.setString("Difficulty\nlevel: " + std::to_string(diffLevel));
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
				if (!isGameOn) {
					if(gc->snakeLength - 3 > hiScore)
						hiScore = gc->snakeLength - 3;
					hiS.setString("Highest score:\n" + std::to_string(hiScore));
					gc->snake.clear();
					gc->taken_squares.clear();
					gc->setStartValues(snake_tex, &apple_tex);
					change = UP;
					newDirection = UP;
					oldDirection = UP;
					points.setString("Points:\n0");
					isGameOn = true;
					isGameFirst = false;
					timerClock.restart();
					gameClock.restart();
				}
		}
		mainWindow.clear(sf::Color::White);
		mainWindow.draw(gc->apple);
		for (Sprite s : gc->snake)
			mainWindow.draw(s);
		if (!isGameOn) {
			mainWindow.draw(GO);
			mainWindow.draw(help);
		}
		mainWindow.draw(timer);
		mainWindow.draw(points);
		mainWindow.draw(lvl);
		mainWindow.draw(fps);
		if (!isGameFirst)
			mainWindow.draw(hiS);
		mainWindow.display();
		fpsCounter++;
	}
	delete gc;
	return 0;
}