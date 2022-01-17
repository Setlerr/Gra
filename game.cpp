#include "game.hpp"
#include "menu.hpp"


const sf::Time Game::TimePerFrame = seconds(1.f / 60.f);

Game::Game() 
{
    resolution = Vector2f(800, 600);
    window.create(VideoMode(resolution.x, resolution.y), "SNAKE", Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();

    mainFont.loadFromFile("arcade.ttf");
    setupText(&titleText, mainFont, "SNAKE", 28, Color::Blue);
    FloatRect titleTextBounds = titleText.getLocalBounds();
    titleText.setPosition(Vector2f(resolution.x / 2 - titleTextBounds.width / 2, -9));
    //
    setupText(&currentLevelText, mainFont, "level 1", 28, Color::Blue);
    currentLevelText.setPosition(Vector2f(15, -9));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    //
    setupText(&applesText, mainFont, "Apples 0", 28, Color::Blue);
    applesText.setPosition(
    Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
    //
    setupText(&scoreText, mainFont, to_string(score), 28, Color::Blue);
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));
    //
    setupText(&gameOverText, mainFont, "YOU LOST", 72, Color::Blue);
    FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition(Vector2f(resolution.x / 2 - gameOverTextBounds.width / 2, 100));
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);
    //
    setupText(&pressEnterText, mainFont, "Press ENTER to restart", 38, Color::Red);
    FloatRect pressEnterTextBounds = pressEnterText.getLocalBounds();
    pressEnterText.setPosition(Vector2f(resolution.x / 2 - pressEnterTextBounds.width / 2, 200));
    pressEnterText.setOutlineColor(Color::Black);
    pressEnterText.setOutlineThickness(2);
    startTheGame();
    currentState = GameState::RUNNING;
    lastState = currentState;
}

void Game::startTheGame() 
{
    score = 0;
    speed = 2;
    snakeDirection = Direction::RIGHT;
    BodyToAdd = 0;
    timeSinceLastMove = Time::Zero;
    wallSections.clear();
    NextMove.clear();
    applesEatenCount = 0;
    applesEatenCountTotal = 0;
    currentLevel = 1;
    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentState = GameState::RUNNING;
    lastState = currentState;
    currentLevelText.setString("level " + to_string(currentLevel));
    applesText.setString("apples " + to_string(applesEatenCountTotal));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
    scoreText.setString(to_string(score));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));
}

 //level

void Game::beginNextLevel() 
{
    currentLevel += 1;
    wallSections.clear();
    NextMove.clear();
    speed = 2 + currentLevel;
    snakeDirection = Direction::RIGHT;
    BodyToAdd = 0;
    applesEatenCount = 0;

    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesText.setPosition(
    Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
}

// Snake at the beginning
void Game::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100, 100));
    snake.emplace_back(Vector2f(80, 100));
    snake.emplace_back(Vector2f(60, 100));
}

void Game::addSnakeBody() 
{
    // Add Body in the same position 
    Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Game::moveApple() 
{
    // Apple placed in a section -2 (walls)
    Vector2f appleResolution = Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
    Vector2f newAppleLocation;
    bool badLocation = false;
    srand(time(nullptr));
    // Loop if wrong location
    do {
        badLocation = false;
        newAppleLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 20;
        newAppleLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 20;
        for (auto& s : snake) 
        {
            if (s.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) 
            {
                badLocation = true;
                break;
            }
        }
        // Check if in the walls
        for (auto& w : wallSections) 
        {
            if (w.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) 
            {
                badLocation = true;
                break;
            }
        }

    } while (badLocation);
    apple.setPosition(newAppleLocation);
}

void Game::Pause() 
{
    if (currentState == GameState::RUNNING) 
    {
        lastState = currentState;
        currentState = GameState::PAUSE;
    }
    else if (currentState == GameState::PAUSE) 
    {
        currentState = lastState;
    }
}

void Game::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) 
{
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(colour);
}

void Game::checkLevelFiles() 
{
    ifstream levelsManifest("maps/levels.txt");
    ifstream testFile;
    for (string manifestLine; getline(levelsManifest, manifestLine);) 
    {
        testFile.open("maps/" + manifestLine);
        if (testFile.is_open()) 
        {
            levels.emplace_back("maps/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}
//Ability to insert own levels through .txt files
void Game::loadLevel(int levelNumber) 
{
    string levelFile = levels[levelNumber - 1];
    ifstream level(levelFile);
    string line;
    if (level.is_open()) 
    {
        for (int y = 0; y < 30; y++) 
        {
            getline(level, line);
            for (int x = 0; x < 40; x++) 
            {
                if (line[x] == 'x') 
                {
                    wallSections.emplace_back(Border(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
                }
            }
        }
    }
    level.close();
}

void Game::run() 
{
    Clock clock;

    while (window.isOpen()) 
    {
        Time deltat = clock.restart();
        


        if (currentState == GameState::PAUSE || currentState == GameState::GAMEOVER) 
        {
            // Wait for input in pause
            input();

            if (currentState == GameState::GAMEOVER) 
            {
                draw();
            }

            sleep(milliseconds(2)); // for CPU optim.
            continue;
        }

        timeSinceLastMove += deltat;

        input();
        update();
        draw();
    }
}