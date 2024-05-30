#include "Scene.h"
#include "Music.h" // Dodaj nag³ówek Music
#include <fstream>

void Scene::showMainMenu(sf::RenderWindow& window, sf::Font& font, GameState& gameState) {
    sf::Text titleText("2048", font, 100);
    titleText.setFillColor(sf::Color(119, 110, 101)); // Kolor napisu na rgb(119, 110, 101)
    titleText.setPosition(640 - titleText.getLocalBounds().width / 2, 50);

    Button playButton("Graj", sf::Vector2f(540, 200), sf::Vector2f(200, 50));
    Button howToPlayButton("Jak Graæ", sf::Vector2f(540, 300), sf::Vector2f(200, 50));
    Button scoreboardButton("Tablica Wyników", sf::Vector2f(540, 400), sf::Vector2f(200, 50));
    Button settingsButton("Ustawienia", sf::Vector2f(540, 500), sf::Vector2f(200, 50)); // Dodaj przycisk ustawieñ w menu g³ównym

    while (window.isOpen() && gameState == GameState::Menu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (playButton.isClicked(mousePos)) {
                    gameState = GameState::DifficultySelection;
                }
                else if (howToPlayButton.isClicked(mousePos)) {
                    gameState = GameState::HowToPlay;
                }
                else if (scoreboardButton.isClicked(mousePos)) {
                    gameState = GameState::Scoreboard;
                }
                else if (settingsButton.isClicked(mousePos)) { // Obs³uga klikniêcia przycisku ustawieñ
                    gameState = GameState::Settings;
                }
            }
        }

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(titleText);
        playButton.draw(window);
        howToPlayButton.draw(window);
        scoreboardButton.draw(window);
        settingsButton.draw(window); // Rysowanie przycisku ustawieñ w menu g³ównym
        window.display();
    }
}

void Scene::showGameOver(sf::RenderWindow& window, sf::Font& font, GameState& gameState) {
    sf::Text gameOverText("Przegra³eœ!", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(640 - gameOverText.getLocalBounds().width / 2, 200);

    Button newGameButton("Nowa Gra", sf::Vector2f(540, 400), sf::Vector2f(200, 50));
    Button saveScoreButton("Zapisz Wynik", sf::Vector2f(540, 460), sf::Vector2f(200, 50));
    Button exitButton("Zakoñcz", sf::Vector2f(540, 520), sf::Vector2f(200, 50));

    while (window.isOpen() && gameState == GameState::GameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (newGameButton.isClicked(mousePos)) {
                    gameState = GameState::DifficultySelection;
                }
                else if (saveScoreButton.isClicked(mousePos)) {
                    gameState = GameState::SaveScore;
                }
                else if (exitButton.isClicked(mousePos)) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(gameOverText);
        newGameButton.draw(window);
        saveScoreButton.draw(window);
        exitButton.draw(window);
        window.display();
    }
}

void Scene::showSettings(sf::RenderWindow& window, sf::Font& font, Slider& volumeSlider, GameState& gameState, Music& musicPlayer) {
    sf::Text titleText("Ustawienia", font, 50);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(640 - titleText.getLocalBounds().width / 2, 50);

    Button backButton("Powrót", sf::Vector2f(540, 400), sf::Vector2f(200, 50));

    while (window.isOpen() && gameState == GameState::Settings) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            volumeSlider.handleEvent(event, window);
            musicPlayer.setVolume(volumeSlider.getValue() * 100); // Aktualizacja g³oœnoœci na bie¿¹co

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (backButton.isClicked(mousePos)) {
                    gameState = GameState::Menu;
                }
            }
        }

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(titleText);
        backButton.draw(window);
        volumeSlider.draw(window);
        window.display();
    }
}


