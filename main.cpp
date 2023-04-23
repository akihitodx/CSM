#include <iostream>
#include "tools.h"
#include "alg.h"
#include <fstream>
#include <assert.h>
int main() {
    string queryPath = "../querySet";
    Graph *querySet = new Graph();
    querySet->readGraph(queryPath);
    querySet->printGraph();

    string dataPath = "../dataSet";
    Graph *dataSet = new Graph();
    dataSet->readGraph(dataPath);
    dataSet->printGraph();





}
