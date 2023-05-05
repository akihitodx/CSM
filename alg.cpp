#include "alg.h"
#include "tools.h"
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
void Graph::readGraph(string &path){
    ifstream ifs;
    ifs.open(path);
    if(!ifs.is_open()){
        cout<<path<<" open failed"<<endl;
        exit(0);
    }
    char type;
    int id,adj=0,degree,label;
    int vNum,eNum;
    ifs>>type>>vNum>>eNum;
    this->vNum = vNum;
    this->eNum = eNum;
    for(int i = 0;i<vNum;++i){
        ifs>>type>>id>>label>>degree;
        this->node_id.emplace_back(id);
        this->node_label.emplace_back(label);
        this->node_adj.emplace_back(adj);
        this->node_degree.emplace_back(degree);
        this->max_degree_id = node_degree[max_degree_id] < degree ? id : max_degree_id;
        this->label_set[label].insert(id);
        adj += degree;
    }
    this->adj_find.resize(adj,-1);
    int left,right;
    for (int i = 0; i < eNum; ++i) {
        ifs>>type>>left>>right;
        int loc = this->node_adj[left];
        while(this->adj_find[loc] != -1){
            ++loc;
        }
        this->adj_find[loc] = right;
        loc = this->node_adj[right];
        while(this->adj_find[loc] != -1 ){
            ++loc;
        }
        this->adj_find[loc] = left;
    }
    ifs.close();
    int loc = 0;
    for(int i = 0; i<vNum; ++i){
        multiset<int> s;
        while(loc<node_adj[i]+node_degree[i]){
            s.insert(node_label[adj_find[loc++]]);
        }
        neighbor[i] = s;
    }
}

void Graph::printGraph() {
    cout<<"printGraph=============================="<<endl;
    cout<<"node_label"<<endl;
    print_vector_one(node_label);
    cout<<"node_adj"<<endl;
    print_vector_one(node_adj);
    cout<<"adj_find"<<endl;
    print_vector_one(adj_find);
    cout<<"adj_degree"<<endl;
    print_vector_one(node_degree);
    cout<<"max_degree_id:"<<max_degree_id<<endl;
    cout<<"Neighbor"<<endl;
    print_Neighbor();
    cout<<"label_set"<<endl;
    print_label_set();
    cout<<"==============================printGraph"<<endl;
}

void Graph::print_label_set() {
    for (auto i: label_set) {
        cout<<i.first<<":";
        for (auto j: i.second) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void Graph::print_Neighbor() {
    for (const auto& i: neighbor) {
        cout<<i.first<<":";
        for (auto j: i.second) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}


vector<int> findKernel(const Graph &graph) {
    int nodeNum = graph.vNum;
    vector<int> kernel_set;
    auto degree = graph.node_degree;
    unordered_set<int> adj;
    degree[graph.max_degree_id] = -1;
    kernel_set.emplace_back(graph.max_degree_id);
    --nodeNum;
    int max_loc=-1;
    //第一次 进行初始化
    for (int i = graph.node_adj[graph.max_degree_id]; i < graph.node_adj[graph.max_degree_id]+ graph.node_degree[graph.max_degree_id]; ++i) {
        int id = graph.adj_find[i];
        --degree[id];
        if(degree[id]==0){
            --nodeNum;
            continue;
        }
        adj.insert(id);
    }
    // 开始寻找核心
    while(nodeNum>0){
        max_loc = findMax(adj,degree);
        kernel_set.emplace_back(max_loc);
        adj.erase(max_loc);
        --nodeNum;
        degree[max_loc] = -1;
        for (int i = graph.node_adj[max_loc]; i < graph.node_adj[max_loc]+ graph.node_degree[max_loc]; ++i) {
            int id = graph.adj_find[i];
            if(degree[id]<0) continue;
            --degree[id];
            if(degree[id]==0){
                --nodeNum;
                continue;
            }
            if (adj.count(id)==0){
                adj.insert(id);
            }
        }
    }
    return kernel_set;
}


int findMax(const unordered_set<int> &adj,const vector<int> &degree){
    int maxDegree = -1;
    int maxId = -1;
    for(auto i : adj){
        if (maxDegree<degree[i]){
            maxDegree = degree[i];
            maxId = i;
        }
    }
    return maxId;
}

bool Match(multiset<int> queryNode,multiset<int> dataNode){
    // dataNode 包含 querNode
    return includes(dataNode.begin(),dataNode.end(),queryNode.begin(),queryNode.end());
}

void preProsessing(Graph &graph,vector<int> &kernelSet,unordered_map<int,vector<pair<int,int>>> &index){

}

void findMatch(unordered_map<int,vector<pair<int,int>>> &index,int node_1,int node_2,bool flag){

}