void Scene::showSaveScore(sf::RenderWindow& window, sf::Font& font, int score, Difficulty difficulty, GameState& gameState) {
    sf::Text usernameText("Login:", font, 24);
    usernameText.setFillColor(sf::Color::Black);
    usernameText.setPosition(540, 300);

    sf::Text passwordText("Has³o:", font, 24);
    passwordText.setFillColor(sf::Color::Black);
    passwordText.setPosition(540, 360);

    sf::String userInputUsername;
    sf::String userInputPassword;

    sf::Text inputUsername("", font, 24);
    inputUsername.setFillColor(sf::Color::Black);
    inputUsername.setPosition(640, 300);

    sf::Text inputPassword("", font, 24);
    inputPassword.setFillColor(sf::Color::Black);
    inputPassword.setPosition(640, 360);

    sf::Text messageText("", font, 24);
    messageText.setFillColor(sf::Color::Red);
    messageText.setPosition(540, 420);

    Button saveButton("Zapisz", sf::Vector2f(540, 500), sf::Vector2f(95, 50));
    Button cancelButton("Anuluj", sf::Vector2f(645, 500), sf::Vector2f(95, 50));
    Button retryButton("Ponowna Próba", sf::Vector2f(540, 560), sf::Vector2f(200, 50));
    Button registerButton("Rejestracja", sf::Vector2f(540, 620), sf::Vector2f(200, 50));

    bool inputCompleted = false;
    bool usernameEntered = true;

    while (window.isOpen() && !inputCompleted) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (usernameEntered && !userInputUsername.isEmpty()) {
                        userInputUsername.erase(userInputUsername.getSize() - 1);
                    }
                    else if (!usernameEntered && !userInputPassword.isEmpty()) {
                        userInputPassword.erase(userInputPassword.getSize() - 1);
                    }
                }
                else if (event.text.unicode < 128) {
                    if (usernameEntered) {
                        userInputUsername += event.text.unicode;
                    }
                    else {
                        userInputPassword += event.text.unicode;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (usernameEntered) {
                        usernameEntered = false;
                    }
                    else {
                        inputCompleted = true;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (saveButton.isClicked(mousePos)) {
                    inputCompleted = true;
                }
                else if (cancelButton.isClicked(mousePos)) {
                    gameState = GameState::Menu;
                    return;
                }
                else if (retryButton.isClicked(mousePos)) {
                    userInputUsername.clear();
                    userInputPassword.clear();
                    usernameEntered = true;
                }
                else if (registerButton.isClicked(mousePos)) {
                    gameState = GameState::Register;
                    return;
                }
            }
        }

        inputUsername.setString(userInputUsername);
        inputPassword.setString(std::string(userInputPassword.getSize(), '*'));

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(usernameText);
        window.draw(passwordText);
        window.draw(inputUsername);
        window.draw(inputPassword);
        window.draw(messageText);
        saveButton.draw(window);
        cancelButton.draw(window);
        retryButton.draw(window);
        registerButton.draw(window);

        if (usernameEntered) {
            sf::RectangleShape cursor(sf::Vector2f(2, 24));
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(inputUsername.getPosition().x + inputUsername.getGlobalBounds().width + 2, inputUsername.getPosition().y);
            window.draw(cursor);
        }
        else {
            sf::RectangleShape cursor(sf::Vector2f(2, 24));
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(inputPassword.getPosition().x + inputPassword.getGlobalBounds().width + 2, inputPassword.getPosition().y);
            window.draw(cursor);
        }

        window.display();
    }

    std::string username = userInputUsername;
    std::string password = userInputPassword;

    if (User::authenticate(username, password)) {
        saveScore(username, score, difficulty);
        messageText.setString("Wynik zapisany pomyœlnie!");
        gameState = GameState::Menu;
    }
    else {
        messageText.setString("Nieprawid³owy login lub has³o.");
        showRetryRegister(window, font, score, difficulty, gameState);
    }
}

