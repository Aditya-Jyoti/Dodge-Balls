#ifndef DODGE_BALLS_H
#define DODGE_BALLS_H

#include <iostream>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    sf::RenderWindow *window;
    sf::Event event;

    sf::CircleShape enemy;
    std::vector<sf::CircleShape> enemyArray;
    std::vector<sf::Vector2f> direcArray;
    sf::CircleShape player;

    sf::Vector2i mousePosWin;
    sf::Vector2f mousePosView;

    float spawnTimer;
    float maxSpawnTimer;
    float points;
    int maxEnemies;

    std::random_device dev;
    std::default_random_engine gen{dev()};

    void initWindow();
    void initVariables();
    void initEnemy();
    void initPlayer();

    sf::Vector2i genRandomNum(sf::Vector2f playerPos);
    sf::Vector2f normalize(sf::Vector2f position);

public:
    Game();
    virtual ~Game();
    bool isWinOpen;

    void spawnEnemies();
    void updateEnemies();
    void renderEnemies();

    void updatePlayer();
    void renderPlayer();

    void updateEvents();
    void updateMousePosition();

    void render();
    void update();
};

#endif