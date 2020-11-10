#include "../Include/Tree.h"


using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) {};

//Rule of 3.
Tree::Tree(const Tree &other) {// copy const
    node = other.getNode();
    clear();
    for(int i=0;i<other.getChildren().size();i++){
        children.push_back(other.getChildren()[i]->clone());
    }
};

Tree &Tree::operator=(const Tree &other) {//rule of 3
    if (this != &other) {
        clear();
        node = other.node;
        for(int i=0;i<other.getChildren().size();i++){
            children.push_back(other.getChildren()[i]->clone());
        }
    }
    return *this;
};

void Tree::clear() {
    if (children.size() > 0) {
        for (int i = 0; i < children.size(); i++) {
            children[i]->clear();
            delete children[i];
        }
        children.clear();
    }
};

Tree::~Tree() {}

//Methods
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

//Getters
int Tree::getNode() const { return node; }

vector<Tree *> Tree::getChildren() const { return children; };

//============================================================================================================

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {};

//Rule of 3.
CycleTree::CycleTree(const CycleTree &other) : currCycle(other.getCycle()), Tree(other) {};

Tree *CycleTree::clone() const { return new CycleTree(*this); }

CycleTree::~CycleTree() {
    for(int i=0;i<children.size();i++){
        delete children[i];
    }
    children.clear();
}

//Methods
int CycleTree::traceTree() {
    vector<Tree *> curr = children;
    while (currCycle > 0 && curr[0] != nullptr) {
        curr = curr[0]->getChildren();
        currCycle--;
    }
    return curr[0]->getNode();
}

//Getters
int CycleTree::getCycle() const { return currCycle; }

//============================================================================================================

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

//Rule of 3.
MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {}

Tree *MaxRankTree::clone() const { return new MaxRankTree(*this); }

MaxRankTree::~MaxRankTree() {
    for(int i=0;i<children.size();i++){
        delete children[i];
    }
    children.clear();
}

//Methods
int MaxRankTree::traceTree() {
    int max = 0;
    int nodeId = 0;
    queue<Tree *> q;
    q.push(this);
    while (!q.empty()) {
        Tree *check = q.front();
        q.pop();
        if (check->getChildren().size() > max) {
            max = check->getChildren().size();
            nodeId = check->getNode();
        } else {
            for (int i = 0; i < q.front()->getChildren().size(); i++) {
                q.push(check->getChildren()[i]);
            }

        }
    }
    return nodeId;
}

//============================================================================================================

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {};

//Rule of 3.
RootTree::RootTree(const RootTree &other) : Tree(other) {
}

Tree *RootTree::clone() const { return new RootTree(*this); }

RootTree::~RootTree() {
    for(int i=0;i<children.size();i++){
        delete children[i];
    }
    children.clear();
};

//Methods
int RootTree::traceTree() { return this->getNode(); }