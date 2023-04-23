#ifndef CSM_ALG_H
#define CSM_ALG_H
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;
class Graph{
public:
    vector<int> node_id;
    vector<int> node_label;
    vector<int> node_adj;
    vector<int> adj_find;
    vector<int> node_degree;
    unordered_map<int,multiset<int>> neighbor;

public:
    void readGraph(string &path);
    void printGraph();
    void print_Neighbor();
};

void findKernel(Graph &graph);

void preProsessing(Graph &graph,vector<int> &kernelSet,unordered_map<int,multiset<int>> &queryNeighbor,unordered_map<int,vector<pair<int,int>>> &index);
/**
 * 在索引内寻找匹配 目前仅实现增加操作 默认为增加操作
 * @param index
 * @param node_1
 * @param node_2
 * @param flag true 增加 false 减少
 */
void findMatch(unordered_map<int,vector<pair<int,int>>> &index,int node_1,int node_2,bool flag=true);

void updateIndex();


#endif //CSM_ALG_H
