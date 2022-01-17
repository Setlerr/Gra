#include "game.hpp"
void savetofile(int score)
{
    fstream file;
    file.open("score.txt", ios::out);
    file << score;
    file.close();
}

void Game::update() 
{
    if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) 
    {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        if (!NextMove.empty()) //no turning 180*
        {

            switch (snakeDirection) 
            {
            case Direction::UP:
                if (NextMove.front() != Direction::DOWN) 
                {
                    snakeDirection = NextMove.front();
                }
                break;
            case Direction::DOWN:
                if (NextMove.front() != Direction::UP) 
                {
                    snakeDirection = NextMove.front();
                }
                break;
            case Direction::LEFT:
                if (NextMove.front() != Direction::RIGHT) 
                {
                    snakeDirection = NextMove.front();
                }
                break;
            case Direction::RIGHT:
                if (NextMove.front() != Direction::LEFT) 
                {
                    snakeDirection = NextMove.front();
                }
                break;
            }
            NextMove.pop_front();
        }

        // Score //todo
        score += snake.size() * (applesEatenCountTotal + 1);
        scoreText.setString(to_string(score));
        FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

        // Growing
        if (BodyToAdd) 
        {
            addSnakeBody();
            BodyToAdd--;
        }

        // Update head
        switch (snakeDirection) 
        {
        case Direction::RIGHT:
            snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
            break;
        case Direction::DOWN:
            snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
            break;
        case Direction::LEFT:
            snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
            break;
        case Direction::UP:
            snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
            break;
        }

        // Update the snake tail positions
        for (int s = 1; s < snake.size(); s++) 
        {
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // update snake sections
        for (auto& s : snake) 
        {
            s.update();
        }

        // Collision detection - Apple
        if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())) 
        {
            // If apple scored, increase speed and move the apple
            applesEatenCount += 1;
            applesEatenCountTotal += 1;
            applesText.setString("apples " + to_string(applesEatenCountTotal));
            FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
            applesText.setPosition(
                Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

            bool beginningNewLevel = false;
            if (applesEatenCount >= 8) 
            {
                // Begin the next if exist
                if (currentLevel < maxLevels) 
                {
                    beginningNewLevel = true;
                    beginNextLevel();
                }
            }
            if (!beginningNewLevel) 
            {
                BodyToAdd += 4;
                speed++;
                moveApple();
            }
        }

        // Collision to body
        for (int s = 1; s < snake.size(); s++) 
        {
            if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds()))
            {
                currentState = GameState::GAMEOVER;
                savetofile(applesEatenCountTotal);
            }
        }

        // Collision to Wall
        for (auto& w : wallSections) 
        {
            if (snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())) 
            {
                currentState = GameState::GAMEOVER;
                savetofile(applesEatenCountTotal);

            }
        }
        timeSinceLastMove = Time::Zero;
    } 
}

