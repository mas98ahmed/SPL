#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

using namespace std;


class Session;

class Agent {
public:
    Agent();

    //Rule of 5.
    Agent(const Agent &other);//copy ctr
    Agent& operator=(const Agent &other);//copy assign
    Agent(const Agent &&other);//move ctr
    Agent& operator=(const Agent &&other);//move assign
    ~Agent();//destructor
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
    
    //Rule of 5.
    ContactTracer(const ContactTracer &other);//copy ctr
    ContactTracer& operator=(const ContactTracer &other);//copy assign
    ContactTracer(const ContactTracer &&other);//move ctr
    ContactTracer& operator=(const ContactTracer &&other);//move assign
    ~ContactTracer();//destructor
    virtual Agent *clone() const;
    
    //methods
    virtual void act(Session &session);
    virtual bool isVirus() const;

    //getters
    virtual int getNodeId() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    //Rule of 5.
    Virus(const Virus &other);//copy ctr
    Virus& operator=(const Virus &other);//copy assign
    Virus(const Virus &&other);//move ctr
    Virus& operator=(const Virus &&other);//move assign
    ~Virus();//destructor
    virtual Agent *clone() const;
    
    //methods
    virtual void act(Session &session);
    virtual bool isVirus() const;

    //getters
    virtual int getNodeId() const;

private:
    const int nodeInd;
};

#endif
