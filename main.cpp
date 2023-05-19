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


    updateIndex(2,3,*querySet,*dataSet,*index);
    updateIndex(3,2,*querySet,*dataSet,*index);
    index->print_all();
    cout<<"++++++++++++++++"<<endl;
    Match m1(*querySet);
    m1.getPath(*querySet,1);
    m1.getUnkernel_path(*querySet,1);
    m1.match_table[1].push_back(3);
    get_All_kernel(3,m1,*querySet,*dataSet,*index);
    m1.print_res();
    get_All_unkernel(m1,*querySet,*dataSet,*index);
    m1.print_res_second();

    cout<<"++++++++++++++++"<<endl;
    updateIndex(6,13,*querySet,*dataSet,*index);
    updateIndex(13,6,*querySet,*dataSet,*index);
    Match m2(*querySet);
    m2.getPath(*querySet,2);
    m2.getUnkernel_path(*querySet,2);
    m2.match_table[2].push_back(6);
    get_All_kernel(6,m2,*querySet,*dataSet,*index);
    m2.print_res();
    get_All_unkernel(m2,*querySet,*dataSet,*index);
    m2.print_res_second();

    cout<<"++++++++++++++++"<<endl;
    updateIndex(11,12,*querySet,*dataSet,*index);
    updateIndex(12,11,*querySet,*dataSet,*index);
    Match m3(*querySet);
    m3.getPath(*querySet,4);
    m3.getUnkernel_path(*querySet,4);
    m3.match_table[4].push_back(11);
    get_All_kernel(11,m3,*querySet,*dataSet,*index);
    m3.print_res();
    get_All_unkernel(m3,*querySet,*dataSet,*index);
    m3.print_res_second();

    return 0;

}


