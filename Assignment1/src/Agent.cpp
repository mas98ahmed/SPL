#include "../Include/Agent.h"
#include "../Include/Session.h"
#include "../Include/Tree.h"

#include <iostream>

using namespace std;

//Agent
Agent::Agent() {}

Agent::Agent(const Agent& other) {}

Agent& Agent::operator=(const Agent& other){}

Agent::Agent(const Agent&& other) {}

Agent& Agent::operator=(const Agent&& other){}

Agent::~Agent(){}

//===================================================================================
//ContactTracer

ContactTracer::ContactTracer() : Agent() {}

ContactTracer::ContactTracer(const ContactTracer& other) {}

ContactTracer& ContactTracer::operator=(const ContactTracer& other){}

ContactTracer::ContactTracer(const ContactTracer&& other) {}

ContactTracer& ContactTracer::operator=(const ContactTracer&& other){}

ContactTracer::~ContactTracer(){}

Agent *ContactTracer::clone() const { return new ContactTracer(*this); }

void ContactTracer::act(Session &session) {
    int nodeId = session.dequeueInfected();
    if (nodeId != -1) {
        Tree *tree = session.getGraph().BFS(session,nodeId);
        int nodeTraced = tree->traceTree();
        vector<vector<int>> matrix = session.getGraph().getEdges();
        int neighborsSize = matrix[nodeTraced].size();
        for (int i = 0; i < neighborsSize; i++) {
            matrix[nodeTraced][i] = 0;
            matrix[i][nodeTraced] = 0;
        }
        Graph g(matrix);
        g.setInfectedNodes(session.getGraph().getInfectedNodes());
        session.setGraph(g);
    }
}

int ContactTracer::getNodeId() const { return -1; }

bool ContactTracer::isVirus() const{ return false;}

//===================================================================================
//Virus

Virus::Virus(int nodeInd) : nodeInd(nodeInd){}

Virus::Virus(const Virus &other) : nodeInd(other.getNodeId()){}

Virus& Virus::operator=(const Virus& other){ nodeInd = other.nodeInd; }

Virus::Virus(const Virus &&other) : nodeInd(other.getNodeId()){}

Virus& Virus::operator=(const Virus&& other){ nodeInd = other.nodeInd;}

Agent *Virus::clone() const { return new Virus(*this); }

void Virus::act(Session &session) {
    if(!session.isenqueued(nodeInd)){
        session.enqueueInfected(nodeInd);
    }
    int NeighborsSize = session.getGraph().getEdges()[nodeInd].size();
    int i = 0;
    while (i < NeighborsSize) {
        if (!session.getGraph().isInfected(i) && session.getGraph().getEdges()[nodeInd][i] == 1) {
            session.addAgent(*(new Virus(i)));
            NeighborsSize = -1;
        }
        i++;
    }
}

int Virus::getNodeId() const { return nodeInd; }

bool Virus::isVirus() const{ return true;}
