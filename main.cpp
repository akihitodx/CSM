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
    string queryPath = "../test/dataSet";
    Graph *querySet = new Graph();
    querySet->readGraph(queryPath);
    querySet->printGraph();

    auto res = findKernel(*querySet);
    print_vector_one(res);





}
