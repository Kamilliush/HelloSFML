#include "User.h"
#include <fstream>

bool User::authenticate(const std::string& username, const std::string& password) {
    std::ifstream file("logowanie.txt");
    std::string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            return true;
        }
    }
    return false;
}

void User::registerUser(const std::string& username, const std::string& password) {
    std::ofstream file("logowanie.txt", std::ios::app);
    if (file.is_open()) {
        file << username << " " << password << "\n";
        file.close();
    }
}
