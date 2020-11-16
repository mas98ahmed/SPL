#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

using namespace std;


class Session;

class Agent {
public:
    Agent();

    virtual ~Agent();//destructor
    virtual Agent *clone() const = 0;
    
    //methods
    virtual void act(Session &session) = 0;
    virtual bool isVirus() const = 0;

    //getters
    virtual int getNodeId() const = 0;
};

class ContactTracer : public Agent {
public:
    ContactTracer();
    
    ContactTracer(const ContactTracer &other);//copy ctr
    ~ContactTracer();//destructor
    Agent *clone() const;
    
    //methods
    virtual void act(Session &session);
    virtual bool isVirus() const;

    //getters
    virtual int getNodeId() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    
    Virus(const Virus &other);//copy ctr
    ~Virus();//destructor
    Agent *clone() const;
    
    //methods
    virtual void act(Session &session);
    virtual bool isVirus() const;

    //getters
    virtual int getNodeId() const;

private:
    const int nodeInd;
};

#endif
