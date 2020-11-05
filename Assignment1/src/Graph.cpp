#include "../Include/Graph.h"

Graph::Graph(vector<vector<int>> matrix): edges(matrix){
    InfectedNodes = new vector<int>();
}

Graph::Graph() {}

bool Graph::isInfected(int nodeInd) {
    for (auto i = InfectedNodes->begin(); i != InfectedNodes->end(); ++i){
        if(*i == nodeInd){
            return true;
        }
    }
    return false;
}

void Graph::infectNode(int nodeInd) {
    InfectedNodes->push_back(nodeInd);
}
