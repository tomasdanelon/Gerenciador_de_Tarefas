#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "login.hpp"
#include "task_manager.cpp"

int main(){
    LoginSystem log_in;
    TaskManager task_manager;
    SaveFile saveFile("user_data.txt");

    std::ifstream file("user_data.txt");
    if (!file.peek()) {
    std::cout << "O arquivo está em branco. Não é possível carregar os dados." << std::endl;
    }else{
        saveFile.load(log_in);
    }

    int choice=1;
    int choice1=1;
    int tarefas=0;
    int logado=0;
    bool sucesso;

    std::cout << "Bem vindo ao sistema de gerenciamento de tarefas!" << std::endl
    << "Para utilizar o sistema você deve entrar em sua conta primeiro." << std::endl;

// Menu do usuário ainda não logado
while (choice != 0 && logado != 1){

    std::cout << "Escolha uma das opções abaixo:" << std::endl
    << "1-Logar;" << std::endl
    << "2-Criar nova conta;" << std::endl
    << "3-Esqueci minha senha;" << std::endl
    << "0-Sair do programa" << std::endl;

    std::cin >> choice;

    while (choice != 0 && choice != 1 && choice != 2 && choice != 3)  {
        std::cout << "Opção inválida. Digite novamente: ";
        std::cin >> choice;
    }

        switch (choice) {
            case 0:{
                break;}

            case 1:{
                sucesso = log_in.login();

                if(sucesso){
                    logado=1;
                }else{
                    std::cout << "Tente Novamente" << std::endl;
                }

                break;}

            case 2:{
                std::string username, password, email, question, answer;
                std::cout << "Insira o username: ";
                std::cin.ignore();
                std::getline(std::cin, username);
                std::cout << "Insira a senha: ";
                std::cin >> password;
                std::cout << "Insira o email: ";
                std::cin >> email;
                std::cout << "Insira a pergunta de segurança: ";
                std::cin >> question;
                std::cout << "Insira a resposta da pergunta de segurança: ";
                std::cin >> answer;

                log_in.createUser(username, password, email, question, answer);
                break;}

            case 3:{
                log_in.forgotPassword();
                break;}
        }
}

// Menu do usuário logado
while (logado != 0 && choice1 != 0){

    std::cout << "Escolha uma das opções abaixo:" << std::endl
    << "1-Logout;" << std::endl
    << "2-Editar dados do usuário;" << std::endl
    << "3-Mostrar usuário logado;" << std::endl
    << "4-Deletar usuário atual;" << std::endl
    << "5-Ir para menu de tarefas;" << std::endl
    << "0-Sair do programa" << std::endl;

    std::cin >> choice1;

    while (choice1 != 0 && choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4 && choice1 != 5)  {
        std::cout << "Opção inválida. Digite novamente: ";
        std::cin >> choice1;
    }

        switch (choice1) {
            case 0:{
                break;}

            case 1:{
                log_in.logout();
                logado=0;
                break;}

            case 2:{
                log_in.editUser();
                break;}

            case 3:{
                log_in.showUser();
                break;}

            case 4:{
                sucesso = log_in.deleteUser();
                if(sucesso){
                    logado=0;
                }else{
                    std::cout << "Tente Novamente" << std::endl;
                }
                break;}

            case 5:{
                task_manager.use(task_manager);
                break;}
        }
}
    saveFile.save(log_in);
    std::cout << "Obrigado por utilizar o programa!" << std::endl;
    return 0;
}
