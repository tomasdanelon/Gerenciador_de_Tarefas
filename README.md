# Gerenciador_de_Tarefas
Sistema para gerenciar tarefas e compromissos de um usuário, desenvolvido para o trabalho final da disciplina Programação e Desenvolvimento de Software II.

O sistema tem como objetivo guardar tarefas para um usuário.

Como nosso objetivo é fazer com que o usuário guarde suas tarefas, é utilizado um sistema de salvamento por meio de usuários e uma lista de tarefas que é atrelada ao usuário quando logado, podendo alternar entre usuários por um sistema de login e logout.

# Classe_User
A classe user é a classe responsável por armazenar os dados do usuário.

A classe user possui apenas gets, sets e o construtor do User que é responsável por criar o usuário já com a senha hashed. O set da password não possui o cálculo do hash apenas para que a função de carregamento não utilize o hash na senha já salva com hash em seu arquivo.

# Classe_Login
A classe login é a classe responsável por fazer todas as ações relacionadas ao usuário e ao login.

A classe login possui nove métodos sendo eles:

Create User - Pede os dados necessários para criar uma conta, ele checa se o username já foi escolhido e se o email possui "@" e ".com", além de utilizar a classe check length em cada dado informado pelo usuario. 
Login - Pede o username e senha do usuario já criado, ele utiliza findByUsername e checa se a senha, com o hash aplicado, é igual a senha guardada dentro do arquivo.
Logout - Desloga o usuário e finaliza o programa.
Show User - Mostra qual usuário atualmente logado.
Edit User - Pergunta qual campo voce deseja editar, senha ou pergunta de segurança, e após a confirmação da senha ele edita estes campos.
Delete user - Pede os dados do usuário e para que ele escreve a palavra "DELETAR" para confirmar a exclusão da conta.
Forgot password - Pergunta o nome de usuário e a resposta da pergunta de segurança para mudar a senha do usuário.
Find by username - Procura um usuário no vetor de usuários, classe feita pois havia muitas repetições no código.
Check Length - Confere se o tamanho do dado inserido é do tamanho permitido.

# Classe_Save_File
A classe Save File é a classe responsável por fazer as ações relacionadas a salvar e carregar os dados do usuário, além de ser feita no princípio RAII para não ocorrer vazamento de memória na manipulação de arquivos.

A classe save file possui quatro métodos sendo eles:

Construtor - Responsável por criar o arquivo com o nome passado.
Save - Responsável por salvar os dados do usuário.
Load - Responsável por ler os dados do usuário no arquivo de texto e inserir os usuários já salvos em sessões anteriores novamento no sistema.
get Value - Classe ajudante de load para funcionamento correto.

# Classe_Password_hasher
A classe Password Hasher é responsável por calcular o hash da senha para criptografia.

A classe password hasher possuir apenas um método sendo:

Calcular hash - Responsáel por calcular o hash das senhas inseridas.

#Classe_Task
A classe Task é a classe responsável por salvar os dados das tarefas e ter os gets e sets.

A classe Task possui apenas gets e sets dos campos privados.

# Classe_Task_Manager
A classe Task Manager é responsável por fazer ações relacionadas as Tasks.

A classe task manager possui sete métodos:
Use - Responsável pela navegação no menu e utilização dos métodos e facilitar a classe Menu.
Add Notes - Responsável por adicionar a descrição da tarefa.
Add Task - Responsável por adicionar a tarefa na lista de tarefas.
Remove Task - Responsável por remover o vetor da lista de tarefas.
List Tasks - Responsável por mostrar a lista de tarefas.
Sort Tasks By Priority - Responsável por organizar as tarefas por ordem de prioridade.
Sort Tasks By Due Date - Responsável por organizar as tarefas por data.

# Classe_Menu
A classe Menu é responsável por utilizar as classes task manager e login.

A classe menu funciona como uma main e é para utilizar o sistema em si, possuindo vários switch cases para melhor funcionamento.
