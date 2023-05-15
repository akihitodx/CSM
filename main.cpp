#include <iostream>

#include "alg.h"
#include <fstream>
//#include <assert.h>
#include <map>
#include "tools.h"


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
    string queryPath = "../test/querySet";
    Graph *querySet = new Graph();
    querySet->readGraph(queryPath);
    querySet->printGraph();
    querySet->print_edge_count();

    querySet->set_kernel();
    querySet->print_kernel();
    querySet->print_kernel_nei_unkernel();

    string dataPath = "../test/dataSet";
    Graph *dataSet = new Graph();
    dataSet->readGraph(dataPath);
    dataSet->printGraph();

    Index *index = new Index(querySet->vNum,dataSet->vNum);
    preProsessing(*querySet,*dataSet,*index);



    index->print_all();
//cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
//    updateIndex(5,0,*querySet,*dataSet,com_index,miss_index);
//    print_com_index(com_index);
//    print_miss_index(miss_index);
//    cout<<"!!!!!!!!!"<<endl;
//    updateIndex(0,5,*querySet,*dataSet,com_index,miss_index);
//    print_com_index(com_index);
//    print_miss_index(miss_index);
//    cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
//    updateIndex(6,0,*querySet,*dataSet,com_index,miss_index);
//    updateIndex(0,6,*querySet,*dataSet,com_index,miss_index);
//    print_com_index(com_index);
//    print_miss_index(miss_index);
//    updateIndex(6,13,*querySet,*dataSet,*index);
//    updateIndex(13,6,*querySet,*dataSet,*index);
//    subgraph_Match(6,13,*querySet,*dataSet,*index);
    updateIndex(2,3,*querySet,*dataSet,*index);
    updateIndex(3,2,*querySet,*dataSet,*index);
    index->print_all();


    return 0;

}


