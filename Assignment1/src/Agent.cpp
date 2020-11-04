#include "../Include/Agent.h"

Agent::Agent(Session &session):session(session) {}

ContactTracer::ContactTracer(Session &session):Agent(session) {}
void ContactTracer::act() {}

Virus::Virus(int nodeInd, Session &session): nodeInd(nodeInd), Agent(session) {}
void Virus::act() {}


