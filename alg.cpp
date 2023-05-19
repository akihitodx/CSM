#include "alg.h"
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <map>

Index::Index(int queryNum, int dataNum) {
    com_index.resize(dataNum);
    miss_index.resize(dataNum);
    com_index_query.resize(queryNum);
}
Match::Match(Graph &query) {
    match_table.resize(query.vNum);
    count = 0;

}

void Match::getPath(Graph &query, int a) {
    queue<int> qqq;
    queue<int> fff;
    unordered_set<int> over;
    over.insert(a);
    for(auto i : query.kernel_adj[a]){
        qqq.push(i);
        fff.push(a);
    }
    while(!qqq.empty()){
        auto temp = qqq.front();
        qqq.pop();
        over.insert(temp);
        auto f = fff.front();
        fff.pop();
        kernel_path.emplace_back(f,temp);
        for(auto i : query.kernel_adj[temp]){
            if(over.find(i)==over.end()){
                qqq.push(i);
                fff.push(temp);
            }
        }
    }

}

void Match::getPath(Graph &query, int a, int b) {
    queue<int> qqq;
    queue<int> fff;
    unordered_set<int> over;
    over.insert(a);
    for(auto i : query.kernel_adj[a]){
        qqq.push(i);
        fff.push(a);
    }
    while(!qqq.empty()){
        auto temp = qqq.front();
        qqq.pop();
        over.insert(temp);
        auto f = fff.front();
        fff.pop();
        kernel_path.emplace_back(f,temp);
        for(auto i : query.kernel_adj[temp]){
            if(over.find(i)==over.end()){
                qqq.push(i);
                fff.push(temp);
            }
        }
    }
    kernel_path.erase(remove(kernel_path.begin(),kernel_path.end(), make_pair(a,b)),kernel_path.end());
}
void Match::getUnkernel_path(Graph &query, int a){
    queue<int> q;
    unordered_set<int> ss = query.kernel_set;
    q.push(a);
    ss.erase(a);
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        unkernel_path.push_back(temp);
        for(auto i: query.kernel_adj[temp]){
            if(ss.find(i) != ss.end()){
                q.push(i);
                ss.erase(i);
            }

        }
    }
}

void Match::getUnkernel_path(Graph &query, int a,int b){
    queue<int> q;
    unordered_set<int> ss = query.kernel_set;
    q.push(a);
    q.push(b);
    ss.erase(a);
    ss.erase(b);
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        unkernel_path.push_back(temp);
        for(auto i: query.kernel_adj[temp]){
            if(ss.find(i) != ss.end()){
                q.push(i);
                ss.erase(i);
            }
        }
    }
}

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

void Graph::set_adj() {
    adj.resize(vNum);
    int begin = 0;
    for(int i = 0;i<vNum;++i){
        adj[i] = set(adj_find.begin()+begin,adj_find.begin()+begin+node_degree[i]);
        begin = begin +node_degree[i];
    }
}

void Graph::set_kernel() {
    this->kernel_set = findKernel(*this);

    for(auto id: this->kernel_set){
        auto nei = this->adj[id];
        for(auto i:nei){
            if(kernel_set.find(i)!=kernel_set.end()){
                kernel_adj[id].insert(i);
            }
        }
    }


//    Kernel *kernel = new Kernel();
//    this->kernel = kernel;
//    for(auto id: this->kernel_set){
//        auto nei = this->adj[id];
//        for(auto i:nei){
//            if(kernel_set.find(i)!=kernel_set.end()){
//                kernel->adj[id].insert(i);
//            }
//        }
//    }
    for(auto i : kernel_set){
        vector adj (this->adj[i].begin(),this->adj[i].end());  //节点的所有邻居
        sort(adj.begin(),adj.end());
        vector ker (kernel_set.begin(),kernel_set.end());
        sort(ker.begin(),ker.end());
        set_difference(adj.begin(),adj.end(),ker.begin(),ker.end(), back_inserter(this->kernel_nei_unkernel[i]));
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

void preProsessing(Graph &query, Graph &data,Index &index){
    for (auto data_node:data.node_id) {
        //获取当前数据节点的标签 所对应的查询节点标签的顶点集合 <label,id>
        auto label_set = query.label_set[data.node_label[data_node]];
        for(auto i: label_set){
            //对于每一个查询顶点 进行集合比较 如果包含，则将这个数据节点添加进com_index   data_id: query_id...
            if(com_Match(query.neighbor[i],data.neighbor[data_node])){
                index.com_index[data_node].insert(i);
                index.com_index_query[i].insert(data_node);
                index.miss_index[data_node].insert({i,-1});
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
                            index.miss_index[data_node].insert({i,j});
                        }
                    }
                }
            }
        }
    }
}

