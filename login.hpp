#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>
#include <sstream>
#include "user.hpp"

class LoginSystem{
    public:
        LoginSystem() : isLoggedIn(false) {} // Construtor

        bool createUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& question,
                        const std::string& answer);

        bool login();

        bool logout();

        bool showUser();

        bool editUser();

        bool deleteUser();

        bool forgotPassword();

        User* findUserByUsername(const std::string& username);

        bool checkLength(const int MaxLength, const std::string& field);

        std::string getUsername() const {
            return currentUsername;
        }

        friend class SaveFile;

    protected:
        std::map<std::string, User> _users;

    private:
        bool isLoggedIn;
        std::string currentUsername;
};

class SaveFile{
    public:
        SaveFile(const std::string& filename) : _filename(filename), _file(filename){}

        bool save(LoginSystem& login);

        bool load(LoginSystem& login);

        static std::string getValue(const std::string& line);
    
    private:
        std::string _filename;
        std::ifstream _file;
};

#endif