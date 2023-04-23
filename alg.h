#ifndef CSM_ALG_H
#define CSM_ALG_H
#include <vector>
#include <string>
using namespace std;
class Graph{
public:
    vector<int> node_id;
    vector<int> node_label;
    vector<int> node_adj;
    vector<int> adj_find;
    vector<int> node_degree;

public:
    void readGraph(string &path);
    void printGraph();
};





#endif //CSM_ALG_H
