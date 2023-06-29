#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "login.hpp"
#include <iostream>

// Inclua a definição da classe Login aqui

TEST_CASE("Teste da classe Login") {
    LoginSystem log_in;
    std::cout << "\nTestando forgotPassword\n\n";
    std::string username = "anaC";
    std::string password = "123456";
    std::string email = "anaC@example.com";
    std::string question = "Qual é o nome do seu animal de estimação?";
    std::string answer = "Rex";

    // Teste da função createUser
    SUBCASE("Teste da função createUser") {
        std::cout << "\nTestando criação\n\n";
        std::string username = "anaC";
        std::string password = "123456";
        std::string email = "anaC@example.com";
        std::string question = "Qual é o nome do seu animal de estimação?";
        std::string answer = "Rex";

        CHECK(log_in.createUser(username, password, email, question, answer) == true);
        CHECK(log_in.createUser(username, password, email, question, answer) == false); // Usuário já existe
        
        // Teste com campos em branco
        CHECK(log_in.createUser("", password, email, question, answer) == false);
        CHECK(log_in.createUser(username, "", email, question, answer) == false);
        CHECK(log_in.createUser(username, password, "", question, answer) == false);
        CHECK(log_in.createUser(username, password, email, "", answer) == false);
        CHECK(log_in.createUser(username, password, email, question, "") == false);
    }

    log_in.createUser(username, password, email, question, answer);

    // Teste da função login
    SUBCASE("Teste da função login") {
        CHECK(log_in.login(username, password) == true); // Teste comum
        log_in.logout();
        CHECK(log_in.login(username, "wrong_password") == false); // Senha incorreta
        log_in.logout();
        CHECK(log_in.login("nonexistent", password) == false); // Usuário não encontrado

        // Teste com usuário já logado
        CHECK(log_in.login("another", "another_password") == false); // Já existe um usuário logado
    }

    // Teste da função logout
    SUBCASE("Teste da função logout") {
        CHECK(log_in.logout() == false); // Nenhum usuário está logado

        CHECK(log_in.login(username, password) == true);

        CHECK(log_in.logout() == true);
        CHECK(log_in.logout() == false); // Nenhum usuário está logado
    }

    // Teste da função showUser
    SUBCASE("Teste da função showUser") {
        CHECK(log_in.showUser() == false); // Nenhum usuário está logado

        CHECK(log_in.login(username, password) == true);

        CHECK(log_in.showUser() == true);
        CHECK(log_in.logout() == true);
        CHECK(log_in.showUser() == false); // Nenhum usuário está logado
    }

    // Teste da função editUser
    SUBCASE("Teste da função editUser") {
        int choice = 1;

        CHECK(log_in.editUser(password, choice, "123456", "0") == false); // Nenhum usuário está logado

        CHECK(log_in.login(username, password) == true);

        CHECK(log_in.editUser(password, choice, password, "0") == true);
        choice = 2;
        CHECK(log_in.editUser(password, choice, "Qual a cor do céu?", "Azul") == true);
        CHECK(log_in.logout() == true);
        choice= 1;
        CHECK(log_in.editUser(password, choice, "123456", "0") == false); // Nenhum usuário está logado
    }

    // Teste da função deleteUser
    SUBCASE("Teste da função deleteUser") {        
        CHECK(log_in.login(username, password) == true);

        CHECK(log_in.deleteUser(username, password, email, answer, "DELETAR") == true);
        CHECK(log_in.login(username, password) == false); // Usuário foi excluído

        // Tentativa de excluir um usuário inexistente
        CHECK(log_in.deleteUser(username, password, email, answer, "DELETAR") == false);
    }

    // Teste da função forgotPassword
    SUBCASE("Teste da função forgotPassword") {
        CHECK(log_in.forgotPassword(username, "Rex", "123456") == true); // Alteração de senha bem-sucedida
        CHECK(log_in.login(username, password) == true); // Login com a nova senha bem-sucedido

        log_in.logout();
        // Tentativa de alterar a senha com resposta incorreta à pergunta de segurança
        CHECK(log_in.forgotPassword(username, "Re", "123456") == false);
    }
}