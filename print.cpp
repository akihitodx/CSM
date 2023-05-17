#include <iostream>
#include "alg.h"
#include "tools.h"

void Index::print_com_index() {
    cout<<"com_index================"<<endl;
    int n = 0;
    for (auto i: this->com_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

void Index::print_miss_index() {
    cout << "miss_index================" << endl;
    int n = 0;
    for (auto i: this->miss_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j.first<<"->"<<j.second<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

void Index::print_com_index_query() {
    cout<<"com_index_query================"<<endl;
    int n = 0;
    for (auto i: this->com_index_query) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

void Index::print_all() {
    print_com_index();
    print_com_index_query();
    print_miss_index();
}

void Graph::print_kernel(){
    cout<<"kernel_set: ";
    for (auto i: kernel_set) {
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"kernel_adj: "<<endl;
    for(auto i: kernel_adj){
        cout<<i.first<<": ";
        for(auto j:i.second){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void Graph::print_kernel_nei_unkernel(){
    cout<<"kernel_unkernel_adj: "<<endl;
    for(auto i : kernel_nei_unkernel){
        cout<<i.first<<": ";
        for(auto j: i.second){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void Graph::print_edge_count(){
    for(auto i : edge_count){
        cout<<"label->("<<i.first.first<<","<<i.first.second<<") : id->";
        for(auto j:i.second){
            cout<<"("<<j.first<<","<<j.second<<"), ";
        }
        cout<<endl;
    }
}

void Graph::print_adj() {
    int n = 0;
    for(auto i: adj){
        cout<<n++<<": ";
        for(auto j : i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
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

void Match::print_res() {
    cout<<"res=================="<<endl;
    for(auto i: res){
        for(auto j : i){
            cout<<"(";
            for(auto k : j){
                cout<<k<<" ";
            }
            cout<<")";
        }
        cout<<endl<<"====================="<<endl;
    }
}