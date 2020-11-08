#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "json.hpp"
#include "Agent.h"
#include <fstream>
#include <queue>

using namespace std;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const string& path);

    void simulate();
    void addAgent(const Agent& agent);
    void addAgent(Agent* agent);
    void setGraph(const Graph& graph);
    Graph getGraph() const;
    void enqueueInfected(int node);
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    queue<int> InfectedNodes;
};

#endif
