// dht.cpp
#include "dht.h"
#include <iostream>
#include <algorithm>

DHTNode::DHTNode(int id) : nodeID(id) {}

void DHTNode::insertKey(const Aluno &aluno)
{
    keyValueStore[aluno.getRa()] = aluno;
    std::cout << "Aluno " << aluno.getNome() << " armazenado no no " << nodeID << std::endl;
}

bool DHTNode::retrieveKey(int ra, Aluno &aluno) const
{
    auto it = keyValueStore.find(ra);
    if (it != keyValueStore.end())
    {
        aluno = it->second;
        return true;
    }
    return false;
}

bool DHTNode::deleteKey(int ra)
{
    auto it = keyValueStore.find(ra);
    if (it != keyValueStore.end())
    {
        keyValueStore.erase(it);
        std::cout << "Aluno com RA " << ra << " removido do no " << nodeID << std::endl;
        return true;
    }
    return false;
}

void DHTNode::printNode() const
{
    std::cout << "No " << nodeID << " armazenando: ";
    for (const auto &pair : keyValueStore)
    {
        std::cout << "[" << pair.first << " -> " << pair.second.getNome() << "] ";
    }
    std::cout << std::endl;
}

int DHTNode::getNodeID() const
{
    return nodeID;
}

void DHT::addNode(int id)
{
    nodes.emplace_back(id);
    std::sort(nodes.begin(), nodes.end(), [](const DHTNode &a, const DHTNode &b)
              { return a.getNodeID() < b.getNodeID(); });
}

void DHT::insertAluno(const Aluno &aluno)
{
    int ra = aluno.getRa();
    for (auto &node : nodes)
    {
        if (ra <= node.getNodeID())
        {
            node.insertKey(aluno);
            return;
        }
    }
    nodes.back().insertKey(aluno);
}

void DHT::removeNode(int id)
{
    auto it = std::find_if(nodes.begin(), nodes.end(), [id](const DHTNode &node)
                           { return node.getNodeID() == id; });

    if (it != nodes.end())
    {
        nodes.erase(it);
        std::cout << "No " << id << " removido da rede.\n";
    }
    else
    {
        std::cout << "Erro: No " << id << " nao encontrado.\n";
    }
}

std::vector<DHTNode> &DHT::getNodes()
{
    return nodes;
}

void DHT::printAllNodes() const
{
    for (const auto &node : nodes)
    {
        node.printNode();
    }
}
