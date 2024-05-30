#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

class Scoreboard {
public:
    static std::vector<std::pair<std::string, int>> loadScores(const std::string& filename);
    static void show(sf::RenderWindow& window, sf::Font& font);
};

#endif // SCOREBOARD_H
