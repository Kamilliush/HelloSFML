#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    static bool authenticate(const std::string& username, const std::string& password);
    static void registerUser(const std::string& username, const std::string& password);
};

#endif // USER_H
