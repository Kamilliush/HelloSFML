#include "Game.h"
#include "Button.h" // Dodaj nag³ówek Button
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>

Game::Game(sf::Font& font)
    : score(0), gameOver(false), gridSize(4), tileSize(100.0f), font(font), gameTime() {
    srand(static_cast<unsigned>(time(nullptr)));
    reset();
}

void Game::setDifficulty(Difficulty difficulty) {
    switch (difficulty) {
    case Difficulty::Easy:
        gridSize = 5;
        tileSize = 80.0f;
        break;
    case Difficulty::Normal:
        gridSize = 4;
        tileSize = 100.0f;
        break;
    case Difficulty::Hard:
        gridSize = 3;
        tileSize = 120.0f;
        break;
    }
    reset();
}

void Game::reset() {
    board = std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
    tiles.clear();
    score = 0;
    gameOver = false;
    gameTime.reset();
    gameTime.start();
    spawnTile();
    spawnTile();
}

void Game::update(float deltaTime) {
    for (auto& tile : tiles) {
        tile.update(deltaTime);
    }
    tiles.erase(std::remove_if(tiles.begin(), tiles.end(), [](const Tile& tile) { return !tile.isMoving(); }), tiles.end());
}

void Game::draw(sf::RenderWindow& window, sf::Font& font) {
    drawBoard(window, font);
    drawScore(window, font);
    drawTime(window, font);
    if (gameOver) {
        drawGameOver(window, font);
    }

    Button newGameButton("Nowa Gra", sf::Vector2f(540, 600), sf::Vector2f(200, 50));
    Button exitButton("Zakoñcz", sf::Vector2f(540, 660), sf::Vector2f(200, 50));
    Button settingsButton("Ustawienia", sf::Vector2f(540, 720), sf::Vector2f(200, 50)); // Rysowanie nowego przycisku ustawieñ w grze
    newGameButton.draw(window);
    exitButton.draw(window);
    settingsButton.draw(window); // Rysowanie nowego przycisku ustawieñ w grze
}

void Game::handleInput(sf::Keyboard::Key key) {
    if (gameOver) return;

    bool moved = false;
    if (key == sf::Keyboard::Left) {
        moved = moveLeft();
    }
    else if (key == sf::Keyboard::Right) {
        moved = moveRight();
    }
    else if (key == sf::Keyboard::Up) {
        moved = moveUp();
    }
    else if (key == sf::Keyboard::Down) {
        moved = moveDown();
    }

    if (moved) {
        spawnTile();
        if (isGameOverCondition()) {
            gameOver = true;
            gameTime.stop();
        }
    }
}

int Game::getScore() const { return score; }
bool Game::isGameOver() const { return gameOver; }

void Game::spawnTile() {
    std::vector<std::pair<int, int>> emptyTiles;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == 0) {
                emptyTiles.push_back({ i, j });
            }
        }
    }

    if (!emptyTiles.empty()) {
        int randIndex = rand() % emptyTiles.size();
        int value = (rand() % 20 == 0) ? 4 : 2;  // 5% chance of 4
        board[emptyTiles[randIndex].first][emptyTiles[randIndex].second] = value;
        tiles.emplace_back(value, getTilePosition(emptyTiles[randIndex].first, emptyTiles[randIndex].second), tileSize, font);
    }
}

