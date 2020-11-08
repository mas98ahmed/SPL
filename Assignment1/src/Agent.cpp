#include "../Include/Agent.h"

//Agent
Agent::Agent(Session &session) : session(session) {}

Session &Agent::getSession() const { return session; }

//===================================================================================
//ContactTracer

ContactTracer::ContactTracer(Session &session) : Agent(session) {}

void ContactTracer::act() {}

ContactTracer::ContactTracer(ContactTracer &other) : Agent(other.getSession()) {}

void ContactTracer::addAgentVisit() { session.addAgent(this); }

int ContactTracer::getNodeId() const {
    return -1;
}

//===================================================================================
//Virus

Virus::Virus(int nodeInd, Session &session) : nodeInd(nodeInd), Agent(session) {}

Virus::Virus(Virus &other) : nodeInd(other.getNode()), Agent(other.getSession()) {}

void Virus::act() {
    session.enqueueInfected(nodeInd);
    vector<int> neighbors = session.getGraph().getEdges().at(nodeInd);
    bool stop = false;
    int i = 0;
    while(i < neighbors.size() && !stop) {
        if (!session.getGraph().isInfected(i)) {
            session.addAgent(i);
            stop = true;
        }
        i++;
    }
}

void Virus::addAgentVisit() { session.addAgent(this); }

int Virus::getNode() const { return nodeInd; }

int Virus::getNodeId() const {
    return this->nodeInd;
}