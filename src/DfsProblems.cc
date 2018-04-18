//
// Created by cjn on 2018/4/17.
//
#include <vector>
using namespace std;

//traverse area

//200. Number of Islands
//first mark cur pos as visited, then traverse four dirs
//at each loop, judge whether it is in bound
vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

static void dfs_200(int i, int j, vector<vector<char>> &grid) {
    int m=grid.size(),n=grid[0].size();
    grid[i][j] = '0';
    for (auto dir:dirs) {
        int x = i + dir[0];
        int y = j + dir[1];
        if(x<0||x>=m||y<0||y>=n||grid[x][y]=='0')
            continue;

        dfs_200(x, y, grid);
    }
}

//329. Longest Increasing Path in a Matrix

// To get max length of increasing sequences:

//Do DFS from every cell
//Compare every 4 direction and skip cells that are out of boundary or smaller
//Get matrix max from every cell’s max
//Use matrix[x][y] <= matrix[i][j] so we don’t need a visited[m][n] array
//The key is to cache the distance because it’s highly possible to revisit a cell

static int dfs_329(vector<vector<char>> &matrix,vector<vector<int>>& dp,int i,int j){
    int m=matrix.size(),n=matrix[0].size();
    if(dp[i][j]!=1){
        return dp[i][j];
    }

    int res=1;
    for(auto dir:dirs){
        int x=i+dir[0],y=j+dir[1];
        if(x<0||x>=m||y<0||y>=n||matrix[x][y]<=matrix[i][j])
            continue;
        int len=1+dfs_329(matrix,dp,x,y);
        res=max(res,len);
    }
    dp[i][j]=res;
    return res;
}