void Scene::showRegister(sf::RenderWindow& window, sf::Font& font, int score, Difficulty difficulty, GameState& gameState) {
    sf::Text usernameText("Login:", font, 24);
    usernameText.setFillColor(sf::Color::Black);
    usernameText.setPosition(540, 300);

    sf::Text passwordText("Has³o:", font, 24);
    passwordText.setFillColor(sf::Color::Black);
    passwordText.setPosition(540, 360);

    sf::String userInputUsername;
    sf::String userInputPassword;

    sf::Text inputUsername("", font, 24);
    inputUsername.setFillColor(sf::Color::Black);
    inputUsername.setPosition(640, 300);

    sf::Text inputPassword("", font, 24);
    inputPassword.setFillColor(sf::Color::Black);
    inputPassword.setPosition(640, 360);

    sf::Text messageText("", font, 24);
    messageText.setFillColor(sf::Color::Red);
    messageText.setPosition(540, 420);

    Button registerButton("Zarejestruj", sf::Vector2f(540, 500), sf::Vector2f(200, 50));
    Button cancelButton("Anuluj", sf::Vector2f(540, 560), sf::Vector2f(200, 50));
    Button retryRegisterButton("Ponowna Próba", sf::Vector2f(540, 620), sf::Vector2f(200, 50));

    bool inputCompleted = false;
    bool usernameEntered = true;

    while (window.isOpen() && !inputCompleted) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (usernameEntered && !userInputUsername.isEmpty()) {
                        userInputUsername.erase(userInputUsername.getSize() - 1);
                    }
                    else if (!usernameEntered && !userInputPassword.isEmpty()) {
                        userInputPassword.erase(userInputPassword.getSize() - 1);
                    }
                }
                else if (event.text.unicode < 128) {
                    if (usernameEntered) {
                        userInputUsername += event.text.unicode;
                    }
                    else {
                        userInputPassword += event.text.unicode;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (usernameEntered) {
                        usernameEntered = false;
                    }
                    else {
                        inputCompleted = true;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (registerButton.isClicked(mousePos)) {
                    inputCompleted = true;
                }
                else if (cancelButton.isClicked(mousePos)) {
                    gameState = GameState::Menu;
                    return;
                }
                else if (retryRegisterButton.isClicked(mousePos)) {
                    userInputUsername.clear();
                    userInputPassword.clear();
                    usernameEntered = true;
                }
            }
        }

        inputUsername.setString(userInputUsername);
        inputPassword.setString(std::string(userInputPassword.getSize(), '*'));

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(usernameText);
        window.draw(passwordText);
        window.draw(inputUsername);
        window.draw(inputPassword);
        window.draw(messageText);
        registerButton.draw(window);
        cancelButton.draw(window);
        retryRegisterButton.draw(window);

        if (usernameEntered) {
            sf::RectangleShape cursor(sf::Vector2f(2, 24));
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(inputUsername.getPosition().x + inputUsername.getGlobalBounds().width + 2, inputUsername.getPosition().y);
            window.draw(cursor);
        }
        else {
            sf::RectangleShape cursor(sf::Vector2f(2, 24));
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(inputPassword.getPosition().x + inputPassword.getGlobalBounds().width + 2, inputPassword.getPosition().y);
            window.draw(cursor);
        }

        window.display();
    }

    std::string username = userInputUsername;
    std::string password = userInputPassword;

    if (!username.empty() && !password.empty()) {
        User::registerUser(username, password);
        saveScore(username, score, difficulty); // Add score to the scoreboard
        messageText.setString("Rejestracja zakoñczona pomyœlnie!");
        gameState = GameState::Menu;
    }
    else {
        messageText.setString("Login i has³o nie mog¹ byæ puste.");
        showRetryRegister(window, font, score, difficulty, gameState);
    }
}

void Scene::showRetryRegister(sf::RenderWindow& window, sf::Font& font, int score, Difficulty difficulty, GameState& gameState) {
    sf::Text usernameText("Login:", font, 24);
    usernameText.setFillColor(sf::Color::Black);
    usernameText.setPosition(540, 300);

    sf::Text passwordText("Has³o:", font, 24);
    passwordText.setFillColor(sf::Color::Black);
    passwordText.setPosition(540, 360);

    sf::String userInputUsername;
    sf::String userInputPassword;

    sf::Text inputUsername("", font, 24);
    inputUsername.setFillColor(sf::Color::Black);
    inputUsername.setPosition(640, 300);

    sf::Text inputPassword("", font, 24);
    inputPassword.setFillColor(sf::Color::Black);
    inputPassword.setPosition(640, 360);

    sf::Text messageText("Login i has³o nie mog¹ byæ puste.", font, 24);
    messageText.setFillColor(sf::Color::Red);
    messageText.setPosition(540, 420);

    Button registerButton("Zarejestruj", sf::Vector2f(540, 500), sf::Vector2f(200, 50));
    Button cancelButton("Anuluj", sf::Vector2f(540, 560), sf::Vector2f(200, 50));
    Button retryRegisterButton("Ponowna Rejestracja", sf::Vector2f(540, 620), sf::Vector2f(200, 50));

    bool inputCompleted = false;
    bool usernameEntered = true;

    while (window.isOpen() && !inputCompleted) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (usernameEntered && !userInputUsername.isEmpty()) {
                        userInputUsername.erase(userInputUsername.getSize() - 1);
                    }
                    else if (!usernameEntered && !userInputPassword.isEmpty()) {
                        userInputPassword.erase(userInputPassword.getSize() - 1);
                    }
                }
                else if (event.text.unicode < 128) {
                    if (usernameEntered) {
                        userInputUsername += event.text.unicode;
                    }
                    else {
                        userInputPassword += event.text.unicode;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (usernameEntered) {
                        usernameEntered = false;
                    }
                    else {
                        inputCompleted = true;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (registerButton.isClicked(mousePos)) {
                    inputCompleted = true;
                }
                else if (cancelButton.isClicked(mousePos)) {
                    gameState = GameState::Menu;
                    return;
                }
                else if (retryRegisterButton.isClicked(mousePos)) {
                    userInputUsername.clear();
                    userInputPassword.clear();
                    usernameEntered = true;
                }
            }
        }

        inputUsername.setString(userInputUsername);
        inputPassword.setString(std::string(userInputPassword.getSize(), '*'));

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(usernameText);
        window.draw(passwordText);
        window.draw(inputUsername);
        window.draw(inputPassword);
        window.draw(messageText);
        registerButton.draw(window);
        cancelButton.draw(window);
        retryRegisterButton.draw(window);

        if (usernameEntered) {
            sf::RectangleShape cursor(sf::Vector2f(2, 24));
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(inputUsername.getPosition().x + inputUsername.getGlobalBounds().width + 2, inputUsername.getPosition().y);
            window.draw(cursor);
        }
        else {
            sf::RectangleShape cursor(sf::Vector2f(2, 24));
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(inputPassword.getPosition().x + inputPassword.getGlobalBounds().width + 2, inputPassword.getPosition().y);
            window.draw(cursor);
        }

        window.display();
    }

    std::string username = userInputUsername;
    std::string password = userInputPassword;

    if (!username.empty() && !password.empty()) {
        User::registerUser(username, password);
        saveScore(username, score, difficulty); // Add score to the scoreboard
        messageText.setString("Rejestracja zakoñczona pomyœlnie!");
        gameState = GameState::Menu;
    }
    else {
        messageText.setString("Login i has³o nie mog¹ byæ puste.");
        showRetryRegister(window, font, score, difficulty, gameState);
    }
}


