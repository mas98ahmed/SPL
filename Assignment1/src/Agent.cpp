#include "../Include/Agent.h"
#include "../Include/Session.h"
#include "../Include/Tree.h"

#include <iostream>

using namespace std;

//Agent
Agent::Agent() {}

Agent::~Agent(){}

//===================================================================================
//ContactTracer

ContactTracer::ContactTracer() : Agent() {}

void ContactTracer::act(Session &session) {
    cout<<"ContactTracer"<<endl;
    int nodeId = session.dequeueInfected();
    if (nodeId != -1) {
        Tree *tree = session.getGraph().BFS(session,nodeId);
        int nodeTraced = tree->traceTree();
        cout<<nodeTraced<<" traced node"<<endl;
        vector<vector<int>> matrix = session.getGraph().getEdges();
        int neighborsSize = matrix[nodeTraced].size();
        for (int i = 0; i < neighborsSize; i++) {
            matrix[nodeTraced][i] = 0;
            matrix[i][nodeTraced] = 0;
        }
        cout<<"InfectedNodes before: "<<session.getGraph().getInfectedNodes().size()<<endl;
        Graph g(matrix);
        g.setInfectedNodes(session.getGraph().getInfectedNodes());
        session.setGraph(g);
        cout<<"InfectedNodes after: "<<session.getGraph().getInfectedNodes().size()<<endl;
    }
}

ContactTracer::ContactTracer(const ContactTracer &other){}

int ContactTracer::getNodeId() const { return -1; }

Agent *ContactTracer::clone() const { return new ContactTracer(*this); }

bool ContactTracer::isVirus() const{ return false;}

//===================================================================================
//Virus

Virus::Virus(int nodeInd) : nodeInd(nodeInd){}

Virus::Virus(const Virus &other) : nodeInd(other.getNodeId()){}

void Virus::act(Session &session) {
    cout<<nodeInd<<" Virus"<<endl;
    if(!session.isenqueued(nodeInd)){
        session.enqueueInfected(nodeInd);
    }
    int NeighborsSize = session.getGraph().getEdges()[nodeInd].size();
    int i = 0;
    while (i < NeighborsSize) {
        if (!session.getGraph().isInfected(i) && session.getGraph().getEdges()[nodeInd][i] == 1) {
            cout<<"InfectedNodes in virus before: "<<session.getGraph().getInfectedNodes().size()<<endl;
            session.addAgent(*(new Virus(i)));
            cout<<"InfectedNodes in virus after: "<<session.getGraph().getInfectedNodes().size()<<endl;
            NeighborsSize = -1;
            cout<<i<<" Holding new Virus"<<endl;
        }
        i++;
    }
}

int Virus::getNodeId() const { return nodeInd; }

Agent *Virus::clone() const { return new Virus(*this); }

bool Virus::isVirus() const{ return true;}
