#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "gamelogic.h"

extern float tileSize;
extern bool isPlaying;
extern int maxFPS;
extern int snakeLength;
extern int highScoreNum;
extern int recordScoreNum;

extern std::string fontFileLocation;
extern std::string lengthText;
extern std::string highScoreText;
extern std::string recordScoreText;

extern std::vector<sf::Vector2f> snakeTail;

extern sf::Vector2f velocity;

extern sf::RectangleShape snake;
extern sf::RectangleShape food;
extern sf::RectangleShape snakeBody;
extern sf::RenderWindow window;

extern sf::Font berlinSans;
extern sf::Text lengthScore;
extern sf::Text highScore;
extern sf::Text recordScore;

void StartGame();
void GameOver();
float RandomX();
float RandomY();
int RandomNumber(int minNum, int maxNum);

#endif // SNAKE_H_INCLUDED
