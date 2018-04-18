//
// Created by cjn on 2018/4/18.
//
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

//133. Clone Graph

//Definition for undirected graph.
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};
class CloneGraph {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node)return nullptr;
        unordered_map<UndirectedGraphNode*,UndirectedGraphNode*> mp;
        queue<UndirectedGraphNode*> q;
        unordered_set<UndirectedGraphNode*> visited;
        q.push(node);
        visited.insert(node);
        UndirectedGraphNode* new_node=new UndirectedGraphNode(node->label);
        mp[node]=new_node;
        while(!q.empty()){
            auto cur=q.front();q.pop();
            for(auto neighbor:cur->neighbors){
                if(!mp.count(neighbor)){
                    mp[neighbor]=new UndirectedGraphNode(neighbor->label);
                }
                if(!visited.count(neighbor)){
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
                mp[cur]->neighbors.push_back(mp[neighbor]);

            }
        }
        return new_node;
    }

};

//542. 01 Matrix
//add 0 to queue first,then do bfs to update the shortest distance to 1
static vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    int m=matrix.size(),n=matrix[0].size();
    vector<pair<int,int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};
    queue<pair<int,int>> q;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(matrix[i][j]==0)
                q.push({i,j});
            else matrix[i][j]=INT_MAX;
        }
    }
    while(!q.empty()){
        auto t=q.front();q.pop();
        for(auto dir:dirs){
            int x=t.first+dir.first,y=t.second+dir.second;
            if(x<0||x>=m||y<0||y>=n||matrix[x][y]<=matrix[t.first][t.second]+1)continue;
            matrix[x][y]=matrix[t.first][t.second]+1;
            q.push({x,y});
        }
    }
    return matrix;
}