#ifndef ALUNO_H
#define ALUNO_H

#include <iostream>
using namespace std;

class Aluno
{
private:
    int ra;
    std::string nome;

public:
    Aluno();
    Aluno(int ra, std::string nome);
    std::string getNome() const;
    int getRa() const;
};

#endif
