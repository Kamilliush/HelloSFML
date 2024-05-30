#ifndef ENUMS_H
#define ENUMS_H

enum class GameState {
    Menu,
    DifficultySelection,
    Playing,
    HowToPlay,
    Scoreboard,
    GameOver,
    SaveScore,
    Register,
    Settings // Nowy stan gry
};

enum class Difficulty {
    Easy,
    Normal,
    Hard
};

#endif // ENUMS_H
