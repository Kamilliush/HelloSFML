#ifndef TIME_H
#define TIME_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <chrono>

class Time {
public:
    Time();
    ~Time();

    void start();
    void stop();
    void reset();
    sf::Text getTimeText(sf::Font& font);

private:
    void run();

    std::thread timerThread;
    std::atomic<bool> running;
    std::atomic<int> elapsedSeconds;
    sf::Text timeText;
};

#endif // TIME_H
