#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Session;
class Tree;

class Graph {
public:
    Graph(vector<vector<int>> matrix);
    Graph();

    //Methods
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree *BFS(const Session &session, int root);
    bool isTetminated(const Session &session);
    void setInfectedNodes(vector<int> InfectedNodes);

    //Getters
    vector<vector<int>> getEdges() const;
    vector<int> getInfectedNodes() const;

private:
    vector<vector<int>> edges;
    vector<int> InfectedNodes;
};

#endif
