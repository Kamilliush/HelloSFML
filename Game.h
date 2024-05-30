#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Enums.h"
#include "Time.h"
#include <vector>
#include <string>

class Game {
public:
    Game(sf::Font& font);

    void setDifficulty(Difficulty difficulty);
    void reset();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window, sf::Font& font);
    void handleInput(sf::Keyboard::Key key);
    int getScore() const;
    bool isGameOver() const;

private:
    std::vector<std::vector<int>> board;
    std::vector<Tile> tiles;
    int score;
    bool gameOver;
    int gridSize;
    float tileSize;
    sf::Font& font;

    Time gameTime;

    void spawnTile();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool isGameOverCondition() const;
    void drawBoard(sf::RenderWindow& window, sf::Font& font);
    void drawScore(sf::RenderWindow& window, sf::Font& font);
    void drawTime(sf::RenderWindow& window, sf::Font& font);
    void drawGameOver(sf::RenderWindow& window, sf::Font& font);
    sf::Vector2f getTilePosition(int x, int y) const;
    void updateTilePosition(int oldX, int oldY, int newX, int newY);
};

#endif // GAME_H
