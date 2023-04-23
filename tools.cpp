#include "tools.h"
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void vector_one(vector<T> &vec){
    for(auto i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

template<typename T>
void vector_two(vector<vector<T>> &vec){
    for (auto i:vec) {
        for(auto j: vec){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}