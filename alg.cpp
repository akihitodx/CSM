#include "alg.h"
#include "tools.h"
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
    cout<<"Neighbor"<<endl;
    print_Neighbor();
    cout<<"==============================printGraph"<<endl;
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


vector<int> findKernel(Graph &graph,unordered_set<int> &vertex,int node) {
    vector<int> kernel_set;
    queue<int> q;
    q.push(node);
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        for (int i = graph.node_adj[cur]; i <graph.node_adj[cur]+graph.node_degree[cur] ; ++i) {
            q.push(i);
        }
    }


    return kernel_set;
}


void preProsessing(Graph &graph,vector<int> &kernelSet,unordered_map<int,vector<pair<int,int>>> &index){

}

void findMatch(unordered_map<int,vector<pair<int,int>>> &index,int node_1,int node_2,bool flag){

}