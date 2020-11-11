#include "../Include/Graph.h"
#include "../Include/Tree.h"
#include "../Include/Session.h"

using namespace std;


Graph::Graph(vector<vector<int>> matrix) : edges(matrix), InfectedNodes(vector<int>()){}

Graph::Graph() : edges(vector<vector<int>>()), InfectedNodes(vector<int>()){}

//Methods
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

    vector<int> q;
    vector<Tree*> qTrees;

    q.push_back(root);
    qTrees.push_back(tree);

    int qNode;
    Tree* qTree;
    Tree* newTree;
    int vertexNum = edges.size();
    while (!q.empty()) {
        qNode = q[0];
        qTree = qTrees[0];

        q.erase(q.begin());
        qTrees.erase(qTrees.begin());


        for (int i = 0; i < vertexNum; i++) {
            if (edges[qNode][i] == 1 && (!visited[i])) {
                newTree = Tree::createTree(session,i);
                qTree->addChild(*newTree);
                q.push_back(i);
                qTrees.push_back(newTree);
                visited[i] = true;
            }
        }
    }
    return tree;
}

//Getters
vector<vector<int>> Graph::getEdges() const { return edges; }

vector<int> Graph::getInfectedNodes() const { return InfectedNodes; }
