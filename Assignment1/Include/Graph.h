#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Graph {
public:
    Graph(vector<vector<int>> matrix);
    Graph();

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    vector<vector<int>> getEdges() const;

private:
    vector<vector<int>> edges;
    vector<int> InfectedNodes;
};

#endif
