#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>

TEST_CASE("Registro de usuário") {

    SUBCASE("Registro de usuário inválido") {
        std::string name = "Luiza, Maria";
        std::string email = "Luiza";
        std::string password = "password123";
        std::string securityQuestion = "Qual é o nome do seu animal de estimação?";
        std::string securityAnswer = "Rex";

        registrationService.registrarUsuario(name, email, password, securityQuestion, securityAnswer);

        std::string userData = userRepository->getUserData(email);

        CHECK(userData.find("Name: " + name) != std::string::npos);
        CHECK(userData.find("Email: " + email) != std::string::npos);
        CHECK(userData.find("Password: " + PasswordHasher::calcularHash(password)) != std::string::npos);
        CHECK(userData.find("Security Question: " + securityQuestion) != std::string::npos);
        CHECK(userData.find("Security Answer: " + securityAnswer) != std::string::npos);
    }

    delete userRepository;
}

TEST_CASE("Autenticação de usuário") {
    UserRepository* userRepository = new FileUserRepository();
    UserRegistrationService registrationService(userRepository);
    UserAuthenticationService authenticationService(userRepository);

    SUBCASE("Autenticação de usuário válido") {
        std::string name = "John Doe";
        std::string email = "john@example.com";
        std::string password = "password123";
        std::string securityQuestion = "Qual é o nome do seu animal de estimação?";
        std::string securityAnswer = "Rex";

        registrationService.registrarUsuario(name, email, password, securityQuestion, securityAnswer);

        bool loginSuccess = authenticationService.realizarLogin(email, password);
        CHECK(loginSuccess == true);
    }

    SUBCASE("Autenticação de usuário inválido") {
        std::string name = "John Doe";
        std::string email = "john@example.com";
        std::string password = "password123";
        std::string securityQuestion = "Qual é o nome do seu animal de estimação?";
        std::string securityAnswer = "Rex";

        registrationService.registrarUsuario(name, email, password, securityQuestion, securityAnswer);

        bool loginSuccess = authenticationService.realizarLogin(email, "wrong_password");
        CHECK(loginSuccess == false);
    }

    delete userRepository;
}

TEST_CASE("Recuperação de senha") {
    UserRepository* userRepository = new FileUserRepository();
    UserRegistrationService registrationService(userRepository);
    UserPasswordRecoveryService passwordRecoveryService(userRepository);

    SUBCASE("Recuperação de senha com resposta correta") {
        // Cenário de teste: Resposta correta
        std::string name = "John Doe";
        std::string email = "john@example.com";
        std::string password = "password123";
        std::string securityQuestion = "Qual é o nome do seu animal de estimação?";
        std::string securityAnswer = "Rex";

        registrationService.registrarUsuario(name, email, password, securityQuestion, securityAnswer);

        // Simular o processo de recuperação de senha com resposta correta
        bool recoverySuccess = passwordRecoveryService.recuperarSenha(email, securityAnswer);
        CHECK(recoverySuccess == true);
    }

    SUBCASE("Recuperação de senha com resposta incorreta") {
        // Cenário de teste: Resposta incorreta
        std::string name = "John Doe";
        std::string email = "john@example.com";
        std::string password = "password123";
        std::string securityQuestion = "Qual é o nome do seu animal de estimação?";
        std::string securityAnswer = "Rex";

        registrationService.registrarUsuario(name, email, password, securityQuestion, securityAnswer);

        // Simular o processo de recuperação de senha com resposta incorreta
        bool recoverySuccess = passwordRecoveryService.recuperarSenha(email, "resposta_errada");
        CHECK(recoverySuccess == false);
    }

    delete userRepository;
}