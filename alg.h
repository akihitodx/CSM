#ifndef CSM_ALG_H
#define CSM_ALG_H
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
using namespace std;
class Graph{
public:
    int vNum,eNum;
    vector<int> node_id;
    vector<int> node_label;
    vector<int> node_adj;
    vector<int> adj_find;
    vector<int> node_degree;
    unordered_map<int,multiset<int>> neighbor;

    int max_degree_id=0;

public:
    void readGraph(string &path);
    void printGraph();
    void print_Neighbor();
};
/**
 * 只覆盖点集 当点集归零 边集自然也归零
 * 要求：度最大优先 且保持连通状态
 * @param graph 查询图
 * @param nodeNum 顶点个数
 */
vector<int> findKernel(const Graph &graph);

int findMax(unordered_set<int> &adj,vector<int> degree);

void preProsessing(const Graph &graph,vector<int> &kernelSet,unordered_map<int,multiset<int>> &queryNeighbor,unordered_map<int,vector<pair<int,int>>> &index);
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
