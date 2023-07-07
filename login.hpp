#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>
#include <sstream>
#include "user.hpp"

/**
 * @class LoginSystem
 * @brief Classe que representa o sistema de login.
 */
class LoginSystem{
    public:
        LoginSystem() : isLoggedIn(false) {} // Construtor

        /**
        * @brief Cria um novo usuário no sistema de login.
        * @param username O nome de usuário do novo usuário.
        * @param password A senha do novo usuário.
        * @param email O email do novo usuário.
        * @param question A pergunta de segurança do novo usuário.
        * @param answer A resposta da pergunta de segurança do novo usuário.
        * @return true se o usuário foi criado com sucesso, false caso contrário.
        */
        bool createUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& question,
                        const std::string& answer);

        /**
        * @brief Realiza o login de um usuário no sistema de login.
        * @return true se o login foi bem-sucedido, false caso contrário.
        */
        bool login();

        /**
        * @brief Realiza o logout do usuário atual no sistema de login.
        * @return true se o logout foi realizado com sucesso, false caso contrário.
        */
        bool logout();

        /**
        * @brief Exibe o nome de usuário do usuário atualmente logado.
        * @return true se o nome de usuário foi exibido com sucesso, false caso contrário.
        */
        bool showUser();

        /**
        * @brief Edita as informações do usuário atualmente logado.
        * @return true se as informações foram editadas com sucesso, false caso contrário.
        */
        bool editUser();

        /**
        * @brief Exclui o usuário atualmente logado do sistema de login.
        * @return true se o usuário foi excluído com sucesso, false caso contrário.
        */
        bool deleteUser();

        /**
        * @brief Recupera a senha do usuário caso tenha sido esquecida.
        * @return true se a senha foi recuperada com sucesso, false caso contrário.
        */
        bool forgotPassword();

        /**
        * @brief Verifica se um usuário com o nome de usuário fornecido já existe.
        * @param username O nome de usuário a ser verificado.
        * @return Um ponteiro para o usuário se encontrado, nullptr caso contrário.
        */
        User* findUserByUsername(const std::string& username);

        /**
        * @brief Verifica se uma string excede o tamanho máximo especificado.
        * @param maxLength O tamanho máximo permitido.
        * @param field A string a ser verificada.
        * @return true se a string excede o tamanho máximo, false caso contrário.
        */
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

/**
 * @class SaveFile
 * @brief Classe responsável por salvar e carregar os dados do sistema de login em um arquivo.
 */
class SaveFile{
    /**
     * @brief Construtor da classe SaveFile.
     * @param filename O nome do arquivo onde os dados serão salvos ou carregados.
     */
    public:
        SaveFile(const std::string& filename) : _filename(filename), _file(filename){}

        /**
        * @brief Salva os dados do sistema de login em um arquivo.
        * @param login O sistema de login contendo os dados a serem salvos.
        * @return true se os dados foram salvos com sucesso, false caso contrário.
        */
        bool save(LoginSystem& login);

        /**
        * @brief Carrega os dados do sistema de login a partir de um arquivo.
        * @param login O sistema de login onde os dados serão carregados.
        * @return true se os dados foram carregados com sucesso, false caso contrário.
        */
        bool load(LoginSystem& login);

        static std::string getValue(const std::string& line);
    
    private:
        std::string _filename;
        std::ifstream _file;
};

#endif