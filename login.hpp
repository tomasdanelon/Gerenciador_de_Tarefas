#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <map>
#include <algorithm>
#include <regex>
#include "user.hpp"

class LoginSystem{
    public:
        LoginSystem() : isLoggedIn(false) {} // Construtor

        bool createUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& question,
                        const std::string& answer);

        bool login(const std::string& username, const std::string& password);

        bool logout();

        bool showUser();

        bool editUser(const std::string& password, const int& choice, 
                      const std::string& change1, const std::string& change2);

        bool deleteUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& answer,
                        const std::string& confirmation);

        bool forgotPassword(const std::string& username, const std::string& answer, 
                            const std::string& newPassword);

        User* findUserByUsername(const std::string& username);

        std::string getUsername() const {
            return currentUsername;
        }
    
    private:
        std::map<std::string, User> _users;
        bool isLoggedIn;
        std::string currentUsername;
};

#endif