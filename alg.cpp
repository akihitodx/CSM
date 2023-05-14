#include "alg.h"
#include "tools.h"
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <map>
void Graph::readGraph(string &path) {
    ifstream ifs;
    ifs.open(path);
    if (!ifs.is_open()) {
        cout << path << " open failed" << endl;
        exit(0);
    }
    char type;
    int id, adj = 0, degree, label;
    int vNum, eNum;
    ifs >> type >> vNum >> eNum;
    this->vNum = vNum;
    this->eNum = eNum;
    for (int i = 0; i < vNum; ++i) {
        ifs >> type >> id >> label >> degree;
        this->node_id.emplace_back(id);
        this->node_label.emplace_back(label);
        this->node_adj.emplace_back(adj);
        this->node_degree.emplace_back(degree);
        this->max_degree_id = node_degree[max_degree_id] < degree ? id : max_degree_id;
        this->label_set[label].insert(id);
        adj += degree;
    }
    this->adj_find.resize(adj, -1);
    int left, right;
    int temp;
    for (int i = 0; i < eNum; ++i) {
        ifs >> type >> left >> right >> temp;
        int loc = this->node_adj[left];
        while (this->adj_find[loc] != -1) {
            ++loc;
        }
        this->adj_find[loc] = right;
        loc = this->node_adj[right];
        while (this->adj_find[loc] != -1) {
            ++loc;
        }
        this->adj_find[loc] = left;

        pair<int,int> label_group;
        if(this->node_label[left]<this->node_label[right]){
            label_group = {this->node_label[left],this->node_label[right]};
            this->edge_count[label_group].insert({left, right});
        }else{
            label_group = {this->node_label[right],this->node_label[left]};
            this->edge_count[label_group].insert({right, left});
        }

    }
    ifs.close();
    int loc = 0;
    for (int i = 0; i < vNum; ++i) {
        multiset<int> s;
        while (loc < node_adj[i] + node_degree[i]) {
            s.insert(node_label[adj_find[loc++]]);
        }
        neighbor[i] = s;
    }

    set_adj();

}
void Graph::printGraph() {
    cout<<"printGraph=============================="<<endl;
    cout<<"node_label"<<endl;
    print_vector_one(node_label);
    cout<<"node_adj"<<endl;
    print_vector_one(node_adj);
    cout<<"adj_find"<<endl;
    print_vector_one(adj_find);
    cout<<"adj_degree"<<endl;
    print_vector_one(node_degree);
    cout<<"max_degree_id:"<<max_degree_id<<endl;
    cout<<"Neighbor"<<endl;
    print_Neighbor();
    cout<<"label_set"<<endl;
    print_label_set();
    cout<<"==============================printGraph"<<endl;
}

