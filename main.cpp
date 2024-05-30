#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Tile.h"
#include "Game.h"
#include "User.h"
#include "Scoreboard.h"
#include "Scene.h"
#include "Enums.h"
#include "Music.h"
#include "Slider.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Application", sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    GameState gameState = GameState::Menu;
    Game game(font);
    sf::Clock clock;

    Difficulty selectedDifficulty = Difficulty::Normal;

    Music musicPlayer("background.ogg");
    musicPlayer.setVolume(50); // Set the volume (0 to 100)
    musicPlayer.play();

    Slider volumeSlider(sf::Vector2f(10, 640), sf::Vector2f(320, 20));
    volumeSlider.setValue(0.5f); // Set initial slider value to match the initial volume

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameState == GameState::Settings) {
                volumeSlider.handleEvent(event, window);
                musicPlayer.setVolume(volumeSlider.getValue() * 100); // Aktualizacja głośności na bieżąco
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (gameState == GameState::Menu) {
                    Scene::showMainMenu(window, font, gameState);
                }
                else if (gameState == GameState::Playing) {
                    Button newGameButton("Nowa Gra", sf::Vector2f(540, 600), sf::Vector2f(200, 50));
                    Button exitButton("Zakończ", sf::Vector2f(540, 660), sf::Vector2f(200, 50));
                    Button settingsButton("Ustawienia", sf::Vector2f(540, 720), sf::Vector2f(200, 50)); // Nowy przycisk ustawień w grze

                    if (newGameButton.isClicked(mousePos)) {
                        gameState = GameState::DifficultySelection;
                    }
                    else if (exitButton.isClicked(mousePos)) {
                        window.close();
                    }
                    else if (settingsButton.isClicked(mousePos)) {
                        gameState = GameState::Settings; // Przejdź do ekranu ustawień
                    }
                }
                else if (gameState == GameState::GameOver) {
                    Scene::showGameOver(window, font, gameState);
                }
                else if (gameState == GameState::Settings) {
                    Scene::showSettings(window, font, volumeSlider, gameState, musicPlayer); // Dodano parametr musicPlayer
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (gameState == GameState::Playing) {
                    game.handleInput(event.key.code);
                    if (game.isGameOver()) {
                        gameState = GameState::GameOver;
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        if (gameState == GameState::Playing) {
            game.update(deltaTime);
        }

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor tła na rgb(250, 248, 239)

        if (gameState == GameState::Menu) {
            Scene::showMainMenu(window, font, gameState);
        }
        else if (gameState == GameState::Playing) {
            game.draw(window, font);
            Button newGameButton("Nowa Gra", sf::Vector2f(540, 600), sf::Vector2f(200, 50));
            Button exitButton("Zakończ", sf::Vector2f(540, 660), sf::Vector2f(200, 50));
            Button settingsButton("Ustawienia", sf::Vector2f(540, 720), sf::Vector2f(200, 50)); // Rysowanie nowego przycisku ustawień w grze
            newGameButton.draw(window);
            exitButton.draw(window);
            settingsButton.draw(window); // Rysowanie nowego przycisku ustawień w grze
        }
        else if (gameState == GameState::HowToPlay) {
            Scene::showHowToPlay(window, font);
            gameState = GameState::Menu;
        }
        else if (gameState == GameState::Scoreboard) {
            Scoreboard::show(window, font);
            gameState = GameState::Menu;
        }
        else if (gameState == GameState::GameOver) {
            Scene::showGameOver(window, font, gameState);
        }
        else if (gameState == GameState::SaveScore) {
            Scene::showSaveScore(window, font, game.getScore(), selectedDifficulty, gameState);
        }
        else if (gameState == GameState::Register) {
            Scene::showRegister(window, font, game.getScore(), selectedDifficulty, gameState);
        }
        else if (gameState == GameState::DifficultySelection) {
            Scene::showDifficultySelection(window, font, selectedDifficulty, gameState);
            if (gameState == GameState::Playing) {
                game.setDifficulty(selectedDifficulty);
                game.reset();
            }
        }
        else if (gameState == GameState::Settings) {
            Scene::showSettings(window, font, volumeSlider, gameState, musicPlayer); // Dodano parametr musicPlayer
        }

        window.display();
    }

    musicPlayer.stop(); // Ensure music stops when the game exits

    return 0;
}
