#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <map>
#include "password_hasher.hpp"

class User{
    public:
        User(const std::string& password, const std::string& email,
            const std::string& question, const std::string& answer) 
            : _password(passwordHash(calcularHash(password))), _email(email), 
            _question(question), _answer(answer) {}

        const std::string& getPassword() const {
            return _password;
        }

        const std::string& getEmail() const {
            return _email;
        }

        const std::string& getQuestion() const {
            return _question;
        }

        const std::string& getAnswer() const {
            return _answer;
        }
    
    private:
        std::string _password;
        std::string _email;
        std::string _question;
        std::string _answer;
};

class Login{
    public:
        LoginSystem();  // Construtor
        bool login(std::string& email, std::string& password);
        bool logout();
        void createUser(std::string& username, std::string& password, 
            std::string& email, std::string& question, 
            std::string& answer);
        bool editUser();
        void showUser();
        void deleteUser(std::string& username);
        bool forgotpassword(std::string& email);

        std::string getUsername() const {
            return currentUsername;
        }
    
    private:
        std::string currentUsername;
        bool isLoggedIn;
        std::map<string, User> _users;
};

class Arquivo{

}