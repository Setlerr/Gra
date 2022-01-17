#include "game.hpp"

void Game::draw() 
{
  window.clear(Color::Blue);

  // walls
  for (auto & w : wallSections) 
  {
    window.draw(w.getShape());
  }

  // apple
  window.draw(apple.getSprite());

  // snake
  for (auto & s : snake) 
  {
    window.draw(s.getShape());
  }

  // text
  window.draw(titleText);
  window.draw(currentLevelText);
  window.draw(applesText);
  window.draw(scoreText);

  // gamemover
  if (currentState == GameState::GAMEOVER) 
  {
    window.draw(gameOverText);
    window.draw(pressEnterText);
  }

  window.display();
}
