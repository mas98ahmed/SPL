#ifndef SESSION_H_
#define SESSION_H_

#include "Graph.h"

#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;


class Agent;
class Graph;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const string& path);

    //Methods
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int node);
    int dequeueInfected();

    //Getters
    TreeType getTreeType() const;
    Graph getGraph() const;
    int getCycle() const;
    
private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    queue<int> InfectedNodes;
    int cycle;
};

#endif
