#include <iostream>

#include "alg.h"
#include <fstream>
//#include <assert.h>
#include <map>
#include "tools.h"

void print_miss_index(vector<multimap<int, int>> &miss_index);
void print_com_index(vector<unordered_set<int>> &com_index);

int main() {
//    string queryPath = "../test/querySet";
//    Graph *querySet = new Graph();
//    querySet->readGraph(queryPath);
//    querySet->printGraph();

//    string dataPath = "../dataSet";
//    Graph *dataSet = new Graph();
//    dataSet->readGraph(dataPath);
//    dataSet->printGraph();

//    string queryPath = "../test/demo01";
//    string queryPath = "../test/cricle";
//    string queryPath = "../test/querySet";
//    string queryPath = "../test/querySet";
//
//    string queryPath = "../test/querySet";
//a
    string queryPath = "../test/datasets/human/query_graph/query_dense_8_2.graph";
    Graph *querySet = new Graph();
    querySet->readGraph(queryPath);
    querySet->printGraph();
    querySet->print_edge_count();

    querySet->set_kernel();
    querySet->print_kernel();

    string dataPath = "../test/dataSet";
    Graph *dataSet = new Graph();
    dataSet->readGraph(dataPath);
    dataSet->printGraph();



    vector<unordered_set<int>> com_index;
    com_index.resize(dataSet->vNum);
    vector<multimap<int,int>> miss_index;
    miss_index.resize(dataSet->vNum);
    preProsessing(*querySet,*dataSet,com_index,miss_index);
    print_com_index(com_index);
    print_miss_index(miss_index);
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    updateIndex(5,0,*querySet,*dataSet,com_index,miss_index);
    print_com_index(com_index);
    print_miss_index(miss_index);
    cout<<"!!!!!!!!!"<<endl;
    updateIndex(0,5,*querySet,*dataSet,com_index,miss_index);
    print_com_index(com_index);
    print_miss_index(miss_index);
    cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    updateIndex(6,0,*querySet,*dataSet,com_index,miss_index);
    updateIndex(0,6,*querySet,*dataSet,com_index,miss_index);
    print_com_index(com_index);
    print_miss_index(miss_index);


}



void print_com_index(vector<unordered_set<int>> &com_index) {
    cout<<"com_index================"<<endl;
    int n = 0;
    for (auto i: com_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

void print_miss_index(vector<multimap<int, int>> &miss_index) {
    cout << "miss_index================" << endl;
    int n = 0;
    for (auto i: miss_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j.first<<"->"<<j.second<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}