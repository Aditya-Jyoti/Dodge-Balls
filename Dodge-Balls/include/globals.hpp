#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

const float PLAYER_SIZE = 15.f;
const float ENEMY_SIZE = 15.f;
const float ENEMY_SPEED = 5.f;
const float PLAYER_SPEED = 7.f;
const float MAX_ENEMIES = 15;
const float MAX_SPAWN_TIMER = 12.f;

const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;

const int WIDTH = (WINDOW_WIDTH / 2) - 160;
const int HEIGHT = (WINDOW_HEIGHT / 2) + 260;

const int START_X = WINDOW_WIDTH / 2 - 700;
const int START_Y = WINDOW_HEIGHT / 2 - 400;

#endif