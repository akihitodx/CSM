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
        bool f1,f2,ff;
        if (label_a == edge_ab.first) {
            f1 = query.kernel_set.find(match.first) != query.kernel_set.end();
            f2 = query.kernel_set.find(match.second) != query.kernel_set.end();
            ff = true;
        } else {
            f2 = query.kernel_set.find(match.first) != query.kernel_set.end();
            f1 = query.kernel_set.find(match.second) != query.kernel_set.end();
            ff = false;
        }

        if (f1 && f2) {
            //都是核心点
            int q_a,q_b;
            if(ff){
                q_a = match.first;
                q_b = match.second;
            }else{
                q_b = match.first;
                q_a = match.second;
            }
            Match mm(query);
            mm.getPath(query,q_a,q_b);
            mm.getUnkernel_path(query,q_a,q_b);
            if(ff){
                mm.match_table[q_a].push_back(node_a);
                mm.match_table[q_b].push_back(node_b);
            }else{
                mm.match_table[q_a].push_back(node_b);
                mm.match_table[q_b].push_back(node_a);
            }
            get_All_kernel(q_a,mm,query,data,index);
            get_All_unkernel(mm,query,data,index);
            auto r = fork_vec(mm.res_second);
            res.insert(res.end(),r.begin(),r.end());

        } else {
            //只存在一个核心点
            int is_query;
            if (f1) {
                is_query = match.first;
            } else {
                is_query = match.second;
            }
            Match mm(query);
            mm.getPath(query,is_query);
            mm.getUnkernel_path(query,is_query);
            if(f1){
                mm.match_table[is_query].push_back(node_a);
                get_All_kernel(node_a,mm,query,data,index);
            } else{
                mm.match_table[is_query].push_back(node_b);
                get_All_kernel(node_b,mm,query,data,index);
            }

            get_All_unkernel(mm,query,data,index);
            auto r = fork_vec(mm.res_second);
            res.insert(res.end(),r.begin(),r.end());
        }

    }


    return res;
}

void rollback(int &loc,vector<int> &temp,vector<vector<int>> &path,vector<vector<int>> &res){
    if(loc == temp.size()){
        res.push_back(temp);
        return;
    }
    int count = path[loc].size();
    for(int j = 0; j<count;++j){
        int i = path[loc][j];
        temp[loc] = i;
        ++loc;
        rollback(loc,temp,path,res);
        --loc;
        temp[loc] = -1;
    }
}
vector<vector<int>> fork_vec(vector<vector<vector<int>>> &match){
    vector<vector<int>> res;
    vector<int> temp(match[0].size(),-1);
    for(auto path: match){
        int a = 0;
        rollback(a,temp,path,res);
    }

    return res;
}