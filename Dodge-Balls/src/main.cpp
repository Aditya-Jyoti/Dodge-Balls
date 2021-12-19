#include <iostream>
#include <cmath>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <dodge-balls.hpp>
#include <globals.hpp>

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
}

void Game::initVariables()
{
	this->window = nullptr;

	this->maxSpawnTimer = MAX_SPAWN_TIMER;
	this->spawnTimer = this->maxSpawnTimer;
	this->points = 0;
	this->maxEnemies = MAX_ENEMIES;
}

void Game::initWindow()
{
	this->isWinOpen = true;
	this->window = new sf::RenderWindow(
		sf::VideoMode(WIDTH, HEIGHT),
		"DODGE BALLS",
		sf::Style::Titlebar | sf::Style::Close);
	this->window->setPosition(sf::Vector2i(START_X, START_Y));
	this->window->setFramerateLimit(60);
}

sf::Vector2i Game::genRandomNum(sf::Vector2f playerPos)
{
	sf::Vector2i spawnPos;
	std::vector<int> temp;

	std::uniform_int_distribution<int> dis1{0, static_cast<int>(playerPos.x - 150)};
	int gen1X = dis1(this->gen);
	std::uniform_int_distribution<int> dis2{static_cast<int>(playerPos.x + PLAYER_SIZE + 30), static_cast<int>(WIDTH - (ENEMY_SIZE + 20))};
	int gen2X = dis2(this->gen);

	temp.push_back(gen1X);
	temp.push_back(gen2X);
	spawnPos.x = temp[rand() % 2];
	temp.clear();

	std::uniform_int_distribution<int> dis3{0, static_cast<int>(playerPos.y - 150)};
	int gen1Y = dis3(this->gen);
	std::uniform_int_distribution<int> dis4{static_cast<int>(playerPos.y + PLAYER_SIZE + 30), static_cast<int>(HEIGHT - (ENEMY_SIZE + 20))};
	int gen2Y = dis4(this->gen);

	temp.push_back(gen1Y);
	temp.push_back(gen2Y);
	spawnPos.y = temp[rand() % 2];
	return spawnPos;
};

sf::Vector2f Game::normalize(sf::Vector2f position)
{
	float magnitude = sqrt(position.x * position.x + position.y * position.y);
	sf::Vector2f unit = position / magnitude;
	return unit;
};

void Game::spawnEnemies()
{

	this->enemy.setRadius(ENEMY_SIZE);
	sf::Vector2f playerPos = this->player.getPosition();
	sf::Vector2i spawnPos = this->genRandomNum(playerPos);
	this->enemy.setPosition(spawnPos.x, spawnPos.y);
	sf::Vector2f newPos = this->normalize(this->enemy.getPosition() - this->player.getPosition());

	this->direcArray.push_back(newPos);
	this->enemyArray.push_back(this->enemy);
}

void Game::updateEnemies()
{
	if (this->enemyArray.size() < this->maxEnemies)
	{
		if (this->spawnTimer >= this->maxSpawnTimer)
		{
			this->spawnEnemies();
			this->spawnTimer = 0.f;
		}
		else
		{
			this->spawnTimer += 1.f;
		}
	}
	for (int i = 0; i < this->enemyArray.size(); i++)
	{
		bool eDelete = false;
		sf::Vector2f newMove = -ENEMY_SPEED * this->direcArray[i];
		this->enemyArray[i].move(newMove.x, newMove.y);

		sf::Vector2f movement = this->enemyArray[i].getPosition();
		if (movement.x > WIDTH || movement.x < 0 || movement.y > HEIGHT || movement.y < 0)
		{
			eDelete = true;
		}

		if (this->enemyArray[i].getGlobalBounds().contains(this->player.getPosition()))
		{
			this->isWinOpen = false;
		}

		if (eDelete)
		{
			this->enemyArray.erase(this->enemyArray.begin() + i);
			this->direcArray.erase(this->direcArray.begin() + i);
		}
	}
}

void Game::renderEnemies()
{
	for (auto &enemy : this->enemyArray)
	{
		this->window->draw(enemy);
	}
}

void Game::initPlayer()
{
	this->player.setRadius(PLAYER_SIZE);
	this->player.setPosition(
		WIDTH / 2 - this->player.getRadius(), HEIGHT / 2 - this->player.getRadius());
	this->player.setFillColor(sf::Color::White);
}

void Game::updatePlayer()
{
	sf::Vector2f movePos = PLAYER_SPEED * this->normalize(this->mousePosView - this->player.getPosition());
	this->player.move(movePos.x, movePos.y);
}

void Game::renderPlayer()
{
	this->window->draw(this->player);
}

void Game::updateMousePosition()
{
	this->mousePosWin = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWin);
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				// std::cout << this->points << std::endl;
			}
			break;
		}
	}
}

void Game::update()
{
	this->updateEvents();
	this->updateMousePosition();
	this->updatePlayer();
	this->updateEnemies();
}

void Game::render()
{
	this->window->clear();

	this->renderEnemies();
	this->renderPlayer();

	this->window->display();
}

int main()
{
	Game game;
	while (game.isWinOpen)
	{
		game.update();
		game.render();
	}
	return 0;
}