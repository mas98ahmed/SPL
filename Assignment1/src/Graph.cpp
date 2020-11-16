#include "../Include/Graph.h"
#include "../Include/Tree.h"
#include "../Include/Session.h"


#include <iostream>
using namespace std;


Graph::Graph(vector<vector<int>> matrix) : edges(matrix), InfectedNodes(vector<int>()){}

Graph::Graph() : edges(vector<vector<int>>()), InfectedNodes(vector<int>()){}

Graph::~Graph(){ clear(); }

void Graph::clear(){
    int size = edges.size();
    for(int i = 0; i < size; i++){
        edges[i].clear();
    }
    edges.clear();
    InfectedNodes.clear();
}

bool Graph::isInfected(int nodeInd) {
    int size = InfectedNodes.size();
    for (int i = 0; i < size; i++) {
        if (InfectedNodes.at(i) == nodeInd) {
            return true;
        }
    }
    return false;
}

void Graph::infectNode(int nodeInd) { InfectedNodes.push_back(nodeInd); }

Tree *Graph::BFS(const Session &session, int root) {
    Tree *tree = Tree::createTree(session, root);
    //BFS...
    vector<bool> visited;
    int size = edges.size();
    for (int i = 0; i < size; i++) {
        visited.push_back(false);
    }
    visited[root] = true;
    //=============
    queue<Tree*> qTrees;
    //=============
    qTrees.push(tree);
    //=============
    Tree* qTree;
    //=============
    int vertexNum = edges.size();
    //=============
    while (!qTrees.empty()) {
        int qNode = qTrees.front()->getNode();
        qTree = qTrees.front();
        //======================
        qTrees.pop();
        //======================
        for (int i = 0; i < vertexNum; i++) {
            if (edges[qNode][i] == 1 && (!visited[i])) {
                Tree* newTree = Tree::createTree(session,i);
                qTree->addChild(*newTree);
                qTrees.push(qTree->getChildren().back());
                visited[i] = true;
            }
        }
    }
    return tree;
}

bool Graph::isTetminated(const Session &session){
    int size = edges.size();
    for(int node : InfectedNodes){
        for(int i = 0; i < size; i++){
            if(edges[node][i] == 1 && !session.isenqueued(i)){
                return false;
            }
        }
    }
    return true;
}

void Graph::setInfectedNodes(vector<int> InfectedNodes){
    this->InfectedNodes = InfectedNodes;
}

vector<vector<int>> Graph::getEdges() const { return edges; }

vector<int> Graph::getInfectedNodes() const { return InfectedNodes; }
