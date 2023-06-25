#include "login.hpp"
#include <algorithm>
#include <iostream>

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
    constexpr int kUsernameMaxLength = 20;
    constexpr int kPasswordMaxLength = 30;
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

    //Se tudo estiver correto, cria o user
    User newUser(password, email, question, answer);

    //Adiciona o user ao map
    _users.emplace(username, newUser);

    //Confirmação da criação
    std::cout << "Novo usuário criado com sucesso.\n";
    return true;
}

bool LoginSystem::login(const std::string& email, const std::string& password){
    // Verificar se já existe um usuário logado
    if (isLoggedIn) {
        std::cout << "Já existe um usuário logado. Faça logout!!\n";
        return false;
    }

    // Procurar o usuário pelo email
    auto it = std::find_if(_users.begin(), _users.end(),
    [&](const auto& userPair) {
    return userPair.second.getEmail() == email;
    });

    // Verificar se o usuário foi encontrado
    if (it == _users.end()) {
        std::cout << "Usuário não encontrado.\n";
        return false;
    }

    // Obter o objeto User correspondente ao email
    const User& user = it->second;

    // Comparar a senha fornecida com a senha do usuário
    if ((PasswordHasher::calcularHash(password)) == user.getPassword()) {
        currentUsername = it->first;  // Definir o nome de usuário atual
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

bool LoginSystem::editUser(){
    // Verificar se há um usuário logado
    if (!isLoggedIn) {
        std::cout << "Nenhum usuário está logado." << std::endl;
        return false;
    }

    std::string currentPassword;
    std::cout << "Digite a senha atual: ";
    std::cin >> currentPassword;

    // Verificar se a senha atual está correta
    if (_users[currentUsername].getPassword() != PasswordHasher::calcularHash(currentPassword)) {
        std::cout << "Senha incorreta. Não é possível editar o usuário." << std::endl;
        return false;
    }

    std::cout << "Selecione o que deseja editar:" << std::endl;
    std::cout << "1. Senha" << std::endl;
    std::cout << "2. Pergunta de segurança" << std::endl;
    std::cout << "0. Sair da edição" << std::endl;

    int choice;
    std::cin >> choice;

    while (choice != 0 && choice != 1 && choice != 2) {
        std::cout << "Opção inválida. Digite novamente: ";
        std::cin >> choice;
    }

    switch (choice) {
        case 0:
            std::cout << "Edição cancelada." << std::endl;
            return false;
        case 1:
        {
            std::string newPassword;
            std::cout << "Digite a nova senha: ";
            std::cin >> newPassword;

            // Verificação de limite de caracteres para a nova senha
            constexpr int kNewPasswordMaxLength = 30;

            if (newPassword.length() > kNewPasswordMaxLength) {
                std::cout << "A nova senha excede o limite de " << kNewPasswordMaxLength << " caracteres.\n";
                break;
            }

            _users[currentUsername].setPassword(PasswordHasher::calcularHash(newPassword));

            std::cout << "Senha alterada com sucesso para o usuário " << currentUsername << "." << std::endl;
            break;
        }
    case 2:
        {
            std::string newQuestion;
            std::cout << "Digite a nova pergunta de segurança: ";
            std::cin.ignore();  // Limpar o buffer de entrada
            std::getline(std::cin, newQuestion);

            // Verificação de limite de caracteres para a nova pergunta de segurança
            constexpr int kNewQuestionMaxLength = 100;

            if (newQuestion.length() > kNewQuestionMaxLength) {
                std::cout << "A nova pergunta de segurança excede o limite de " << kNewQuestionMaxLength << " caracteres.\n";
                break;
            }

            std::string newAnswer;
            std::cout << "Digite a nova resposta da pergunta de segurança: ";
            std::cin.ignore();  // Limpar o buffer de entrada
            std::getline(std::cin, newAnswer);

            // Verificação de limite de caracteres para a nova pergunta de segurança
            constexpr int kNewAnswerMaxLength = 100;

            if (newAnswer.length() > kNewAnswerMaxLength) {
                std::cout << "A nova reposta de segurança excede o limite de " << kNewQuestionMaxLength << " caracteres.\n";
                break;
            }

            _users[currentUsername].setQuestion(newQuestion);
            _users[currentUsername].setAnswer(newAnswer);

            std::cout << "Pergunta de segurança e resposta alteradas com sucesso para o usuário " << currentUsername << "." << std::endl;
            break;
        }
    }

    return true;
}

bool LoginSystem::deleteUser(const std::string& username, const std::string& password,
                const std::string& email, const std::string& question,
                const std::string& answer){
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
        _users[currentUsername].getQuestion() != question ||
        _users[currentUsername].getAnswer() != answer) {
        std::cout << "Os campos informados não correspondem ao usuário atual." << std::endl;
        return false;
    }

    // Solicitar a confirmação do usuário
    std::string confirmation;
    std::cout << "Digite 'DELETAR' para confirmar a exclusão do usuário: ";
    std::cin >> confirmation;

    // Verificar se a confirmação está correta
    if (confirmation != "DELETAR") {
        std::cout << "Exclusão cancelada. A confirmação não corresponde." << std::endl;
        return false;
    }

    // Excluir o usuário
    _users.erase(currentUsername);
    isLoggedIn = false;

    std::cout << "Usuário" << currentUsername <<"excluído com sucesso." << std::endl;
    currentUsername.clear();
    return true;
}

bool LoginSystem::forgotpassword(const std::string& email){
    // Verificar se o usuário está logado
    if (isLoggedIn) {
        std::cout << "Você já está logado. Faça logout antes de esquecer a senha." << std::endl;
        return false;
    }

    // Verificar se o e-mail informado corresponde a algum usuário
    std::map<std::string, User>::iterator it = std::find_if(_users.begin(), _users.end(),
        [&](const std::pair<std::string, User>& userPair) {
            return userPair.second.getEmail() == email;
        }
    );  

    if (it == _users.end()) {
        std::cout << "O e-mail informado não está registrado." << std::endl;
        return false;
    }

        // Solicitar a resposta à pergunta de segurança
    std::string answer;
    std::cout << "Responda à pergunta de segurança: " << it->second.getQuestion() << std::endl;
    std::cin.ignore();
    std::getline(std::cin, answer);

    // Verificar se a resposta está correta
    if (answer != it->second.getAnswer()) {
        std::cout << "Resposta incorreta." << std::endl;
        return false;
    }

    // Solicitar a nova senha
    std::string newPassword;
    std::cout << "Digite a nova senha: ";
    std::cin >> newPassword;

    // Atualizar a senha do usuário
    it->second.setPassword(newPassword);

    std::cout << "Senha atualizada com sucesso." << std::endl;
    return true;
}

