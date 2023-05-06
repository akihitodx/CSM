#include <iostream>
#include "tools.h"
#include "alg.h"
#include <fstream>
#include <assert.h>
#include <map>

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


    vector<unordered_set<int>> com_index;
    com_index.resize(dataSet->vNum);
    vector<multimap<int,int>> miss_index;
    miss_index.resize(dataSet->vNum);
    preProsessing(*querySet,*dataSet,com_index,miss_index);
    print_com_index(com_index);
    print_miss_index(miss_index);

    updateIndex(2,3,*querySet,*dataSet,com_index,miss_index);

    print_com_index(com_index);
    print_miss_index(miss_index);



}


