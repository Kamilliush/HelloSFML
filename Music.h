#ifndef MUSIC_H
#define MUSIC_H

#include <SFML/Audio.hpp>
#include <thread>
#include <atomic>

class Music {
public:
    Music(const std::string& musicFile);
    ~Music();

    void play();
    void stop();
    void pause();
    void resume();
    void toggle();
    void setVolume(float volume);
    void increaseVolume();
    void decreaseVolume();

private:
    void run();

    sf::Music music;
    std::thread musicThread;
    std::atomic<bool> running;
    std::string musicFile;
};

#endif // MUSIC_H
