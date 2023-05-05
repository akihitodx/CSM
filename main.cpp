#include <iostream>
#include "tools.h"
#include "alg.h"
#include <fstream>
#include <assert.h>
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
    string queryPath = "../test/querySet";
    Graph *querySet = new Graph();
    querySet->readGraph(queryPath);
    querySet->printGraph();

    string dataPath = "../test/dataSet";
    Graph *dataSet = new Graph();
    dataSet->readGraph(dataPath);
    dataSet->printGraph();

    auto res = findKernel(*querySet);
    print_vector_one(res);


    unordered_map<int,set<int>> com_index;
    unordered_map<int,set<pair<int,int>>> miss_index;
    preProsessing(*querySet,*dataSet,com_index,miss_index);
    cout<<"!!!!!!!!!!!!!!!!"<<endl;
    for (auto i: com_index) {
        cout<<i.first<<": ";
        for (auto j: i.second) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
    for (auto i: miss_index) {
        cout<<i.first<<": ";
        for (auto j: i.second) {
            cout<<j.first<<"->"<<j.second<<" ";
        }
        cout<<endl;
    }
    cout<<"!!!!!!!!!!!!!!!!"<<endl;
    updateIndex(2,3,*querySet,*dataSet,com_index,miss_index);





}
