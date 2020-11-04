#include "../Include/Session.h"

using namespace std;

Session::Session(const string &path) :agents(vector<Agent *>()) {
    ifstream is(path);
    nlohmann::json file;
    is >> file;
    int c = 0;
    //Entering the agents data.
    while (file["agents"][c] != nullptr) {
        int nodeId = file["agents"][c][1];
        Agent *a = file["agents"][c][0] == "V" ? new Virus(nodeId, *this) : new ContactTracer();
        this->agents.push_back(a);
        c++;
    }
    //========================================================================================================
    int i = 0;
    int j = 0;
    //The matrix of the graph.
    vector<vector<int>> *matrix = new vector<vector<int>>();
    //The line of every loop in the matrix.
    vector<int> *line = new vector<int>();
    //Entering the graph data.
    while (file["graph"][i] != nullptr) {
        while (file["graph"][i][j] != nullptr) {
            line->push_back(file["graph"][i][j]);
            j++;
        }
        matrix->push_back(*line);
        line->clear();
        i++;
    }
    this->g = new Graph(*matrix);
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