void Scene::showHowToPlay(sf::RenderWindow& window, sf::Font& font) {
    sf::Text howToPlayText(
        "Jak graæ w 2048:\n\n"
        "U¿ywaj strza³ek na klawiaturze, aby przesuwaæ kafelki.\n"
        "Gdy dwa kafelki o tej samej wartoœci siê zetkn¹, ³¹cz¹ siê w jeden.\n"
        "Celem gry jest osi¹gniêcie kafelka o wartoœci 2048.",
        font, 24
    );
    howToPlayText.setFillColor(sf::Color::Black);
    howToPlayText.setPosition(640 - howToPlayText.getLocalBounds().width / 2, 200);

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
        backButton.draw(window);
        window.draw(howToPlayText);
        window.display();
    }
}

void Scene::showDifficultySelection(sf::RenderWindow& window, sf::Font& font, Difficulty& selectedDifficulty, GameState& gameState) {
    sf::Text selectDifficultyText("Wybierz Poziom Trudnoœci", font, 50);
    selectDifficultyText.setFillColor(sf::Color::Black);
    selectDifficultyText.setPosition(640 - selectDifficultyText.getLocalBounds().width / 2, 100);

    Button easyButton("£atwy", sf::Vector2f(540, 200), sf::Vector2f(200, 50));
    Button normalButton("Normalny", sf::Vector2f(540, 300), sf::Vector2f(200, 50));
    Button hardButton("Trudny", sf::Vector2f(540, 400), sf::Vector2f(200, 50));
    Button backButton("Powrót", sf::Vector2f(540, 500), sf::Vector2f(200, 50));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (easyButton.isClicked(mousePos)) {
                    selectedDifficulty = Difficulty::Easy;
                    gameState = GameState::Playing;
                    return;
                }
                else if (normalButton.isClicked(mousePos)) {
                    selectedDifficulty = Difficulty::Normal;
                    gameState = GameState::Playing;
                    return;
                }
                else if (hardButton.isClicked(mousePos)) {
                    selectedDifficulty = Difficulty::Hard;
                    gameState = GameState::Playing;
                    return;
                }
                else if (backButton.isClicked(mousePos)) {
                    gameState = GameState::Menu;
                    return;
                }
            }
        }

        window.clear(sf::Color(250, 248, 239)); // Ustawia kolor t³a na rgb(250, 248, 239)
        window.draw(selectDifficultyText);
        easyButton.draw(window);
        normalButton.draw(window);
        hardButton.draw(window);
        backButton.draw(window);
        window.display();
    }
}



void Scene::saveScore(const std::string& username, int score, Difficulty difficulty) {
    std::string filename;
    switch (difficulty) {
    case Difficulty::Easy:
        filename = "tablicaLatwy.txt";
        break;
    case Difficulty::Normal:
        filename = "tablicaNormalny.txt";
        break;
    case Difficulty::Hard:
        filename = "tablicaTrudny.txt";
        break;
    }

    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << username << " " << score << "\n";
        file.close();
    }
}
