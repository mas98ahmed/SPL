#include "../Include/Graph.h"

Graph::Graph(vector<vector<int>> matrix) : edges(matrix) {
    InfectedNodes = vector<int>();
}

Graph::Graph() {}

bool Graph::isInfected(int nodeInd) {
    for (int i = 0; i < InfectedNodes.size(); i++) {
        if (InfectedNodes.at(i) == nodeInd) {
            return true;
        }
    }
    return false;
}

void Graph::infectNode(int nodeInd) {
    InfectedNodes.push_back(nodeInd);
}

vector<vector<int>> Graph::getEdges() const {
    return edges;
}