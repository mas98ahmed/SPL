#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

using namespace std;


class Session;

class Agent {
public:
    Agent();

    virtual Agent *clone() const = 0;
    
    virtual ~Agent();

    virtual void act(Session &session) = 0;

    virtual int getNodeId() const = 0;
};

class ContactTracer : public Agent {
public:
    ContactTracer();

    ContactTracer(const ContactTracer &other);

    virtual Agent *clone() const;
    
    virtual void act(Session &session);

    virtual int getNodeId() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    Virus(const Virus &other);

    virtual Agent *clone() const;
    
    virtual void act(Session &session);

    virtual int getNodeId() const;

private:
    const int nodeInd;
};

#endif
