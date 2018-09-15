#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "snake.h"
#include "gamelogic.h"
#include "datamanager.h"

bool directionChangedThisFrame = false;

void GetKeyInput(int keyCode)
{
    /*
    x has to equal zero to change left or right and
    y has to equal zero to change up or down,
    to prevent the player from reversing the snake
    and causing the snake to die
    */
    if (!directionChangedThisFrame)
    {
        if (keyCode == sf::Keyboard::Left && velocity.x == 0)
        {
            velocity.x = -tileSize;
            velocity.y = 0;
        }
        else if (keyCode == sf::Keyboard::Right && velocity.x == 0)
        {
            velocity.x = tileSize;
            velocity.y = 0;
        }
        else if (keyCode == sf::Keyboard::Up && velocity.y == 0)
        {
            velocity.y = -tileSize;
            velocity.x = 0;
        }
        else if (keyCode == sf::Keyboard::Down && velocity.y == 0)
        {
            velocity.y = tileSize;
            velocity.x = 0;
        }
        directionChangedThisFrame = true;
    }
}

// Every frame, this is run
void RenderLoop()
{
    FoodLogic();
    SnakeLogic();

    window.draw(snake);
    window.draw(food);

    /*
    SnakeLength is used instead of getting the length of the vector
    to avoid running the for loop when the snake has no tail
    */
    for (int i = 0; i < snakeLength-1; ++i)
    {
        snakeBody.setPosition(snakeTail[i].x, snakeTail[i].y); // Sets the tail to draw
        //std::cout << "Position in array: " << i << " X: " << snakeTail[i].x << " Y: " << snakeTail[i].y << std::endl;
        window.draw(snakeBody);
    }

    lengthScore.setString(lengthText + std::to_string(snakeLength));
    highScore.setString(highScoreText + std::to_string(highScoreNum));
    recordScore.setString(recordScoreText + std::to_string(recordScoreNum));


    if (highScoreNum < snakeLength)
    {
        highScoreNum = snakeLength;
    }

    if (recordScoreNum < snakeLength)
    {
        recordScoreNum = snakeLength;
    }

    directionChangedThisFrame = false;

    window.draw(lengthScore);
    window.draw(highScore);
    window.draw(recordScore);
}

void SetupText()
{
    if (!berlinSans.loadFromFile(fontFileLocation))
    {
        exit(1);
    }

    int textSize = 18;

    lengthScore.setFont(berlinSans);
    lengthScore.setString(lengthText + std::to_string(snakeLength));
    lengthScore.setCharacterSize(textSize);
    lengthScore.setFillColor(sf::Color::White);
    lengthScore.setPosition(0, 0);

    CreateDataFile();
    try
    {
        highScoreNum = std::stoi(GetHighScore());
    }
    catch (int e)
    {
        recordScoreNum = 0;
    }
    highScore.setFont(berlinSans);
    highScore.setString(highScoreText + std::to_string(highScoreNum));
    highScore.setCharacterSize(textSize);
    highScore.setFillColor(sf::Color::White);
    sf::FloatRect highScoreRect = highScore.getLocalBounds();
    highScore.setOrigin(0, highScoreRect.top + highScoreRect.height); // Changes origin to right corner
    highScore.setPosition(0, window.getSize().y);

    try
    {
        recordScoreNum = std::stoi(GetRecordScore());
    }
    catch (int e)
    {
        recordScoreNum = 0;
    }

    recordScore.setFont(berlinSans);
    recordScore.setString(recordScoreText + std::to_string(recordScoreNum));
    recordScore.setCharacterSize(textSize);
    recordScore.setFillColor(sf::Color::White);
    sf::FloatRect recordScoreRect = recordScore.getLocalBounds();
    recordScore.setOrigin(0, recordScoreRect.top + recordScoreRect.height); // Changes origin to right corner
    recordScore.setPosition(0, window.getSize().y-textSize);
}

void Setup()
{
    srand(time(NULL)); // Sets seed for random numbers
    window.setFramerateLimit(maxFPS);

    snake.setFillColor(sf::Color::Green);
    snake.setOutlineThickness(2); // Padding around the body
    snake.setOutlineColor(sf::Color::Black);

    snakeBody.setFillColor(sf::Color::Green);
    snakeBody.setOutlineThickness(2); // Padding around the body
    snakeBody.setOutlineColor(sf::Color::Black);

    food.setFillColor(sf::Color::Red);

    snake.setPosition(RandomX(), RandomY()); // New random positon
    food.setPosition(RandomX(), RandomY()); // Sets postion out of bounds

    SetupText();
}

int main()
{
    Setup();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Keyboard event manager
            if (event.type == sf::Event::KeyPressed)
                GetKeyInput(event.key.code);

        }

        window.clear();
        RenderLoop();
        window.display();
    }

    return 0;
}
