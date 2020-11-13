#include "../Include/Tree.h"
#include "../Include/Session.h"

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree*>()) {};

//Rule of 3.
Tree::Tree(const Tree &other): node(other.getNode()), children(vector<Tree*>()) {// copy const
    clear();
    int childrenSize = other.getChildren().size();
    for(int i=0;i< childrenSize;i++){
        children.push_back(other.getChildren()[i]->clone());
    }
};

Tree &Tree::operator=(const Tree &other) {//rule of 3
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

void Tree::clear() {
    int childrenSize = children.size();
    if (childrenSize > 0) {
        
        for (int i = 0; i < childrenSize; i++) {
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
CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.getCycle()) {};

Tree *CycleTree::clone() const { return new CycleTree(*this); }

CycleTree::~CycleTree() {
    int childrenSize = children.size();
    for(int i=0;i<childrenSize;i++){
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
    int ChildrenSize = children.size();
    for(int i=0;i<ChildrenSize;i++){
        delete children[i];
    }
    children.clear();
}

//Methods
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

//Rule of 3.
RootTree::RootTree(const RootTree &other) : Tree(other) {
}

Tree *RootTree::clone() const { return new RootTree(*this); }

RootTree::~RootTree() {
    int childrenSize = children.size();
    for(int i=0;i<childrenSize;i++){
        delete children[i];
    }
    children.clear();
};

//Methods
int RootTree::traceTree() { return this->getNode(); }
