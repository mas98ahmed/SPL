#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Session;

class Agent {
public:
    Agent(Session &session);

    virtual void act() = 0;

    virtual void addAgentVisit() = 0 const ;

    Session &getSession() const;

    virtual int getNodeId() const = 0;

protected:
    Session &session;
};

class ContactTracer : public Agent {
public:
    ContactTracer(Session &session);

    ContactTracer(ContactTracer &other);

    virtual void act();

    virtual void addAgentVisit();

    virtual int getNodeId() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd, Session &session);

    Virus(Virus &other);

    virtual void act();

    int getNode() const;

    virtual void addAgentVisit();

    virtual int getNodeId() const;

private:
    const int nodeInd;
};

#endif