//
// Created by cjn on 2018/4/17.
//
#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>

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
//399. Evaluate Division
//first build a graph
//do dfs
//*****important******
//if the problem is to find a possible solution,
// then don't need backtracking, just use hash table to record the visited pos
class Dfs399 {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations,
                                vector<double>& values, vector<pair<string, string>> query)
    {
        unordered_map<string,unordered_map<string, double>> m;
        vector<double> res;
        for (int i = 0; i < values.size(); ++i)
        {
            m[equations[i].first].insert(make_pair(equations[i].second,values[i]));
            if(values[i]!=0)
                m[equations[i].second].insert(make_pair(equations[i].first,1/values[i]));
        }

        for (auto i : query)
        {
            unordered_set<string> s;
            double tmp = check(i.first,i.second,m,s);
            if(tmp) res.push_back(tmp);
            else res.push_back(-1);
        }
        return res;
    }

    double check(string up, string down,
                 unordered_map<string,unordered_map<string, double>> &m,
                 unordered_set<string> &s)
    {
        if(m[up].find(down) != m[up].end()) return m[up][down];
        for (auto i : m[up])
        {
            if(s.find(i.first) == s.end())
            {
                s.insert(i.first);
                double tmp = check(i.first,down,m,s);
                if(tmp) return i.second*tmp;
            }
        }
        return 0;
    }
};