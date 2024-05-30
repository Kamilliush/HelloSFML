#include "Music.h"

Music::Music(const std::string& musicFile)
    : musicFile(musicFile), running(false) {
}

Music::~Music() {
    stop();
}

void Music::play() {
    if (!running) {
        running = true;
        musicThread = std::thread(&Music::run, this);
    }
}

void Music::stop() {
    if (running) {
        running = false;
        if (musicThread.joinable()) {
            musicThread.join();
        }
        music.stop();
    }
}

void Music::pause() {
    music.pause();
}

void Music::resume() {
    music.play();
}

void Music::toggle() {
    if (music.getStatus() == sf::Music::Playing) {
        music.pause();
    }
    else {
        music.play();
    }
}

void Music::setVolume(float volume) {
    music.setVolume(volume);
}

void Music::increaseVolume() {
    float volume = music.getVolume();
    if (volume < 100) {
        music.setVolume(volume + 10);
    }
}

void Music::decreaseVolume() {
    float volume = music.getVolume();
    if (volume > 0) {
        music.setVolume(volume - 10);
    }
}

void Music::run() {

    if (!music.openFromFile(musicFile)) {
        return; // Error handling if the music file cannot be opened
    }
    music.setLoop(true); // Ensure the music loops
    music.play();

    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
