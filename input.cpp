#include "game.hpp"

void Game::input() 
{
    Event event{};

    while (window.pollEvent(event)) 
    {
        if (event.type == Event::Closed) 
        {
            window.close();
        }

        if (event.type == Event::KeyPressed) 
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape)) 
            {
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)) 
            {
                Pause();
            }

            if (currentState == GameState::GAMEOVER) 
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter)) 
                {
                    startTheGame();
                }
            }
        }
    } 
    if (Keyboard::isKeyPressed(Keyboard::Up)) 
    {
        addDirection(Direction::UP);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) 
    {
        addDirection(Direction::DOWN);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) 
    {
        addDirection(Direction::LEFT);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) 
    {
        addDirection(Direction::RIGHT);
    }
}

void Game::addDirection(int newDirection) 
{
    if (NextMove.empty()) 
    {
        NextMove.emplace_back(newDirection);
    }
    else 
    {
        if (NextMove.back() != newDirection) 
        {
            NextMove.emplace_back(newDirection);
        }
    }
}
