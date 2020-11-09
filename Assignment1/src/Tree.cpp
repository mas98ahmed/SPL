#include "../Include/Tree.h"


using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) {};

Tree::Tree(const Tree &tree) {// copy const
    children = tree.children;
    node = tree.node;
};

Tree &Tree::operator=(const Tree &tree) {//rule of 3
    if (this == &tree)
        return *this;
    clear();
    children = tree.children;
    node = tree.node;
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

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree *ans;
    switch (type) {
        case Cycle :
            ans = new RootTree(rootLabel);
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

int Tree::getNode() const { return node; }

vector<Tree *> Tree::getChildren() const { return children; };

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

Tree::~Tree() {

}

//============================================================================================================

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {};

CycleTree::CycleTree(const CycleTree &other) : Tree(other.getNode()) {};

int CycleTree::traceTree() {
    vector<Tree *> curr = children;
    while (currCycle > 0 && curr[0] != nullptr) {
        curr = curr[0]->getChildren();
        currCycle--;
    }
    return curr[0]->getNode();
}

Tree *CycleTree::clone() const { return new CycleTree(*this); }

CycleTree::~CycleTree() {}

//curr and prev to change code;

//============================================================================================================

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other.getNode()) {}

int MaxRankTree::traceTree() {
    int max = 0;
    int nodeId = 0;
    queue<Tree *> q;
    q.push(this);// ask shahar
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
    return nodeId; // never reach this line
}

Tree *MaxRankTree::clone() const { return new MaxRankTree(*this); }

MaxRankTree::~MaxRankTree() {}

//============================================================================================================

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {};

int RootTree::traceTree() {
    return this->getNode();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}

RootTree::RootTree(const RootTree &other) : Tree(other.getNode()) {
}

RootTree::~RootTree() {};

