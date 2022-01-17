#ifndef _GAME_HPP
#define _GAME_HPP

#include "snakebody.hpp"
#include "apple.hpp"
#include "border.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>


using namespace sf;
using namespace std;

class Game 
{
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    vector<SnakeBody> snake;
    int snakeDirection;
    deque<int> NextMove;
    int speed;
    int BodyToAdd;
    int applesEatenCount;
    int applesEatenCountTotal;
    unsigned long long int score;

    Apple apple;

    vector<Border> wallSections;
    int currentLevel;
    int maxLevels;
    vector<String> levels;

    Font mainFont;
    Text titleText;
    Text applesText;
    Text currentLevelText;
    Text scoreText;
    Text gameOverText;
    Text pressEnterText;

    Time timeSinceLastMove;

    int currentState;
    int lastState;
public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { RUNNING, PAUSE, GAMEOVER };
    Game();
    void input();
    void addDirection(int newDirection);
    void update();
    void draw();
    static void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);
    void newSnake();
    void addSnakeBody();
    void moveApple();
    void checkLevelFiles();
    void loadLevel(int levelNumber);
    void beginNextLevel();
    void startTheGame();
    void Pause();
    void run();
    
};


#endif 
