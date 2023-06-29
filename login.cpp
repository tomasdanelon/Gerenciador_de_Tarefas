#include "login.hpp"
#include <algorithm>
#include <iostream>

User* LoginSystem::findUserByUsername(const std::string& username) {
    auto it = _users.find(username);
    if (it != _users.end()) {
        return &(it->second);
    } else {
        return nullptr; // Usuário não encontrado
    }
}

bool LoginSystem::createUser(const std::string& username, const std::string& password,
                        const std::string& email, const std::string& question,
                        const std::string& answer){
    //Verificação se o usuário já existe
    if (_users.find(username) != _users.end()) {
        std::cout << "Usuário já existe. Escolha um nome de usuário diferente.\n";
        return false;
    }

    //Verificação se o email já foi usado
    for (const auto& pair : _users) {
        const User& existingUser = pair.second;
        if (existingUser.getEmail() == email) {
            std::cout << "O email já foi utilizado por outro usuário. Use um email diferente.\n";
            return false;
        }
    }

    //Verificação se algum dado foi dado em branco
    if (username.empty() || password.empty() || email.empty() || question.empty() || answer.empty()) {
        std::cout << "Dados de usuário inválidos. Preencha todos os campos corretamente.\n";
        return false;
    }

     // Verificação de limite de caracteres
    constexpr int kUsernameMaxLength = 10;
    constexpr int kPasswordMaxLength = 15;
    constexpr int kEmailMaxLength = 50;
    constexpr int kQuestionMaxLength = 100;
    constexpr int kAnswerMaxLength = 50;

    if (username.length() > kUsernameMaxLength) {
        std::cout << "Nome de usuário excede o limite de " << kUsernameMaxLength << " caracteres.\n";
        return false;
    }

    if (password.length() > kPasswordMaxLength) {
        std::cout << "Senha excede o limite de " << kPasswordMaxLength << " caracteres.\n";
        return false;
    }

    if (email.length() > kEmailMaxLength) {
        std::cout << "Email excede o limite de " << kEmailMaxLength << " caracteres.\n";
        return false;
    }

    if (question.length() > kQuestionMaxLength) {
        std::cout << "Pergunta de segurança excede o limite de " << kQuestionMaxLength << " caracteres.\n";
        return false;
    }

    if (answer.length() > kAnswerMaxLength) {
        std::cout << "Resposta de segurança excede o limite de " << kAnswerMaxLength << " caracteres.\n";
        return false;
    }

    //Verifica se o email possui @ e um ponto no final 
    if (email.find('@') == std::string::npos || !std::regex_match(email, std::regex(".+\\..+"))) {
        std::cout << "Email inválido. Insira um email válido com o formato correto.\n";
        return false;
    }

    //Se tudo estiver correto, cria o user
    User newUser(password, email, question, answer);

    //Adiciona o user ao map
    _users.emplace(username, newUser);

    //Confirmação da criação
    std::cout << "Novo usuário criado com sucesso.\n";
    return true;
}

bool LoginSystem::login(const std::string& username, const std::string& password){
    // Verificar se já existe um usuário logado
    if (isLoggedIn) {
        std::cout << "Já existe um usuário logado. Faça logout!!\n";
        return false;
    }

    // Procurar usuário pelo username e obter objeto
    User* user = LoginSystem::findUserByUsername(username);

    // Caso não encontre
    if(user == nullptr){
        std::cout << "Usuário não encontrado" << std::endl;
        return false;
    }

    // Comparar a senha fornecida com a senha do usuário
    if ((PasswordHasher::calcularHash(password)) == user->getPassword()) {
        currentUsername = username;  // Definir o nome de usuário atual
        isLoggedIn = true;
        std::cout << "Login bem-sucedido. Bem-vindo, " << currentUsername << "!\n";
        return true;
    } else {
        std::cout << "Senha incorreta.\n";
        return false;
    }

    return false;
}

bool LoginSystem::logout(){
    // Verificar se há um usuário logado
    if (!isLoggedIn) {
        std::cout << "Nenhum usuário está logado.\n";
        return false;
    }

    std::cout << "Logout realizado para o usuário " << currentUsername << ".\n";
    currentUsername.clear();  // Limpar o nome de usuário atual
    isLoggedIn = false;
    return true;
}

bool LoginSystem::showUser(){
    // Verificar se há um usuário logado
    if (!isLoggedIn) {
        std::cout << "Nenhum usuário está logado." << std::endl;
        return false;
    }

    std::cout << "Usuário logado: " << currentUsername << std::endl;
    return true;
}

