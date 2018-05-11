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