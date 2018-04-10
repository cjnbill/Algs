//
// Created by cjn on 2018/4/5.
//

#include "UnionFind.h"
#include <vector>
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