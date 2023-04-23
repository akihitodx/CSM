#ifndef CSM_TOOLS_H
#define CSM_TOOLS_H
#include <string>
#include <iostream>
#include "alg.h"
using namespace  std;

template<typename T>
void print_vector_one(vector<T> &vec){
    for(auto i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

template<typename T>
void print_vector_two(vector<vector<T>> &vec){
    for (auto i:vec) {
        for(auto j: vec){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}




#endif //CSM_TOOLS_H
