#include <ctime>
#include <cstdlib>

#include "snake.h"
#include "datamanager.h"

float tileSize = 20; // How big each square is
bool isPlaying = false;
int maxFPS = 15;
int snakeLength = 1;
int highScoreNum;
int recordScoreNum;

std::string fontFileLocation = "assets/BRLNSR.TTF";
// Text to be infront of number
std::string lengthText = "Current Length: ";
std::string highScoreText = "Longest length: ";
std::string recordScoreText = "Record length: ";

std::vector<sf::Vector2f> snakeTail; // The position of trailing body of the snake

sf::Vector2f velocity(0, 0);

sf::RectangleShape snake(sf::Vector2f(tileSize, tileSize));
sf::RectangleShape food(sf::Vector2f(tileSize, tileSize));
sf::RectangleShape snakeBody(sf::Vector2f(tileSize, tileSize)); // What is acturly drawm
sf::RenderWindow window(sf::VideoMode(40*tileSize, 30*tileSize), "Snake", sf::Style::Titlebar | sf::Style::Close);

sf::Font berlinSans;
sf::Text lengthScore; // Shows current length
sf::Text highScore;
sf::Text recordScore; // Online highscore

void StartGame()
{
    snake.setPosition(RandomX(), RandomY()); // New random positon
    food.setPosition(RandomX(), RandomY()); // Sets postion out of bounds

    velocity.x = 0;
    velocity.y = 0;

    snakeLength = 1;
    snakeTail.clear();
}

void GameOver()
{
    SetHighScore(snakeLength);
    SetRecordScore(recordScoreNum);
    StartGame();
}

float RandomX()
{
    sf::Vector2u winSize = window.getSize();
    /*
    Gets a random tile, to make sure it is a tile it
    divides winSize by tileSize.
    It then multiples it back to the normal coordinates
    by multipling it by tileSize
    */
    return (float)(RandomNumber(0, (winSize.x/tileSize))*tileSize);
}

float RandomY()
{
    sf::Vector2u winSize = window.getSize();
    /*
    Gets a random tile, to make sure it is a tile it
    divides winSize by tileSize.
    It then multiples it back to the normal coordinates
    by multipling it by tileSize
    */
    return (float)(RandomNumber(0, (winSize.y/tileSize))*tileSize);
}

int RandomNumber(int minNum, int maxNum)
{
    return (rand() % maxNum + minNum);
}
