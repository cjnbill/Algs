//
// Created by cjn on 2018/4/18.
//
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

using namespace std;


static vector<pair<int,int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

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


//207. course schedule

static bool CourseSchedule(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<int> degrees(numCourses,0);
    unordered_map<int,unordered_set<int>> posts;
    for(auto p:prerequisites){
        degrees[p.first]++;
        posts[p.second].insert(p.first);
    }
    queue<int> q;
    for(int i=0;i<numCourses;i++){
        if(degrees[i]==0)q.push(i);
    }
    int res=0;
    while(!q.empty()){
        int t=q.front();q.pop();
        res++;
        for(auto post:posts[t]){
            if(--degrees[post]==0)q.push(post);
        }
    }
    return res==numCourses;
}


//Bike and person
//0 is bike, 1 is person
//add bikes to queue, do bfs for each bike, update the distance from person to bike meanwhile
//if the person's pos equals to the input, return
//no need for visited set

string pair2str(pair<int,int> pos){
    return to_string(pos.first)+','+to_string(pos.second);
}
pair<int,int> str2pair(string s){
    int pos=s.find(',');
    string pf=s.substr(0,pos);
    string ps=s.substr(pos+1);
    return {stoi(pf),stoi(ps)};
};

static pair<int,int> BikePerson(vector<vector<int>>& grid, pair<int,int> person){
    queue<pair<string,pair<int,int>>> q;
    int m=grid.size(),n=grid[0].size();
    unordered_map<string,unordered_set<string>> visited;
    //unordered_map<string,pair<int,int>> bike_person;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==0) {
                q.push({pair2str({i,j}),{i, j}});
                auto key=pair2str({i,j});
                visited[key].insert({i,j});
            }
        }
    }
    while(!q.empty()){
        auto t=q.front();q.pop();
        string key=t.first;
        int x=t.second.first,y=t.second.second;
        for(auto dir:dirs){
            int nx=x+dir.first,ny=y+dir.second;
            if(visited[key].count(pair2str({nx,ny}))||nx<0||nx>=m||ny<0||ny>=n)
                continue;
            if(grid[nx][ny]==1){
                //bike_person[key]={nx,ny};
                grid[nx][ny]=0;
                if(nx==person.first&&ny==person.second)
                    return str2pair(key);
            }
        }
    }
    //return pos[person.first][person.second];
    return {};
}


