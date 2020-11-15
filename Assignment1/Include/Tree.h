#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <queue>
#include <vector>
#include "Session.h"

using namespace std;


class Session;

class Tree {
public:
    Tree(int rootLabel);

    //Rule of 5.
    Tree(const Tree &other);//copy ctr
    Tree &operator=(const Tree &other);//copy assign 
    Tree(const Tree &&other);//move ctr
    Tree &operator=(const Tree &&other);//move assign
    virtual ~Tree();//destrustor
    virtual Tree *clone() const = 0;
    void clear();

    //Methods
    static Tree *createTree(const Session &session, int rootLabel);
    void addChild(const Tree &child);
    virtual int traceTree() = 0;

    //getters
    vector<Tree *> getChildren() const;
    int getNode() const;

protected:
    int node;
    vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    //Rule of 5.
    CycleTree(const CycleTree &other);//copy ctr
    CycleTree &operator=(const CycleTree &other);//copy assign
    CycleTree(const CycleTree &&other);//move ctr
    CycleTree &operator=(const CycleTree &&other);//move assign
    virtual ~CycleTree();
    virtual Tree *clone() const;

    //Methods
    virtual int traceTree();

    //Getters
    int getCycle() const;
private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    //Rule of 5.
    MaxRankTree(const MaxRankTree &other);//copy ctr
    MaxRankTree &operator=(const MaxRankTree &other);//copy assign
    MaxRankTree(const MaxRankTree &&other);//move ctr
    MaxRankTree &operator=(const MaxRankTree &&other);//move assign
    virtual ~MaxRankTree();//destructor
    virtual Tree *clone() const;

    //Methods
    virtual int traceTree();
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    //Rule of 5.
    RootTree(const RootTree &other);//copy ctr
    RootTree &operator=(const RootTree &other);//copy assign
    RootTree(const RootTree &&other);//move ctr
    RootTree &operator=(const RootTree &&other);//move assign
    virtual ~RootTree();//destructor
    virtual Tree *clone() const;

    //Methods
    virtual int traceTree();
};

#endif
