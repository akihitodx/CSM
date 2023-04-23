#include "alg.h"
#include "tools.h"
#include <fstream>
#include <iostream>
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
    cout<<"==============================printGraph"<<endl;
}
