#include "../Include/Session.h"


Session::Session(const string &path) : g(), treeType(), agents() {
    //Openning a stream to the file.
    ifstream is(path);
    nlohmann::json file;
    is >> file;

    //========================================================================================================

    int i = 0;
    int j = 0;
    //The matrix of the graph.
    vector<vector<int>> matrix = vector<vector<int>>();
    //The line of every loop in the matrix.
    vector<int> line = vector<int>();
    //Entering the graph data.
    while (file["graph"][i] != nullptr) {
        while (file["graph"][i][j] != nullptr) {
            line.push_back(file["graph"][i][j]);
            j++;
        }
        matrix.push_back(line);
        line.clear();
        i++;
    }
    this->g = Graph(matrix);

    //========================================================================================================
    //Entering the Agents data.
    int c = 0;
    Agent *a;
    InfectedNodes = queue<int>();
    //Entering the agents data.
    while (file["agents"][c] != nullptr) {
        int nodeId = file["agents"][c][1];
        if (file["agents"][c][0] == "V") {
            a = new Virus(nodeId, *this);
            InfectedNodes.push(nodeId);
        } else {
            a = new ContactTracer(*this);
        }
        this->agents.push_back(a);
        c++;
    }
    //========================================================================================================
    //Entering the TreeType data.

    if (file["tree"] == "M") {
        this->treeType = MaxRank;
    } else {
        if (file["tree"] == "C") {
            this->treeType = Cycle;
        } else {
            this->treeType = Root;
        }
    }
}

void Session::addAgent(const Agent &agent) { agent.addAgentVisit(); }

void Session::addAgent(Agent *agent) {
    Agent *a = agent;
    agents.push_back(a);
    InfectedNodes.push(agent->getNodeId());
}

void Session::setGraph(const Graph &graph) { this->g = graph; }

void Session::enqueueInfected(int node) {
    InfectedNodes.push(node);
    g.infectNode(node);
}

int Session::dequeueInfected() {
    if (!InfectedNodes.empty()) {
        int node = InfectedNodes.front();
        InfectedNodes.pop();
        return node;
    }
    return -1;
}

TreeType Session::getTreeType() const { return treeType; }

Graph Session::getGraph() const {
    return g;
}

void Session::simulate() {
    while (!InfectedNodes.empty()) {
        int size = agents.size();
        for (int i = 0; i < size; i++) {
            agents.at(i)->act();
        }
    }
}