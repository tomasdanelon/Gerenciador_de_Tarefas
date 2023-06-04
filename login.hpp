#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <vector>

    class User{
    public:
        User(const std::string& name, const std::string& password, 
            const std::string& email, const std::string& question, 
            const std::string& answer) 
            : _name(name), _password(password), _email(email), 
            _question(question), _answer(answer) {}

        const std::string& getName() const {
            return _name;
        }

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
        std::string _name;
        std::string _password;
        std::string _email;
        std::string _question;
        std::string _answer;
    
    };

    class Login{
    public:

        void createUser(std::string& name, std::string& password, 
            std::string& email, std::string& question, std::string& answer);
        bool editUser(std::string& name);
        void showUser(std::string& name);
        bool login(std::string& name, std::string& password);
        bool logout();
        bool forgotpassword(std::string& name, std::string& password);
    
    private:
        std::vector<User> _users;
    };

#endif