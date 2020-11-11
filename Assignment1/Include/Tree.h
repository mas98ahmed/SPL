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

    //Rule of 3.
    Tree(const Tree &other);
    virtual Tree *clone() const = 0;
    Tree &operator=(const Tree &other);
    void clear();
    virtual ~Tree();

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

    //Rule of 3.
    CycleTree(const CycleTree &other);
    virtual Tree *clone() const;
    virtual ~CycleTree();

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

    //Rule of 3.
    MaxRankTree(const MaxRankTree &other);
    virtual Tree *clone() const;
    virtual ~MaxRankTree();

    //Methods
    virtual int traceTree();
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    //Rule of 3.
    RootTree(const RootTree &other);
    virtual Tree *clone() const;
    virtual ~RootTree();

    //Methods
    virtual int traceTree();
};

#endif
