#ifndef USER_H
#define USER_H
#include <string>
#include <map>
#include "password_hasher.hpp"

class User{
    public:
        User() = default;
        User(const std::string& password, const std::string& email,
            const std::string& question, const std::string& answer) 
            : _password(PasswordHasher::calcularHash(password)), _email(email), 
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

        void setPassword(const std::string& password) {
            _password = password;
        }

        void setEmail(const std::string& email) {
            _email = email;
        }

        void setQuestion(const std::string& question) {
            _question = question;
        }

        void setAnswer(const std::string& answer) {
            _answer = answer;
        }      
    
    private:
        std::string _password;
        std::string _email;
        std::string _question;
        std::string _answer;
};

#endif