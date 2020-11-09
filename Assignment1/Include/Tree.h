#ifndef TREE_H_
#define TREE_H_

#include "../Include/Session.h"

#include <iostream>
#include <queue>
#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel);

    Tree(const Tree &tree);

    virtual Tree *clone() const = 0;

    Tree &operator=(const Tree &tree);

    virtual ~Tree();

    void clear();

    int getNode() const;

    void addChild(const Tree &child);

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    vector<Tree *> getChildren() const;

protected:
    int node;
    vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    CycleTree(const CycleTree &other);

    virtual Tree *clone() const;

    virtual ~CycleTree();

    virtual int traceTree();

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    MaxRankTree(const MaxRankTree &other);

    virtual ~MaxRankTree();
    virtual Tree *clone() const;

    virtual int traceTree();
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    RootTree(const RootTree &other);

    virtual Tree *clone() const;

    virtual ~RootTree();

    virtual int traceTree();
};

#endif