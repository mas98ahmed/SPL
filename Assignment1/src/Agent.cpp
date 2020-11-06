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

//===================================================================================
//Virus

Virus::Virus(int nodeInd, Session &session) : nodeInd(nodeInd), Agent(session) {}

Virus::Virus(Virus &other) : nodeInd(other.getNode()), Agent(other.getSession()) {}

void Virus::act() {}

void Virus::addAgentVisit() { session.addAgent(this); }

int Virus::getNode() const { return nodeInd; }