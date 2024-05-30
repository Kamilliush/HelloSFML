#include "Time.h"
#include <iomanip>
#include <sstream>

Time::Time() : running(false), elapsedSeconds(0) {}

Time::~Time() {
    stop();
}

void Time::start() {
    if (!running) {
        running = true;
        timerThread = std::thread(&Time::run, this);
    }
}

void Time::stop() {
    if (running) {
        running = false;
        if (timerThread.joinable()) {
            timerThread.join();
        }
    }
}

void Time::reset() {
    elapsedSeconds = 0;
}

sf::Text Time::getTimeText(sf::Font& font) {
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;

    timeText.setFont(font);
    timeText.setString("Czas: " + oss.str());
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(100, 150);

    return timeText;
}

void Time::run() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (running) {
            ++elapsedSeconds;
        }
    }
}
