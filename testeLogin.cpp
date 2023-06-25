#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "login.hpp"
#include <iostream>

// Inclua a definição da classe Login aqui

TEST_CASE("Teste da classe Login") {
    LoginSystem login;

    // Teste da função createUser
    SUBCASE("Teste da função createUser") {
        std::string username = "john_doe";
        std::string password = "123456";
        std::string email = "john.doe@example.com";
        std::string question = "Qual é o nome do seu animal de estimação?";
        std::string answer = "Rex";

        CHECK(login.createUser(username, password, email, question, answer) == true);
        CHECK(login.createUser(username, password, email, question, answer) == false); // Usuário já existe

        // Teste com campos em branco
        CHECK(login.createUser("", password, email, question, answer) == false);
        CHECK(login.createUser(username, "", email, question, answer) == false);
        CHECK(login.createUser(username, password, "", question, answer) == false);
        CHECK(login.createUser(username, password, email, "", answer) == false);
        CHECK(login.createUser(username, password, email, question, "") == false);
    }

    // Teste da função login
    SUBCASE("Teste da função login") {
        std::string email = "john.doe@example.com";
        std::string password = "123456";

        CHECK(login.login(email, password) == true);
        CHECK(login.login(email, "wrong_password") == false); // Senha incorreta
        CHECK(login.login("nonexistent@example.com", password) == false); // Usuário não encontrado

        // Teste com usuário já logado
        CHECK(login.login("another@example.com", "another_password") == false); // Já existe um usuário logado
    }

    // Teste da função logout
    SUBCASE("Teste da função logout") {
        CHECK(login.logout() == false); // Nenhum usuário está logado

        std::string email = "john.doe@example.com";
        std::string password = "123456";
        CHECK(login.login(email, password) == true);

        CHECK(login.logout() == true);
        CHECK(login.logout() == false); // Nenhum usuário está logado
    }

    // Teste da função showUser
    SUBCASE("Teste da função showUser") {
        CHECK(login.showUser() == false); // Nenhum usuário está logado

        std::string email = "john.doe@example.com";
        std::string password = "123456";
        CHECK(login.login(email, password) == true);

        CHECK(login.showUser() == true);
        CHECK(login.logout() == true);
        CHECK(login.showUser() == false); // Nenhum usuário está logado
    }

    // Teste da função editUser
    SUBCASE("Teste da função editUser") {
        CHECK(login.editUser() == false); // Nenhum usuário está logado

        std::string email = "john.doe@example.com";
        std::string password = "123456";
        CHECK(login.login(email, password) == true);

        CHECK(login.editUser() == true);
        CHECK(login.logout() == true);
        CHECK(login.editUser() == false); // Nenhum usuário está logado
    }

    // Teste da função deleteUser
    /*SUBCASE("Teste da função deleteUser") {
        std::string email = "john.doe@example.com";
        std::string password = "123456";
        CHECK(login.login(email, password) == true);

        CHECK(login.deleteUser() == true);
        CHECK(login.login(email, password) == false); // Usuário foi excluído

        // Tentativa de excluir um usuário inexistente
        CHECK(login.deleteUser() == false);
    }

    // Teste da função changePassword
    SUBCASE("Teste da função changePassword") {
        std::string email = "john.doe@example.com";
        std::string password = "123456";
        std::string newPassword = "new_password";
        CHECK(login.login(email, password) == true);

        CHECK(login.changePassword(password, newPassword) == true); // Alteração de senha bem-sucedida
        CHECK(login.login(email, password) == false); // Tentativa de login com a senha antiga falha
        CHECK(login.login(email, newPassword) == true); // Login com a nova senha bem-sucedido

        // Tentativa de alterar a senha sem estar logado
        CHECK(login.changePassword(password, newPassword) == false);
    }

    // Teste da função resetPassword
    SUBCASE("Teste da função resetPassword") {
        std::string email = "john.doe@example.com";
        std::string newPassword = "new_password";

        CHECK(login.resetPassword(email, newPassword) == true); // Reset de senha bem-sucedido
        CHECK(login.login(email, newPassword) == true); // Login com a nova senha bem-sucedido

        // Tentativa de resetar a senha de um usuário inexistente
        CHECK(login.resetPassword("nonexistent@example.com", newPassword) == false);
    }

    // Teste da função forgotPassword
    SUBCASE("Teste da função forgotPassword") {
        std::string email = "john.doe@example.com";
        std::string question = "Qual é o nome do seu animal de estimação?";
        std::string answer = "Rex";
        std::string newPassword = "new_password";

        CHECK(login.forgotPassword(email, question, answer, newPassword) == true); // Alteração de senha bem-sucedida
        CHECK(login.login(email, newPassword) == true); // Login com a nova senha bem-sucedido

        // Tentativa de alterar a senha com resposta incorreta à pergunta de segurança
        CHECK(login.forgotPassword(email, question, "wrong_answer", newPassword) == false);
    }

    // Teste da função editQuestion
    SUBCASE("Teste da função editQuestion") {
        std::string email = "john.doe@example.com";
        std::string password = "123456";
        std::string newQuestion = "Qual é a sua cor favorita?";
        std::string answer = "Rex";

        CHECK(login.login(email, password) == true);

        CHECK(login.editQuestion(newQuestion, answer) == true); // Edição da pergunta de segurança bem-sucedida

        // Tentativa de edição da pergunta sem estar logado
        CHECK(login.logout() == true);
        CHECK(login.editQuestion(newQuestion, answer) == false);
    }

    // Teste da função editAnswer
    SUBCASE("Teste da função editAnswer") {
        std::string email = "john.doe@example.com";
        std::string password = "123456";
        std::string question = "Qual é a sua cor favorita?";
        std::string newAnswer = "Azul";

        CHECK(login.login(email, password) == true);

        CHECK(login.editAnswer(question, newAnswer) == true); // Edição da resposta da pergunta de segurança bem-sucedida

        // Tentativa de edição da resposta sem estar logado
        CHECK(login.logout() == true);
        CHECK(login.editAnswer(question, newAnswer) == false);
    }

    // Teste da função isLoggedIn
    SUBCASE("Teste da função isLoggedIn") {
        CHECK(login.isLoggedIn() == false); // Nenhum usuário está logado

        std::string email = "john.doe@example.com";
        std::string password = "123456";
        CHECK(login.login(email, password) == true);

        CHECK(login.isLoggedIn() == true); // Um usuário está logado

        CHECK(login.logout() == true);
        CHECK(login.isLoggedIn() == false); // Nenhum usuário está logado
    }*/
}