void Graph::print_label_set() {
    for (auto i: label_set) {
        cout<<i.first<<":";
        for (auto j: i.second) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void Graph::print_Neighbor() {
    for (const auto& i: neighbor) {
        cout<<i.first<<":";
        for (auto j: i.second) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
void Graph::set_adj() {
    adj.resize(vNum);
    int begin = 0;
    for(int i = 0;i<vNum;++i){
        adj[i] = unordered_set(adj_find.begin()+begin,adj_find.begin()+begin+node_degree[i]);
        begin = begin +node_degree[i];
    }
}
void Graph::print_adj() {
    int n = 0;
    for(auto i: adj){
        cout<<n++<<": ";
        for(auto j : i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
void Graph::print_edge_count(){
    for(auto i : edge_count){
        cout<<"label->("<<i.first.first<<","<<i.first.second<<") : id->";
        for(auto j:i.second){
            cout<<"("<<j.first<<","<<j.second<<"), ";
        }
        cout<<endl;
    }
}
void Graph::print_kernel(){
    cout<<"kernel_set: ";
    for (auto i: kernel_set) {
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"kernel: "<<endl;
    for(auto i: kernel->adj){
        cout<<i.first<<": ";
        for(auto j:i.second){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
void Graph::set_kernel() {
    this->kernel_set = findKernel(*this);
    Kernel *kernel = new Kernel();
    this->kernel = kernel;
    for(auto id: this->kernel_set){
        auto nei = this->adj[id];
        for(auto i:nei){
            if(kernel_set.find(i)!=kernel_set.end()){
                kernel->adj[id].insert(i);
            }
        }
    }

}

unordered_set<int> findKernel(const Graph &graph) {
    int nodeNum = graph.vNum;
    unordered_set<int> kernel_set;
    auto degree = graph.node_degree;
    unordered_set<int> adj;
    degree[graph.max_degree_id] = -1;
    kernel_set.insert(graph.max_degree_id);
    --nodeNum;
    int max_loc=-1;
    //第一次 进行初始化
    for (int i = graph.node_adj[graph.max_degree_id]; i < graph.node_adj[graph.max_degree_id]+ graph.node_degree[graph.max_degree_id]; ++i) {
        int id = graph.adj_find[i];
        --degree[id];
        if(degree[id]==0){
            --nodeNum;
            continue;
        }
        adj.insert(id);
    }
    // 开始寻找核心
    while(nodeNum>0){
        max_loc = findMax(adj,degree);
        kernel_set.insert(max_loc);
        adj.erase(max_loc);
        --nodeNum;
        degree[max_loc] = -1;
        for (int i = graph.node_adj[max_loc]; i < graph.node_adj[max_loc]+ graph.node_degree[max_loc]; ++i) {
            int id = graph.adj_find[i];
            if(degree[id]<0) continue;
            --degree[id];
            if(degree[id]==0){
                --nodeNum;
                continue;
            }
            if (adj.count(id)==0){
                adj.insert(id);
            }
        }
    }
    return kernel_set;
}

int findMax(const unordered_set<int> &adj,const vector<int> &degree){
    int maxDegree = -1;
    int maxId = -1;
    for(auto i : adj){
        if (maxDegree<degree[i]){
            maxDegree = degree[i];
            maxId = i;
        }
    }
    return maxId;
}

bool com_Match(multiset<int> &queryNode,multiset<int> &dataNode){
    // dataNode 包含 querNode
    return includes(dataNode.begin(),dataNode.end(),queryNode.begin(),queryNode.end());
}

int miss_Match(multiset<int> &queryNode,multiset<int> &dataNode){
    vector<int> target;
    set_difference(queryNode.begin(),queryNode.end(),dataNode.begin(),dataNode.end(),back_inserter(target));
    if(target.size()==1){
        return target[0];
    }
    return -1;
}

void preProsessing(Graph &query, Graph &data,vector<unordered_set<int>> &com_index,vector<multimap<int,int>> &miss_index,vector<unordered_set<int>> &com_index_query){
    for (auto data_node:data.node_id) {
        //获取当前数据节点的标签 所对应的查询节点标签的顶点集合 <label,id>
        auto label_set = query.label_set[data.node_label[data_node]];
        for(auto i: label_set){
            //对于每一个查询顶点 进行集合比较 如果包含，则将这个数据节点添加进com_index   data_id: query_id...
            if(com_Match(query.neighbor[i],data.neighbor[data_node])){
                com_index[data_node].insert(i);
                com_index_query[i].insert(data_node);
                miss_index[data_node].insert({i,-1});
            }else{
                //如果不满足包含，进行缺一比较  返回值>=0 则是缺失的标签 -1则不满足缺一
                auto tar = miss_Match(query.neighbor[i],data.neighbor[data_node]);
                if( tar != -1){
                    //满足缺一 添加进索引  data_id: query_id->miss_query_id ...
//                    for(int k = query.adj_find[query.node_adj[i]]; k<query.node_adj[i]+ query.node_degree[i];++k){
//                        if(query.node_label[k] == tar){
//                            miss_index[data_node].insert({i,query.adj_find[k]});
//                        }
//                    }
                    for(auto j: query.adj[i]){
                        if(query.node_label[j] == tar){
                            miss_index[data_node].insert({i,j});
                        }
                    }
                }
            }
        }
    }
}

void updateIndex(int node, int nei ,Graph &query, Graph &data,vector<unordered_set<int>> &com_index,vector<multimap<int,int>> &miss_index){
    //邻居表更新
    data.neighbor[node].insert(data.node_label[nei]);
    data.adj[node].insert(nei);
    //获取该数据节点可能对应的查询节点 （即标签匹配） 对于每一个查询节点进行匹配
    auto label_set = query.label_set[data.node_label[node]];
    for(auto i :label_set){
        //完全匹配 无需更新
        if(com_index[node].size() == 0 || com_index[node].find(i) == com_index[node].end()){ //不是该查询顶点的完全匹配
            //缺一匹配 可能发生变化
            if(miss_index[node].size() != 0 && miss_index[node].count(i)>0){ //构成缺一匹配 测试是不是构成了新完全匹配
                auto it = miss_index[node].find(i);
                for(int count = 0  ; count != miss_index[node].count(i) ;++count,++it){
                    if(data.node_label[nei] == query.node_label[it->second]){
                        //满足条件 构成完全匹配了
                        com_index[node].insert(i);
                    }
                }
                //删除miss_index[node]中的冗余部分 更新com_index[node]的内容
                miss_index[node].erase(i);
                miss_index[node].insert({i,-1});

            }else{ //不构成匹配 尝试进行缺一匹配
                int vv = miss_Match(query.neighbor[i],data.neighbor[node]);
                if(vv!= -1){ //构成了缺一匹配
                    for(auto v : query.adj[node]){
                        if (query.node_label[v] == vv){
                            miss_index[node].insert({i,v});
                        }
                    }
                }
            }
        }
    }


//    data.neighbor[nei].insert(data.node_label[node]);


/*
    auto find_com_a = com_index.find(a);
    auto find_miss_a = miss_index.find(a);
    auto find_com_b = com_index.find(b);
    auto find_miss_b = miss_index.find(b);

    //如果都是完全匹配， 必定存在匹配
    if(find_com_a != com_index.end() && find_com_b!= com_index.end()){
        //进行匹配 确定双方是否都有彼此
        return;
    }
    // a,b不满足缺一和完全， 必定不存在匹配
    if(find_miss_a != miss_index.end() || find_miss_b!= miss_index.end()){
        //不进行匹配
        return;
    }
    //a完全 b缺一 可能存在匹配
    if(find_com_a != com_index.end() && find_com_b==com_index.end() && find_miss_b!=miss_index.end()){
        auto index_b = miss_index[b];
        auto index_a = miss_index[a];
        for(auto i : index_b){
            if(index_a.find(i.second)!=index_a.end()){
                //找到匹配
                //执行回溯搜索
            }
        }
        return;
    }

    //b完全 a缺一 可能存在匹配
    if(find_com_b != com_index.end() && find_com_a==com_index.end() && find_miss_a!=miss_index.end()){
        auto index_b = miss_index[b];
        auto index_a = miss_index[a];
        for(auto i : index_a){
            if(index_b.find(i.second)!=index_b.end()){
                //找到匹配
                //执行回溯搜索
            }
        }
        return;
    }
    //a缺一，b缺一 可能存在
    if(find_com_a == com_index.end() && find_com_b==com_index.end() && find_miss_a!=miss_index.end() && find_miss_b!=miss_index.end()){
        auto index_b = miss_index[b];
        auto index_a = miss_index[a];
        for(auto i:index_a){

        }
        return;
    }


*/


}

void doubleKernel_match(int main){

}

void singleKernel_match(int main,vector<int> &match_table){

}

vector<vector<int>> subgraph_Match(int node_a, int node_b, Graph &query, Graph &data, vector<unordered_set<int>> &com_index ){
    vector<vector<int>> res;
    int label_a = data.node_label[node_a];
    int label_b = data.node_label[node_b];
    pair<int,int> edge_ab;
    int a,b;
    if(label_a<label_b){
        edge_ab = {label_a,label_b};
        a = 0;
        b = 1;
    }else{
        edge_ab = {label_b,label_a};
        a = 1;
        b = 0;
    }
    auto edge_match = query.edge_count[edge_ab];
    auto com_a = com_index[node_a];
    auto com_b = com_index[node_b];
    vector<pair<int,int>> should_match;
    for (auto i: edge_match) {
        if(label_a == edge_ab.first){
            if(com_a.find(i.first) != com_a.end()  && com_b.find(i.second) != com_b.end()  ){
                should_match.emplace_back(i);
            }
        }else{
            if(com_a.find(i.second) != com_a.end()  && com_b.find(i.first) != com_b.end()  ){
                should_match.emplace_back(i);
            }
        }
    }
    for(auto match : should_match){
        if(label_a == edge_ab.first){
            bool f1 = query.kernel_set.find(match.first) != query.kernel_set.end() ? true: false;
            bool f2 = query.kernel_set.find(match.second) != query.kernel_set.end() ? true: false;
            if(f1 && f2){
                //都是核心点

            } else{
                //只存在一个核心点
                if(f1){
                    //第一个点是核心点
                    unordered_map<int,unordered_set<int>> maybe_kernel;
                    auto nei_query = query.kernel->adj[match.second];  //这些核心顶点的匹配周围必循存在node_b
                    vector<int> match_table;
                    match_table.resize(query.vNum,-1);
                    match_table[match.first];
//                    for (auto ker_id: com_index[])


                } else{

                }
            }
        }

    }


    return res;

}

