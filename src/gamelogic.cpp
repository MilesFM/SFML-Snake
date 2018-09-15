#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "gamelogic.h"

static bool newFood = false; // Prevents tail from shifting if food has been eaten that frame

bool CheckFoodPostion(sf::Vector2f snakePos) // Makes sure that the food positon does not end up where the snake or tail is
{
    sf::Vector2f foodPos = food.getPosition();
    if (snakePos.x == foodPos.x && snakePos.y == foodPos.y)
    {
        return true;
    }
    for (int i = 0; i < snakeLength-1; ++i)
    {
        if (snakeTail[i].x == foodPos.x && snakeTail[i].y == foodPos.y)
        {
            return true;
        }
    }
    return false;
}

void FoodLogic()
{
    sf::Vector2f snakePos = snake.getPosition();
    sf::Vector2f foodPos = food.getPosition();
    if (snakePos.x == foodPos.x && snakePos.y == foodPos.y)
    {
        do
        {
            food.setPosition(RandomX(), RandomY()); // New random positon
        }
        while (CheckFoodPostion(snakePos));


        sf::Vector2f segment(snakePos.x, snakePos.y);
        auto beginning = snakeTail.begin();
        snakeTail.insert(beginning, segment);
        ++snakeLength;
        newFood = true;
    }
}

void SnakeLogic()
{
    sf::Vector2f snakePos = snake.getPosition();

    if (!newFood)
    {
        sf::Vector2f segment(snakePos.x, snakePos.y);
        auto beginning = snakeTail.begin();
        snakeTail.insert(beginning, segment);
        snakeTail.pop_back();
    }
    else
    {
        newFood = false;
    }

    snake.move(velocity); // Moves the snake by the snake velocity
    snakePos = snake.getPosition();

    bool bitingTail = false; // If the snake runs into itself
    for (int i = 0; i < snakeLength-1; ++i)
    {
        if (snakePos.x == snakeTail[i].x && snakePos.y == snakeTail[i].y)
        {
            bitingTail = true;
        }
    }

    // If snake is out of bounds
    if (snakePos.x < 0 || snakePos.x > window.getSize().x ||
        snakePos.y < 0 || snakePos.y > window.getSize().y ||
        bitingTail)
    {
        GameOver();
    }
}