void updateIndex(int node, int nei ,Graph &query, Graph &data, Index &index){
    //邻居表更新
    data.neighbor[node].insert(data.node_label[nei]);
    data.adj[node].insert(nei);
    //获取该数据节点可能对应的查询节点 （即标签匹配） 对于每一个查询节点进行匹配
    auto label_set = query.label_set[data.node_label[node]];
    for(auto i :label_set){
        //完全匹配 无需更新
        if(index.com_index[node].empty() || index.com_index[node].find(i) == index.com_index[node].end()){ //不是该查询顶点的完全匹配
            //缺一匹配 可能发生变化
            if(!index.miss_index[node].empty() && index.miss_index[node].count(i)>0){ //构成缺一匹配 测试是不是构成了新完全匹配
                auto it = index.miss_index[node].find(i);
                for(int count = 0  ; count != index.miss_index[node].count(i) ;++count,++it){
                    if(data.node_label[nei] == query.node_label[it->second]){
                        //满足条件 构成完全匹配了
                        index.com_index[node].insert(i);
                        index.com_index_query[i].insert(node);
                    }
                }
                //删除miss_index[node]中的冗余部分 更新com_index[node]的内容
                index.miss_index[node].erase(i);
                index.miss_index[node].insert({i,-1});

            }else{ //不构成匹配 尝试进行缺一匹配
                int vv = miss_Match(query.neighbor[i],data.neighbor[node]);
                if(vv!= -1){ //构成了缺一匹配
                    for(auto v : query.adj[node]){
                        if (query.node_label[v] == vv){
                            index.miss_index[node].insert({i,v});
                        }
                    }
                }
            }
        }
    }
}

void doubleKernel_match(int main){

}

void singleKernel_match(int main, int is_query, Match &match, Graph &query, Graph &data, Index &index,int &loc){
    //is_quert main对应的查询节点
    //count 用于记录经过的核心节点的数量

//    if( *(kernel_match.end()-1) ==  0){
//        if(*(match_table.end()-1) == 0){
//            res.push_back({match_table.begin(),match_table.end()-1});
//        }
//    }

    if(!match.match_table[is_query].empty()){   //核心节点只会经过一次 //好像不需要
        return ;
    }
    if(match.count == 0){

//        ++count;
        return;
    }

    match.match_table[is_query].push_back(main); //main插入match_table
    --match.count;
    auto main_nei_unkernel = query.kernel_nei_unkernel[is_query]; //get all unkernel of is_query's neighbor
    for(auto i :main_nei_unkernel){  // do insert for each unkernel
        vector<int> unkernel_cand;
        for(auto n : data.adj[main]){
            if(index.com_index[n].find(i) != index.com_index[n].end()){
                unkernel_cand.push_back(n);
            }
        }
        sort(unkernel_cand.begin(),unkernel_cand.end());
        if(match.match_table[i].empty()){
            match.match_table[i] = unkernel_cand;
        }else{
            vector<int> change;
            set_intersection(match.match_table[i].begin(),match.match_table[i].end(),unkernel_cand.begin(),unkernel_cand.end(), back_inserter(change));
            if(change.empty()){
                //这里需要回溯的逻辑
                match.match_table[is_query].pop_back();
                ++match.count;
                return ;
            }
            match.match_table[i] = change;

        }
    }

//    auto main_nei_kernel = query.kernel_adj[is_query];
//    for(auto qid: main_nei_kernel){
//        auto qid_cand = index.com_index_query[qid];
//        if(count != 0){
//            for(auto cand : qid_cand){
//                match_table[qid].push_back(cand);
//                singleKernel_match(cand,qid,match_table,query,data,res,index, --count);
//
//                match_table[qid].pop_back();
//            }
//        } else{
//            res.push_back(match_table);
//            ++count;
//        }
//
//    }

    vector<int> main_nei_kernel(query.kernel_adj[is_query].begin(),query.kernel_adj[is_query].end());
    vector<vector<int>> kernel_cand_set;
    for(auto i: main_nei_kernel){
        vector<int> kernel_cand;
        for(auto n : data.adj[main]){
            if(index.com_index[n].find(i) != index.com_index[n].end()){
                kernel_cand.push_back(n);
            }
        }
        sort(kernel_cand.begin(),kernel_cand.end());
        kernel_cand_set[i] = kernel_cand;
    }


//    auto kernel_nei = kernel.adj[is_query];
//    for(auto i : kernel_nei){
//        auto com = index.com_index_query[i];
//        for(auto j : com){
//
//        }
//    }

}



