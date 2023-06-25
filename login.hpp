#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <map>
#include <algorithm>
#include "user.hpp"

class LoginSystem{
    public:
        LoginSystem()=default; // Construtor

        bool createUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& question,
                        const std::string& answer);

        bool login(const std::string& email, const std::string& password);

        bool logout();

        bool showUser();

        bool editUser();

        bool deleteUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& question,
                        const std::string& answer);

        bool forgotpassword(const std::string& email);

        std::string getUsername() const {
            return currentUsername;
        }
    
    private:
        std::map<std::string, User> _users;
        bool isLoggedIn;
        std::string currentUsername;
};

#endif