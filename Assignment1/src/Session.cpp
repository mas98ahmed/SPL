#include "../Include/Session.h"
#include "../Include/Graph.h"
#include "../Include/json.hpp"
#include "../Include/Agent.h"

#include <iostream>

using namespace std;

Session::Session(const string &path) : g(Graph()), treeType(Root), agents(vector<Agent *>()), InfectedNodes(queue<int>()), enqueuedNodes(vector<int>()), cycle(0)
{
    //Opening a stream to the file.
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
    while (file["graph"][i] != nullptr)
    {
        while (file["graph"][i][j] != nullptr)
        {
            line.push_back(file["graph"][i][j]);
            j++;
        }
        j = 0;
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
    while (file["agents"][c] != nullptr)
    {
        int nodeId = file["agents"][c][1];
        if (file["agents"][c][0] == "V")
        {
            a = new Virus(nodeId);
        }
        else
        {
            a = new ContactTracer();
        }
        addAgent(*a);
        c++;
    }

    //========================================================================================================
    //Entering the TreeType data.

    if (file["tree"] == "M")
    {
        this->treeType = MaxRank;
    }
    else
    {
        if (file["tree"] == "C")
        {
            this->treeType = Cycle;
        }
        else
        {
            this->treeType = Root;
        }
    }
}

Session::Session(const Session &other) : g(other.g), treeType(other.treeType), agents(vector<Agent*>()), InfectedNodes(queue<int>()), enqueuedNodes(vector<int>()), cycle(other.cycle)
{
    if (this != &other)
    {
        clear();
        int size = other.InfectedNodes.size();
        queue<int> Infect = other.InfectedNodes;
        for (int i = 0; i < size; i++)
        {
            int tmp = Infect.front();
            Infect.pop();
            InfectedNodes.push(tmp);
        }
        size = other.enqueuedNodes.size();
        for (int i = 0; i < size; i++)
        {
            enqueuedNodes.push_back(other.enqueuedNodes[i]);
        }
        size = other.agents.size();
        for (int i = 0; i < size; i++)
        {
            agents.push_back(other.agents[i]->clone());
        }
    }
}

Session &Session::operator=(const Session &other)
{
    if (this != &other)
    {
        clear();
        g = other.g;
        treeType = other.treeType;
        cycle = other.cycle;
        int size = other.InfectedNodes.size();
        queue<int> Infect = other.InfectedNodes;
        for (int i = 0; i < size; i++)
        {
            int tmp = Infect.front();
            Infect.pop();
            InfectedNodes.push(tmp);
        }
        size = other.enqueuedNodes.size();
        for (int i = 0; i < size; i++)
        {
            enqueuedNodes.push_back(other.enqueuedNodes[i]);
        }
        size = other.agents.size();
        for (int i = 0; i < size; i++)
        {
            agents.push_back(other.agents[i]->clone());
        }
    }
    return *this;
}

Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents), InfectedNodes(other.InfectedNodes), enqueuedNodes(other.enqueuedNodes), cycle(other.cycle)
{
    if (this != &other)
    {
        other.g = Graph();
        treeType = Root;
        other.cycle = -1;
        other.agents = vector<Agent*>();
        other.InfectedNodes = queue<int>();
        other.enqueuedNodes = vector<int>();
    }
}

Session &Session::operator=(Session &&other)
{
    if (this != &other)
    {
        g = other.g;
        treeType = other.treeType;
        cycle = other.cycle;
        agents = other.agents;
        InfectedNodes = other.InfectedNodes;
        enqueuedNodes = other.enqueuedNodes;
        other.g = Graph();
        other.treeType = Root;
        other.cycle = -1;
        other.agents = vector<Agent*>();
        other.InfectedNodes = queue<int>();
        other.enqueuedNodes = vector<int>();
    }
    return *this;
}

Session::~Session() { clear(); }

void Session::clear()
{
    int size = agents.size();
    for (int i = 0; i < size; i++)
    {
        delete agents[i];
    }
    agents.clear();
    for (int i = 0; i < size; i++)
    {
        InfectedNodes.pop();
    }
    enqueuedNodes.clear();
}

void Session::addAgent(const Agent &agent)
{
    agents.push_back(agent.clone());
    if (agent.getNodeId() != -1)
    {
        g.infectNode(agent.getNodeId());
    }
}

void Session::setGraph(const Graph &graph) { this->g = graph; }

void Session::enqueueInfected(int node)
{
    InfectedNodes.push(node);
    enqueuedNodes.push_back(node);
}

int Session::dequeueInfected()
{
    if (!InfectedNodes.empty())
    {
        int node = InfectedNodes.front();
        InfectedNodes.pop();
        return node;
    }
    return -1;
}

bool Session::isenqueued(int nodeId) const
{
    int size = enqueuedNodes.size();
    for (int i = 0; i < size; i++)
    {
        if (enqueuedNodes[i] == nodeId)
        {
            return true;
        }
    }
    return false;
}

TreeType Session::getTreeType() const { return treeType; }

Graph Session::getGraph() const { return g; }

void Session::simulate()
{
    if (VirusExist())
    {
        while (!g.isTetminated(*this))
        {
            int size = agents.size();
            for (int i = 0; i < size; i++)
            {
                agents.at(i)->act(*this);
            }
            cycle++;
        }
    }
    cycle = 0;

    //writing to the file.
    nlohmann::json file;
    file["graph"] = g.getEdges();
    file["infected"] = g.getInfectedNodes();
    ofstream os("output.json");
    os << file;
}

int Session::getCycle() const { return cycle; }

bool Session::VirusExist() const
{
    int size = agents.size();
    for (int i = 0; i < size; i++)
    {
        if (agents[i]->isVirus())
        {
            return true;
        }
    }
    return false;
}