void get_All_kernel(int main, Match &match, Graph &query, Graph &data, Index &index) {
    if (match.count == match.kernel_path.size()) {
        match.res.push_back(match.match_table);
        return;
    }

    int is_query = match.kernel_path[match.count].first;
    int next = match.kernel_path[match.count].second;

    for (auto mid: match.match_table[is_query]) {  //还是有问题
        for (auto i: data.adj[mid]) {
            if (index.com_index[i].find(next) == index.com_index[i].end()) {
                continue;
            }
            ++match.count;
            match.match_table[next].push_back(i);
            get_All_kernel(i, match, query, data, index);
            --match.count;
            match.match_table[next].pop_back();
        }
    }
}

void get_All_unkernel(Match &match,Graph &query,Graph &data,Index &index){
    bool flag= true;
    for(auto path:match.res){

        for(auto is_query: match.unkernel_path){
            if(!flag) break;
            auto main = path[is_query][0];
            auto main_nei_unkernel = query.kernel_nei_unkernel[is_query];
            for (auto i: main_nei_unkernel) {  // do insert for each unkernel
                if(!flag) break;
                vector<int> unkernel_cand;
                for (auto n: data.adj[main]) {
                    if (index.com_index[n].find(i) != index.com_index[n].end()) {
                        unkernel_cand.push_back(n);
                    }
                }
                if (path[i].empty()) {
                    path[i] = unkernel_cand;
                } else {
                    vector<int> change;
                    set_intersection(path[i].begin(), path[i].end(), unkernel_cand.begin(),
                                     unkernel_cand.end(), back_inserter(change));
                    if (change.empty()) {
                        flag = false;
                    } else{
                        path[i] = {change.begin(),change.end()};
                    }
                }
            }
        }
        if(flag){
            match.res_second.push_back(path);
        } else{
            flag = true;
        }
    }
}


vector<vector<int>> subgraph_Match(int node_a, int node_b, Graph &query, Graph &data, Index &index) {
    vector<vector<int>> res;
    int label_a = data.node_label[node_a];
    int label_b = data.node_label[node_b];
    pair<int, int> edge_ab;
    int a, b;
    if (label_a < label_b) {
        edge_ab = {label_a, label_b};
        a = 0;
        b = 1;
    } else {
        edge_ab = {label_b, label_a};
        a = 1;
        b = 0;
    }
    auto edge_match = query.edge_count[edge_ab];
    auto com_a = index.com_index[node_a];
    auto com_b = index.com_index[node_b];
    vector<pair<int, int>> should_match;
    for (auto i: edge_match) {
        if (label_a == edge_ab.first) {
            if (com_a.find(i.first) != com_a.end() && com_b.find(i.second) != com_b.end()) {
                should_match.emplace_back(i);
            }
        } else {
            if (com_a.find(i.second) != com_a.end() && com_b.find(i.first) != com_b.end()) {
                should_match.emplace_back(i);
            }
        }
    }
    for (auto match: should_match) {
        if (label_a == edge_ab.first) {
            bool f1 = query.kernel_set.find(match.first) != query.kernel_set.end() ? true : false;
            bool f2 = query.kernel_set.find(match.second) != query.kernel_set.end() ? true : false;
            if (f1 && f2) {
                //都是核心点

            } else {
                //只存在一个核心点
                if (f1) {
                    //第一个点是核心点
                    unordered_map<int, unordered_set<int>> maybe_kernel;
                    auto nei_query = query.kernel_adj[match.second];  //这些核心顶点的匹配周围必循存在node_b
                    vector<int> match_table;
                    match_table.resize(query.vNum + 1, -1);
                    match_table[query.vNum] = query.vNum;
                    for (auto ker_id: index.com_index[match.first]) {
                        match_table[match.first] = ker_id;
//                        singleKernel_match();
                    }


                } else {

                }
            }
        }

    }


    return res;

}

