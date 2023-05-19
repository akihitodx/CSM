#include <iostream>

#include "alg.h"
#include <fstream>
//#include <assert.h>
#include <map>
#include "tools.h"
#include <ctime>

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
    clock_t begin,end;
    double elapsedTime;


    string queryPath = "../test/querySet";
    string dataPath = "../test/dataSet";

    begin = clock();

    Graph *querySet = new Graph();
    querySet->readGraph(queryPath);
//    querySet->printGraph();
//    querySet->print_edge_count();
    querySet->set_kernel();
//    querySet->print_kernel();
//    querySet->print_kernel_nei_unkernel();

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;

    begin = clock();

    Graph *dataSet = new Graph();
    dataSet->readGraph(dataPath);
//    dataSet->printGraph();

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;

    begin = clock();
    Index *index = new Index(querySet->vNum,dataSet->vNum);
    preProsessing(*querySet,*dataSet,*index);
    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
//    index->print_all();
    vector<vector<int>> res;
    cout<<"*********************************"<<endl;
    begin = clock();
    updateIndex(2,3,*querySet,*dataSet,*index);
    updateIndex(3,2,*querySet,*dataSet,*index);
    res = subgraph_Match(2,3,*querySet,*dataSet,*index);
    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    print_vector_two(res);
    cout<<"*********************************"<<endl;

    begin = clock();
    updateIndex(6,13,*querySet,*dataSet,*index);
    updateIndex(13,6,*querySet,*dataSet,*index);
    res = subgraph_Match(6,13,*querySet,*dataSet,*index);
    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    print_vector_two(res);
    cout<<"*********************************"<<endl;

    begin = clock();
    updateIndex(11,12,*querySet,*dataSet,*index);
    updateIndex(12,11,*querySet,*dataSet,*index);
    res = subgraph_Match(11,12,*querySet,*dataSet,*index);
    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    print_vector_two(res);
    cout<<"*********************************"<<endl;

    //两种可能 需要set hash一下 要不就要想办法去重。

    return 0;
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


