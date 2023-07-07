#ifndef USER_H
#define USER_H
#include <string>
#include <map>
#include "password_hasher.hpp"

/**
 * @class User
 * @brief Classe que representa um usuário no sistema de login.
 */
class User{
    /**
     * @brief Construtor da classe User.
     * @param password A senha do usuário.
     * @param email O email do usuário.
     * @param question A pergunta de segurança do usuário.
     * @param answer A resposta da pergunta de segurança do usuário.
     */
    public:
        /**
        * @brief Construtor da classe User.
        * @param password A senha do usuário.
        * @param email O email do usuário.
        * @param question A pergunta de segurança do usuário.
        * @param answer A resposta da pergunta de segurança do usuário.
        */
        User() = default;
        User(const std::string& password, const std::string& email,
            const std::string& question, const std::string& answer) 
            : _password(PasswordHasher::calcularHash(password)), _email(email), 
            _question(question), _answer(answer) {}

        /**
        * @brief Obtém a senha hashed do usuário.
        * @return A senha hashed do usuário.
        */
        const std::string& getPassword() const {
            return _password;
        }
        /**
        * @brief Obtém o email do usuário.
        * @return O email do usuário.
        */
        const std::string& getEmail() const {
            return _email;
        }

        /**
        * @brief Obtém a pergunta de segurança do usuário.
        * @return A pergunta de segurança do usuário.
        */
        const std::string& getQuestion() const {
            return _question;
        }

        /**
        * @brief Obtém a resposta da pergunta de segurança do usuário.
        * @return A resposta da pergunta de segurança do usuário.
        */
        const std::string& getAnswer() const {
            return _answer;
        }

        /**
        * @brief Define a senha do usuário sem o uso de hash.
        * @param password A senha do usuário sem hash.
        */
        void setPassword(const std::string& password) {
            _password = password;
        }

        /**
        * @brief Define o email do usuário.
        * @param email O novo email do usuário.
        */
        void setEmail(const std::string& email) {
            _email = email;
        }

        /**
        * @brief Define a pergunta de segurança do usuário.
        * @param password A nova pergunta de segurança do usuário.
        */
        void setQuestion(const std::string& question) {
            _question = question;
        }

         /**
        * @brief Define a resposta da pergunta de segurança do usuário.
        * @param password A nova resposta da pergunta de segurança do usuário.
        */
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