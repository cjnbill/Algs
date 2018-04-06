//
// Created by cjn on 2018/4/5.
//

#include "union_find.h"
#include <vector>
using namespace std;

union_find::union_find(std::vector<std::vector<char>>& grid){
    int m=grid.size(),n=grid[0].size();
    father.resize(m*n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='1'){
                int id=i*n+j;
                father[id]=id;
                count++;
            }
        }
    }
}

int union_find::find(int x) {
    if(father[x]==x)
        return x;
    father[x]=find(father[x]);
    return father[x];
}

void union_find::unin(int a, int b) {
    auto root_a=find(a);
    auto root_b=find(b);
    if(root_a!=root_b){
        father[root_a]=root_b;
        count--;
    }
}

int numIslands(vector<vector<char>>& grid) {
    //corner cases
    if(grid.empty()||grid[0].empty())
        return 0;
    vector<pair<int,int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};
    int m=grid.size(),n=grid[0].size();
    union_find* uf=new union_find(grid);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='1'){
                for(auto dir:dirs){
                    int x=i+dir.first;
                    int y=j+dir.second;
                    if(x>=0&&x<m&&y>=0&&y<n&&grid[x][y]=='1'){
                        uf->unin(i*n+j,x*n+y);
                    }
                }
            }
        }
    }
    return uf->count;
}