#include "../Include/Agent.h"
#include "../Include/Tree.h"

//Agent
Agent::Agent() {}

//===================================================================================
//ContactTracer

ContactTracer::ContactTracer() : Agent() {}

void ContactTracer::act(Session &session) {
    int nodeId = session.dequeueInfected();
    if (nodeId == -1) {
        Tree *tree = Tree::createTree(session, nodeId);
        int nodeTraced = tree->traceTree();
        vector<vector<int>> matrix = session.getGraph().getEdges();
        int neighborsSize = matrix[nodeTraced].size();
        for (int i = 0; i < neighborsSize; i++) {
            matrix[nodeTraced][i] = 0;
            matrix[i][nodeTraced] = 0;
        }
        session.setGraph(Graph(matrix));
    }
}

ContactTracer::ContactTracer(const ContactTracer &other) : Agent() {}

int ContactTracer::getNodeId() const { return -1; }

Agent *ContactTracer::clone() const { return new ContactTracer(*this); }

//===================================================================================
//Virus

Virus::Virus(int nodeInd) : nodeInd(nodeInd), Agent() {}

Virus::Virus(const Virus &other) : nodeInd(other.getNodeId()), Agent() {}

void Virus::act(Session &session) {
    session.enqueueInfected(nodeInd);
    int NeighborsSize = session.getGraph().getEdges()[nodeInd].size();
    bool stop = false;
    int i = 0;
    while (i < NeighborsSize && !stop) {
        if (!session.getGraph().isInfected(i)) {
            session.addAgent(new Virus(i));
            stop = true;
        }
        i++;
    }
}

int Virus::getNodeId() const { return nodeInd; }

Agent *Virus::clone() const { return new Virus(*this); }
