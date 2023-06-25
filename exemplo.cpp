#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "password_hasher.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>

// Interface para persistência dos dados do usuário
class UserRepository {
public:
    virtual void saveUser(const std::string& userData) = 0;
    virtual std::string getUserData(const std::string& email) = 0;
};

// Implementação da persistência em arquivo
class FileUserRepository : public UserRepository {
public:
    void saveUser(const std::string& userData) override {
        std::ofstream arquivo("informacoes_login.txt", std::ios::app);
        if (!arquivo) {
            throw std::runtime_error("Não foi possível abrir o arquivo.");
        }
        arquivo << userData << std::endl;
        std::cout << "Usuário registrado com sucesso." << std::endl;
    }

    std::string getUserData(const std::string& email) override {
        std::ifstream arquivo("informacoes_login.txt");
        if (!arquivo) {
            throw std::runtime_error("Não foi possível abrir o arquivo.");
        }

        std::string line;
        while (std::getline(arquivo, line)) {
            if (line.find("Email: " + email) != std::string::npos) {
                std::string userData;
                std::getline(arquivo, userData);
                return userData;
            }
        }

        return "";
    }
};

// Serviço de registro de usuários
class UserRegistrationService {
private:
    UserRepository* userRepository;

public:
    UserRegistrationService(UserRepository* repository) : userRepository(repository) {}

    void registrarUsuario(const std::string& name, const std::string& email,
                          const std::string& password, const std::string& securityQuestion,
                          const std::string& securityAnswer) {
        std::string userData = "Name: " + name + "\n";
        userData += "Email: " + email + "\n";
        userData += "Password: " + PasswordHasher::calcularHash(password) + "\n";
        userData += "Security Question: " + securityQuestion + "\n";
        userData += "Security Answer: " + securityAnswer + "\n";

        userRepository->saveUser(userData);
    }
};

// Serviço de autenticação de usuários
class UserAuthenticationService {
private:
    UserRepository* userRepository;

public:
    UserAuthenticationService(UserRepository* repository) : userRepository(repository) {}

    bool realizarLogin(const std::string& email, const std::string& password) {
        std::string userData = userRepository->getUserData(email);
        if (!userData.empty()) {
            std::string hashSenha = userData.substr(userData.find("Password: ") + 10);
            std::string senhaInformada = PasswordHasher::calcularHash(password);
            return (hashSenha == senhaInformada);
        }
        return false;
    }
};

TEST_CASE("Registro de usuário") {
    UserRepository* userRepository = new FileUserRepository();
    UserRegistrationService registrationService(userRepository);

    SUBCASE("Registro de usuário válido") {
        std::string name = "John Doe";
        std::string email = "john@example.com";
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

/*TEST_CASE("Recuperação de senha") {
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
}*/