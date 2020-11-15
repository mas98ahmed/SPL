#include "../Include/Tree.h"
#include "../Include/Session.h"
#include <iostream>

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree*>()) {};


Tree::Tree(const Tree &other): node(other.getNode()), children(vector<Tree*>()) {
    clear();
    int childrenSize = other.getChildren().size();
    for(int i=0;i< childrenSize;i++){
        children.push_back(other.getChildren()[i]->clone());
    }
};

Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        clear();
        node = other.node;
        int childrenSize = other.getChildren().size();
        for(int i=0;i< childrenSize;i++){
            children.push_back(other.getChildren()[i]->clone());
        }
    }
    return *this;
};

Tree::Tree(const Tree &other): node(other.getNode()), children(vector<Tree*>()) {
    clear();
    int childrenSize = other.getChildren().size();
    for(int i=0;i< childrenSize;i++){
        children.push_back(other.getChildren()[i]->clone());
    }
}

Tree &Tree::operator=(const Tree &&other) {
    if (this != &other)
    {
        clear();
        node = other.node;
        int childrenSize = other.getChildren().size();
        for (int i = 0; i < childrenSize; i++)
        {
            children.push_back(other.getChildren()[i]);
        }
        childrenSize = other.children.size();
        
        for (int i = 0; i < childrenSize; i++)
        {
            other.children[i]->clear();
            delete other.children[i];
        }
        other.children.clear();
    }
    return *this;
}

void Tree::clear() {
    int childrenSize = children.size();
    for (int i = 0; i < childrenSize; i++)
    {
        children[i]->clear();
        delete children[i];
    }
    children.clear();
}

Tree::~Tree() {
    int childrenSize = children.size();
    for(int i=0;i<childrenSize;i++){
        delete children[i];
    }
    children.clear();
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree *ans;
    switch (type) {
        case Cycle :
            ans = new CycleTree(rootLabel, session.getCycle());
            break;
        case MaxRank :
            ans = new MaxRankTree(rootLabel);
            break;
        case Root :
            ans = new RootTree(rootLabel);
            break;
    }
    return ans;
}

void Tree::addChild(const Tree &child) { children.push_back(child.clone()); }

int Tree::getNode() const { return node; }

vector<Tree *> Tree::getChildren() const { return children; }

//============================================================================================================

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.getCycle()) {}

Tree *CycleTree::clone() const { return new CycleTree(*this); }

CycleTree::~CycleTree() {}

int CycleTree::traceTree() {
    Tree *curr = this;
    while (currCycle > 0 && curr->getChildren().size() > 0) {
        curr = curr->getChildren()[0];
        currCycle--;
    }
    return curr->getNode();
}

int CycleTree::getCycle() const { return currCycle; }

//============================================================================================================

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {}

Tree *MaxRankTree::clone() const { return new MaxRankTree(*this); }

MaxRankTree::~MaxRankTree() {}

int MaxRankTree::traceTree() {
    int max = 0;
    int nodeId = node;
    queue<Tree *> q;
    q.push(this);
    while (!q.empty()) {
        Tree *check = q.front();
        int ChildrenSize = check->getChildren().size();
        if (ChildrenSize > max) {
            max = ChildrenSize;
            nodeId = check->getNode();
        }else{
            for (int i = 0; i < ChildrenSize; i++) {
                q.push(check->getChildren()[i]);
            }
            q.pop();
        }
    }
    return nodeId;
}

//============================================================================================================

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {};

RootTree::RootTree(const RootTree &other) : Tree(other) {}

Tree *RootTree::clone() const { return new RootTree(*this); }

RootTree::~RootTree() {};

int RootTree::traceTree() { return this->getNode(); }
