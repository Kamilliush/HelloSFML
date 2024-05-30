#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Game.h"
#include "User.h"
#include "Scoreboard.h"
#include "Enums.h"
#include "Slider.h"
#include "Music.h" // Dodaj nag³ówek Music

class Scene {
public:
    static void showMainMenu(sf::RenderWindow& window, sf::Font& font, GameState& gameState);
    static void showGameOver(sf::RenderWindow& window, sf::Font& font, GameState& gameState);
    static void showSaveScore(sf::RenderWindow& window, sf::Font& font, int score, Difficulty difficulty, GameState& gameState);
    static void showRegister(sf::RenderWindow& window, sf::Font& font, int score, Difficulty difficulty, GameState& gameState);
    static void showHowToPlay(sf::RenderWindow& window, sf::Font& font);
    static void showDifficultySelection(sf::RenderWindow& window, sf::Font& font, Difficulty& selectedDifficulty, GameState& gameState);
    static void showRetryRegister(sf::RenderWindow& window, sf::Font& font, int score, Difficulty difficulty, GameState& gameState);
    static void showSettings(sf::RenderWindow& window, sf::Font& font, Slider& volumeSlider, GameState& gameState, Music& musicPlayer); // Dodano parametr Music
private:
    static void saveScore(const std::string& username, int score, Difficulty difficulty);
};

#endif // SCENE_H
