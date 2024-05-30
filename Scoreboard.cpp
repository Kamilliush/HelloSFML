#include "Scoreboard.h"
#include "Button.h"
#include <fstream>
#include <algorithm>

std::vector<std::pair<std::string, int>> Scoreboard::loadScores(const std::string& filename) {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(filename);
    std::string name;
    int score;
    while (file >> name >> score) {
        scores.push_back(std::make_pair(name, score));
    }
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return b.second > a.second; // Higher scores first
        });
    return scores;
}

void Scoreboard::show(sf::RenderWindow& window, sf::Font& font) {
    auto easyScores = loadScores("tablicaLatwy.txt");
    auto normalScores = loadScores("tablicaNormalny.txt");
    auto hardScores = loadScores("tablicaTrudny.txt");

    sf::Text scoreboardTitle("Tablica Wyników", font, 50);
    scoreboardTitle.setFillColor(sf::Color::Black);
    scoreboardTitle.setPosition(640 - scoreboardTitle.getLocalBounds().width / 2, 50);

    sf::Text easyTitle("£atwy", font, 24);
    easyTitle.setFillColor(sf::Color::Black);
    easyTitle.setPosition(200 - easyTitle.getLocalBounds().width / 2, 150);

    sf::Text normalTitle("Normalny", font, 24);
    normalTitle.setFillColor(sf::Color::Black);
    normalTitle.setPosition(640 - normalTitle.getLocalBounds().width / 2, 150);

    sf::Text hardTitle("Trudny", font, 24);
    hardTitle.setFillColor(sf::Color::Black);
    hardTitle.setPosition(1080 - hardTitle.getLocalBounds().width / 2, 150);

    sf::Text easyScoresText("", font, 24);
    easyScoresText.setFillColor(sf::Color::Black);
    std::string easyScoreString;
    for (const auto& score : easyScores) {
        easyScoreString += score.first + ": " + std::to_string(score.second) + "\n";
    }
    easyScoresText.setString(easyScoreString);
    easyScoresText.setPosition(100, 200);

    sf::Text normalScoresText("", font, 24);
    normalScoresText.setFillColor(sf::Color::Black);
    std::string normalScoreString;
    for (const auto& score : normalScores) {
        normalScoreString += score.first + ": " + std::to_string(score.second) + "\n";
    }
    normalScoresText.setString(normalScoreString);
    normalScoresText.setPosition(540, 200);

    sf::Text hardScoresText("", font, 24);
    hardScoresText.setFillColor(sf::Color::Black);
    std::string hardScoreString;
    for (const auto& score : hardScores) {
        hardScoreString += score.first + ": " + std::to_string(score.second) + "\n";
    }
    hardScoresText.setString(hardScoreString);
    hardScoresText.setPosition(980, 200);

    Button backButton("Powrót", sf::Vector2f(540, 600), sf::Vector2f(200, 50));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (backButton.isClicked(mousePos)) {
                    return; // Go back to the main menu
                }
            }
        }

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(scoreboardTitle);
        window.draw(easyTitle);
        window.draw(normalTitle);
        window.draw(hardTitle);
        window.draw(easyScoresText);
        window.draw(normalScoresText);
        window.draw(hardScoresText);
        backButton.draw(window);
        window.display();
    }
}
