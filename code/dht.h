// dht.h
#ifndef DHT_H
#define DHT_H

#include <vector>
#include <map>
#include "aluno.h"

class DHTNode
{
private:
    int nodeID;
    std::map<int, Aluno> keyValueStore;

public:
    DHTNode(int id);
    void insertKey(const Aluno &aluno);
    bool retrieveKey(int ra, Aluno &aluno) const;
    bool deleteKey(int ra);
    void printNode() const;
    int getNodeID() const;
};

class DHT
{
private:
    std::vector<DHTNode> nodes;

public:
    void addNode(int id);
    void insertAluno(const Aluno &aluno);
    void printAllNodes() const;
    void removeNode(int id);  // Adicionado para remover nós
    std::vector<DHTNode> &getNodes(); // Adicionado para acesso aos nós
};

#endif