bool LoginSystem::editUser(const std::string& password, const int& choice, const std::string& change1, const std::string& change2){
    // Verificar se há um usuário logado
    if (!isLoggedIn) {
        std::cout << "Nenhum usuário está logado." << std::endl;
        return false;
    }

    // Verificar se a senha atual está correta
    if (_users[currentUsername].getPassword() != PasswordHasher::calcularHash(password)) {
        std::cout << "Senha incorreta. Não é possível editar o usuário." << std::endl;
        return false;
    }

    /*std::cout << "Selecione o que deseja editar:" << std::endl;
    std::cout << "1. Senha" << std::endl;
    std::cout << "2. Pergunta de segurança" << std::endl;
    std::cout << "0. Sair da edição" << std::endl;

    int choice;
    std::cin >> choice;

    while (choice != 0 && choice != 1 && choice != 2) {
        std::cout << "Opção inválida. Digite novamente: ";
        std::cin >> choice;
    }*/

    switch (choice) {
        case 0:
            std::cout << "Edição cancelada." << std::endl;
            return false;
        case 1:
        {
            /*std::string newPassword;
            std::cout << "Digite a nova senha: ";
            std::cin >> newPassword;*/

            // Verificação de limite de caracteres para a nova senha
            constexpr int kNewPasswordMaxLength = 30;

            if (change1.length() > kNewPasswordMaxLength) {
                std::cout << "A nova senha excede o limite de " << kNewPasswordMaxLength << " caracteres.\n";
                break;
            }

            _users[currentUsername].setPassword(change1);

            std::cout << "Senha alterada com sucesso para o usuário " << currentUsername << "." << std::endl;
            break;
        }
    case 2:
        {
            /*std::string newQuestion;
            std::cout << "Digite a nova pergunta de segurança: ";
            std::cin.ignore();  // Limpar o buffer de entrada
            std::getline(std::cin, newQuestion);*/

            // Verificação de limite de caracteres para a nova pergunta de segurança
            constexpr int kNewQuestionMaxLength = 100;

            if (change1.length() > kNewQuestionMaxLength) {
                std::cout << "A nova pergunta de segurança excede o limite de " << kNewQuestionMaxLength << " caracteres.\n";
                break;
            }

            /*std::string newAnswer;
            std::cout << "Digite a nova resposta da pergunta de segurança: ";
            std::cin.ignore();  // Limpar o buffer de entrada
            std::getline(std::cin, newAnswer);*/

            // Verificação de limite de caracteres para a nova pergunta de segurança
            constexpr int kNewAnswerMaxLength = 100;

            if (change2.length() > kNewAnswerMaxLength) {
                std::cout << "A nova reposta de segurança excede o limite de " << kNewQuestionMaxLength << " caracteres.\n";
                break;
            }

            _users[currentUsername].setQuestion(change1);
            _users[currentUsername].setAnswer(change2);

            std::cout << "Pergunta de segurança e resposta alteradas com sucesso para o usuário " << currentUsername << "." << std::endl;
            break;
        }
    }

    return true;
}

bool LoginSystem::deleteUser(const std::string& username, const std::string& password,
                            const std::string& email, const std::string& answer, const std::string& confirmation){
    // Verificar se o usuário está logado
    if (!isLoggedIn) {
        std::cout << "Nenhum usuário está logado no momento." << std::endl;
        return false;
    }

    std::string passwordHash = PasswordHasher::calcularHash(password);

    // Verificar se o usuário atual corresponde aos campos informados
    if (currentUsername != username ||
        _users[currentUsername].getPassword() != passwordHash ||
        _users[currentUsername].getEmail() != email ||
        _users[currentUsername].getAnswer() != answer) {
        std::cout << "Os campos informados não correspondem ao usuário atual." << std::endl;
        return false;
    }

    /* Solicitar a confirmação do usuário
    std::string confirmation;
    std::cout << "Digite 'DELETAR' para confirmar a exclusão do usuário: ";
    std::cin >> confirmation;*/

    // Verificar se a confirmação está correta
    if (confirmation != "DELETAR") {
        std::cout << "Exclusão cancelada. A confirmação não corresponde." << std::endl;
        return false;
    }

    // Excluir o usuário
    _users.erase(currentUsername);
    isLoggedIn = false;

    std::cout << "Usuário " << currentUsername <<" excluído com sucesso." << std::endl;
    currentUsername.clear();
    return true;
}

bool LoginSystem::forgotPassword(const std::string& username, const std::string& answer, const std::string& newPassword){
    // Verificar se o usuário está logado
    if (isLoggedIn) {
        std::cout << "Você já está logado. Faça logout antes de esquecer a senha." << std::endl;
        return false;
    }

    // Procurar usuário pelo username e obter objeto
    User* user = LoginSystem::findUserByUsername(username);

    // Caso não encontre
    if(user == nullptr){
        std::cout << "Usuário não encontrado" << std::endl;
        return false;
    }

    /* Solicitar a resposta à pergunta de segurança
    std::string answer;
    std::cout << "Responda à pergunta de segurança: " << it->second.getQuestion() << std::endl;
    std::cin >> answer;*/

    // Verificar se a resposta está correta
    if (answer != user->getAnswer()) {
        std::cout << "Resposta incorreta." << std::endl;
        return false;
    }

    /* Solicitar a nova senha
    std::string newPassword;
    std::cout << "Digite a nova senha: ";
    std::cin >> newPassword;*/

    // Atualizar a senha do usuário
    user->setPassword(newPassword);

    std::cout << "Senha atualizada com sucesso." << std::endl;
    return true;
}

