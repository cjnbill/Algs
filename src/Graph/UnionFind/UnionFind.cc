//
// Created by cjn on 2018/4/5.
//

#include "UnionFind.h"
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

UnionFind::UnionFind(std::vector<std::vector<char>>& grid){
    auto m=grid.size(),n=grid[0].size();
    father_.resize(m*n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='1'){
                auto id=i*n+j;
                father_[id]=id;
                count_++;
            }
        }
    }
}

int UnionFind::Find(int x) {
    if(father_[x]==x)
        return x;
    father_[x]= Find(father_[x]);
    return father_[x];
}

void UnionFind::Union(unsigned long a, unsigned long b) {
    auto root_a= Find(a);
    auto root_b= Find(b);
    if(root_a!=root_b){
        father_[root_a]=root_b;
        count_--;
    }
}

int NumOfIslands(vector<vector<char>> &grid) {
    //corner cases
    if(grid.empty()||grid[0].empty())
        return 0;
    vector<pair<int,int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};
    auto m=grid.size(),n=grid[0].size();
    auto uf=new UnionFind(grid);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='1'){
                for(auto dir:dirs){
                    int x=i+dir.first;
                    int y=j+dir.second;
                    if(x>=0&&x<m&&y>=0&&y<n&&grid[x][y]=='1'){
                        uf->Union(i * n + j, x * n + y);
                    }
                }
            }
        }
    }
    return uf->count_;
}


class SentenceSimilarity {
public:
    class union_find{
    public:
        unordered_map<string,string> father;

        string Find(string x){
            if(father[x]==x)
                return x;
            father[x]=Find(father[x]);
            return father[x];
        }
        void Union(string a,string b){
            auto root_a=Find(a);
            auto root_b=Find(b);
            if(root_a!=root_b){
                father[root_a]=root_b;
            }
        }
    };
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        int m=words1.size(),n=words2.size();
        if(m!=n)return false;
        if(!m)return true;
        union_find uf;
        for(auto p:pairs){
            if(!uf.father.count(p.first))
                uf.father[p.first]=p.first;
            if(!uf.father.count(p.second))
                uf.father[p.second]=p.second;
            uf.Union(p.first,p.second);
        }
        for(int i=0;i<m;i++){
            auto root_a=uf.Find(words1[i]);
            auto root_b=uf.Find(words2[i]);
            if(root_a!=root_b)return false;
        }
        return true;
    }
};


class CalcEquation {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, Node*> map;
        vector<double> res;
        for (int i = 0; i < equations.size(); i ++) {
            string s1 = equations[i].first, s2 = equations[i].second;
            if (map.count(s1) == 0 && map.count(s2) == 0) {
                map[s1] = new Node();
                map[s2] = new Node();
                map[s1] -> value = values[i];
                map[s2] -> value = 1;
                map[s1] -> parent = map[s2];
            } else if (map.count(s1) == 0) {
                map[s1] = new Node();
                map[s1] -> value = map[s2] -> value * values[i];
                map[s1] -> parent = map[s2];
            } else if (map.count(s2) == 0) {
                map[s2] = new Node();
                map[s2] -> value = map[s1] -> value / values[i];
                map[s2] -> parent = map[s1];
            } else {
                unionNodes(map[s1], map[s2], values[i], map);
            }
        }

        for (auto query : queries) {
            if (map.count(query.first) == 0 || map.count(query.second) == 0 || findParent(map[query.first]) != findParent(map[query.second]))
                res.push_back(-1);
            else
                res.push_back(map[query.first] -> value / map[query.second] -> value);
        }
        return res;
    }

private:
    struct Node {
        Node* parent;
        double value = 0.0;
        Node()  {parent = this;}
    };

    void unionNodes(Node* node1, Node* node2, double num, unordered_map<string, Node*>& map) {
        Node* parent1 = findParent(node1), *parent2 = findParent(node2);
        double ratio = node2 -> value * num / node1 -> value;
        for (auto it = map.begin(); it != map.end(); it ++)
            if (findParent(it -> second) == parent1)
                it -> second -> value *= ratio;
        parent1 -> parent = parent2;
    }

    Node* findParent(Node* node) {
        if (node -> parent == node)
            return node;
        node -> parent = findParent(node -> parent);
        return node -> parent;
    }
};