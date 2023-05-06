#ifndef CSM_TOOLS_H
#define CSM_TOOLS_H
#include <string>
#include <iostream>
//#include "alg.h"
using namespace  std;

template<typename T>
void print_vector_one(const vector<T> &vec){
    for(auto i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

template<typename T>
void print_vector_two(const vector<vector<T>> &vec){
    for (auto i:vec) {
        for(auto j: vec){
            cout<<j<<" ";
        }
        cout<<endl;
    }
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

void print_miss_index(vector<multimap<int,int>> &miss_index){
    cout<<"miss_index================"<<endl;
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

#endif //CSM_TOOLS_H
