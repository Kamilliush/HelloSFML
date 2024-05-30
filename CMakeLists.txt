cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(HelloSFML)

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ustawienie architektury na macOS
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Dodanie wszystkich plików źródłowych
set(SOURCES
        main.cpp
        Button.cpp
        Game.cpp
        Scoreboard.cpp
        Music.cpp
        Scene.cpp
        Slider.cpp
        Tile.cpp
        Time.cpp
        User.cpp
)

# Dodanie wszystkich plików nagłówkowych
set(HEADERS
        Button.h
        Game.h
        Scoreboard.h
        Music.h
        Scene.h
        Slider.h
        Tile.h
        Time.h
        User.h
)

# Dodanie pliku wykonywalnego
add_executable(HelloSFML ${SOURCES} ${HEADERS})

# Znalezienie i dołączenie bibliotek SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Dodanie katalogów z nagłówkami
include_directories(${SFML_INCLUDE_DIR})

# Linkowanie bibliotek SFML
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Kopiowanie plików czcionki, dźwięków i tekstowych do katalogu bin
add_custom_command(TARGET HelloSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        /Users/kamiljakut/Desktop/Studia/PK4/2048_v2/ClearSans-Regular.ttf
        $<TARGET_FILE_DIR:HelloSFML>/arial.ttf)

add_custom_command(TARGET HelloSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        /Users/kamiljakut/Desktop/Studia/PK4/2048_v2/background.ogg
        $<TARGET_FILE_DIR:HelloSFML>/background.ogg)

add_custom_command(TARGET HelloSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        /Users/kamiljakut/Desktop/Studia/PK4/2048_v2/tablicaLatwy.txt
        $<TARGET_FILE_DIR:HelloSFML>/tablicaLatwy.txt)

add_custom_command(TARGET HelloSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        /Users/kamiljakut/Desktop/Studia/PK4/2048_v2/tablicaNormalny.txt
        $<TARGET_FILE_DIR:HelloSFML>/tablicaNormalny.txt)

add_custom_command(TARGET HelloSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        /Users/kamiljakut/Desktop/Studia/PK4/2048_v2/tablicaTrudny.txt
        $<TARGET_FILE_DIR:HelloSFML>/tablicaTrudny.txt)

add_custom_command(TARGET HelloSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        /Users/kamiljakut/Desktop/Studia/PK4/2048_v2/logowanie.txt
        $<TARGET_FILE_DIR:HelloSFML>/logowanie.txt)

# Dodanie katalogów z bibliotekami, jeśli są w niestandardowej lokalizacji
link_directories(/opt/homebrew/lib)

# Opcjonalnie, można dodać komendy instalacji
install(TARGETS HelloSFML DESTINATION bin)