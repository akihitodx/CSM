#ifndef CSM_ALG_H
#define CSM_ALG_H
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
using namespace std;

class Kernel{
public:
    unordered_map<int,unordered_set<int>> adj;
};


class Index{
public:
    vector<unordered_set<int>> com_index;  //data_id: query_id...
    vector<unordered_set<int>> com_index_query; //query_id: data_id...
    vector<multimap<int,int>> miss_index; //data_id: query_id->miss_query_id

public:
    Index(int queryNum,int dataNum);
    void print_miss_index();
    void print_com_index();
    void print_com_index_query();

    void print_all();
};

class Graph{
public:
    int vNum,eNum;
    vector<int> node_id;
    vector<int> node_label;
    vector<int> node_adj;
    vector<int> adj_find;
    vector<int> node_degree;
    unordered_map<int,multiset<int>> neighbor;        //node_id: nei_node01_label...
    unordered_map<int,unordered_set<int>> label_set;  //label: node_id ...
    vector<set<int>> adj;
    map<pair<int,int>,set<pair<int,int>>> edge_count; // <label_a,label_b> -> {(0,1),(2,3) ...}  label_a < label_b
    int max_degree_id=0;
    unordered_set<int> kernel_set;  // only for query
//    Kernel *kernel; //for query
    unordered_map<int,vector<int>> kernel_nei_unkernel; //for query
    unordered_map<int,unordered_set<int>> kernel_adj; //for query

public:
    void readGraph(string &path);
    void printGraph();
    void print_Neighbor();
    void print_label_set();
    void set_adj();
    void print_adj();
    void print_edge_count();
    void print_kernel();
    void print_kernel_nei_unkernel();
    void set_kernel();
};

class Match{
public:
    vector<vector<int>> match_table;
    vector<vector<vector<int>>> res;
    vector<vector<vector<int>>> res_second;
    int count;
    vector<pair<int,int>> kernel_path;
    vector<int> unkernel_path;
public:
    Match(Graph &query);

    //深搜还是广搜呢？
    void getPath(Graph &query,int a);
    void getPath(Graph &query,int a,int b);

    void getUnkernel_path(Graph &query, int a);
    void getUnkernel_path(Graph &query,int a, int b);
    void print_res();
    void print_res_second();

};


/**
 * 有优化空间 因为寻找核心的时候每次都进行了查询与比较
 * 只覆盖点集 基于度 当点集归零 边集自然也归零
 * 要求：度最大优先 且保持连通状态
 * @param graph 查询图
 */
unordered_set<int> findKernel(const Graph &graph);

/**
 * 寻找当前邻接组内最大度数节点
 * 配合findKernel()使用
 * @param adj
 * @param degree
 * @return
 */
int findMax(const unordered_set<int> &adj,const vector<int> &degree);

void preProsessing(Graph &query, Graph &data,Index &index);

void updateIndex(int a, int b ,Graph &query, Graph &data, Index &index);

bool com_Match(multiset<int> &queryNode,multiset<int> &dataNode);
int miss_Match(multiset<int> &queryNode,multiset<int> &dataNode);

vector<vector<int>> subgraph_Match(int node_a, int node_b, Graph &query, Graph &data, Index &index );

void get_All_kernel(int is_query, Match &match, Graph &query, Graph &data, Index &index);

void get_All_unkernel(Match &match,Graph &query,Graph &data,Index &index);

vector<vector<int>> fork_vec(vector<vector<vector<int>>> &match);
#endif //CSM_ALG_H