bool Game::moveLeft() {
    bool moved = false;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 1; j < gridSize; ++j) {
            if (board[i][j] != 0) {
                int k = j;
                while (k > 0 && board[i][k - 1] == 0) {
                    std::swap(board[i][k], board[i][k - 1]);
                    updateTilePosition(i, k, i, k - 1);
                    --k;
                    moved = true;
                }
                if (k > 0 && board[i][k - 1] == board[i][k]) {
                    board[i][k - 1] *= 2;
                    board[i][k] = 0;
                    score += board[i][k - 1];
                    updateTilePosition(i, k, i, k - 1);
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool Game::moveRight() {
    bool moved = false;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = gridSize - 2; j >= 0; --j) {
            if (board[i][j] != 0) {
                int k = j;
                while (k < gridSize - 1 && board[i][k + 1] == 0) {
                    std::swap(board[i][k], board[i][k + 1]);
                    updateTilePosition(i, k, i, k + 1);
                    ++k;
                    moved = true;
                }
                if (k < gridSize - 1 && board[i][k + 1] == board[i][k]) {
                    board[i][k + 1] *= 2;
                    board[i][k] = 0;
                    score += board[i][k + 1];
                    updateTilePosition(i, k, i, k + 1);
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool Game::moveUp() {
    bool moved = false;
    for (int j = 0; j < gridSize; ++j) {
        for (int i = 1; i < gridSize; ++i) {
            if (board[i][j] != 0) {
                int k = i;
                while (k > 0 && board[k - 1][j] == 0) {
                    std::swap(board[k][j], board[k - 1][j]);
                    updateTilePosition(k, j, k - 1, j);
                    --k;
                    moved = true;
                }
                if (k > 0 && board[k - 1][j] == board[k][j]) {
                    board[k - 1][j] *= 2;
                    board[k][j] = 0;
                    score += board[k - 1][j];
                    updateTilePosition(k, j, k - 1, j);
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool Game::moveDown() {
    bool moved = false;
    for (int j = 0; j < gridSize; ++j) {
        for (int i = gridSize - 2; i >= 0; --i) {
            if (board[i][j] != 0) {
                int k = i;
                while (k < gridSize - 1 && board[k + 1][j] == 0) {
                    std::swap(board[k][j], board[k + 1][j]);
                    updateTilePosition(k, j, k + 1, j);
                    ++k;
                    moved = true;
                }
                if (k < gridSize - 1 && board[k + 1][j] == board[k][j]) {
                    board[k + 1][j] *= 2;
                    board[k][j] = 0;
                    score += board[k + 1][j];
                    updateTilePosition(k, j, k + 1, j);
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool Game::isGameOverCondition() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == 0) return false;
            if (i > 0 && board[i][j] == board[i - 1][j]) return false;
            if (i < gridSize - 1 && board[i][j] == board[i + 1][j]) return false;
            if (j > 0 && board[i][j] == board[i][j - 1]) return false;
            if (j < gridSize - 1 && board[i][j] == board[i][j + 1]) return false;
        }
    }
    return true;
}

void Game::drawBoard(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));
    tileShape.setOutlineThickness(5);
    tileShape.setOutlineColor(sf::Color(187, 173, 160)); // Kolor ramki na rgb(187, 173, 160)

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            tileShape.setPosition(350 + j * (tileSize + 10), 100 + i * (tileSize + 10));
            tileShape.setFillColor(sf::Color(205, 193, 180)); // Kolor pustego pola na rgb(205, 193, 180)
            window.draw(tileShape);
            if (board[i][j] != 0) {
                Tile tile(board[i][j], getTilePosition(i, j), tileSize, font);
                tile.draw(window);
            }
        }
    }
}

void Game::drawScore(sf::RenderWindow& window, sf::Font& font) {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Wynik: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(100, 100);
    window.draw(scoreText);
}

void Game::drawTime(sf::RenderWindow& window, sf::Font& font) {
    window.draw(gameTime.getTimeText(font));
}

void Game::drawGameOver(sf::RenderWindow& window, sf::Font& font) {
    sf::Text gameOverText("Przegra³eœ!", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(640 - gameOverText.getLocalBounds().width / 2, 200);
    window.draw(gameOverText);
}

sf::Vector2f Game::getTilePosition(int x, int y) const {
    return sf::Vector2f(350 + y * (tileSize + 10), 100 + x * (tileSize + 10));
}

void Game::updateTilePosition(int oldX, int oldY, int newX, int newY) {
    for (auto& tile : tiles) {
        if (tile.getPosition() == getTilePosition(oldX, oldY)) {
            tile.setTargetPosition(getTilePosition(newX, newY));
            break;
        }
    }
}
