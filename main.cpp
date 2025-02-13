#include "dht.h"
#include <iostream>

void runTests()
{
    std::cout << " INICIANDO TESTES \n";
    std::cout << "-----------------------\n";

    DHT dht;

    // Criando nós na DHT
    dht.addNode(100);
    dht.addNode(500);
    dht.addNode(2000);
    dht.addNode(4000);
    dht.addNode(7000);

    // 1 - Teste: Inserção e Recuperação de um Aluno
    std::cout << "\nTeste 1: Insercao e Recuperacao de um Aluno\n";
    Aluno alunoTeste1(150, "Ana");
    dht.insertAluno(alunoTeste1);

    Aluno alunoEncontrado;
    bool encontrado = false;
    for (auto &node : dht.getNodes())
    {
        if (node.retrieveKey(150, alunoEncontrado))
        {
            encontrado = true;
            break;
        }
    }

    if (encontrado)
        std::cout << "Aluno encontrado: " << alunoEncontrado.getNome() << "\n";
    else
        std::cout << "Erro: Aluno nao encontrado!\n";

    // ============================
    // 2 - Teste: Remoção de um Aluno
    // ============================
    std::cout << "\nTeste 2: Remocao de um Aluno\n";
    bool removido = false;
    for (auto &node : dht.getNodes())
    {
        if (node.deleteKey(150))
        {
            removido = true;
            break;
        }
    }

    if (removido)
        std::cout << "Aluno removido com sucesso!\n";
    else
        std::cout << "Erro ao remover o aluno!\n";

    // ============================
    // 3 - Teste: Busca de um RA Inexistente
    // ============================
    std::cout << "\nTeste 3: Busca de um RA Inexistente\n";
    encontrado = false;
    for (auto &node : dht.getNodes())
    {
        if (node.retrieveKey(9999, alunoEncontrado))
        {
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        std::cout << "Aluno nao encontrado (correto, pois nunca foi inserido).\n";
    else
        std::cout << "Erro: Aluno com RA inexistente foi encontrado!\n";

    // ============================
    // 4 - Teste: Verificação do Nó Correto
    // ============================
    std::cout << "\nTeste 4: Verificacao do No Correto\n";
    Aluno alunoTeste4(450, "Pedro");
    dht.insertAluno(alunoTeste4);

    int expectedNodeID = 500;
    int actualNodeID = -1;
    for (auto &node : dht.getNodes())
    {
        if (node.retrieveKey(450, alunoEncontrado))
        {
            actualNodeID = node.getNodeID();
            break;
        }
    }

    if (actualNodeID == expectedNodeID)
        std::cout << "RA=450 armazenado corretamente no no " << actualNodeID << "\n";
    else
        std::cout << "Erro: RA=450 deveria estar no no " << expectedNodeID
                  << " mas foi armazenado no no " << actualNodeID << "\n";

    // ============================
    // 5 - Teste: Remoção de um Nó e Realocação de Alunos
    // ============================
    std::cout << "\nTeste 5: Remocao de um No e Realocacao de Alunos\n";
    dht.addNode(6000); // Adiciona um nó intermediário para testar realocação
    dht.insertAluno(Aluno(5900, "Lucas")); // Deve ir para o nó 6000

    // Removendo o nó 6000 (Lucas deve ser realocado para 7000)
    dht.removeNode(6000);

    encontrado = false;
    for (auto &node : dht.getNodes())
    {
        if (node.retrieveKey(5900, alunoEncontrado))
        {
            encontrado = true;
            break;
        }
    }

    if (encontrado)
        std::cout << "Aluno Lucas realocado corretamente apos remocao do no 6000.\n";
    else
        std::cout << "Erro: Aluno Lucas nao foi encontrado apos remocao do no 6000.\n";

    std::cout << "\nTodos os testes concluidos.\n";
}


int main()
{
    DHT dht;

    // Adicionando nós
    dht.addNode(100);
    dht.addNode(500);
    dht.addNode(2000);
    dht.addNode(4000);
    dht.addNode(7000);

    // Inserindo alunos
    dht.insertAluno(Aluno(123, "Joao"));
    dht.insertAluno(Aluno(456, "Maria"));
    dht.insertAluno(Aluno(789, "Pedro"));
    dht.insertAluno(Aluno(1000, "Ana"));
    dht.insertAluno(Aluno(2001, "Carlos"));

    // Imprimindo o estado dos nós
    std::cout << "\nEstado final dos nos:\n";
    dht.printAllNodes();

    runTests();
    return 0;
}