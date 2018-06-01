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
                auto key=pair2str({i,j});
                q.push({key,{i, j}});
                visited[key].insert(key);
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
/*
 * def shorstOverallDistance(people, bikes):#coordinations of N people and N bikes
    if not people:
        return 0
    size = len(people)
    shortest_distance = None
    for i in size:
        for j in size:
            distance = distanceBetween(people[i], bikes[j]) + shortestOverallDistance(people[:i] + people[i+1:], bikes[j] + bikes[j+1:])
            if not shortest_distance or shortest_distance > distance:
                shortest_distance = distance
    return distance

    def distanceBetween(p1, p2): #apply any custom distance function
    '''
 */

/*
 * 距离场
 *
*/

//542. 01 Matrix, walls and gates
//find nearest 0 for each 1
//距离场初始化为 0 for target,INT_MAX for source
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

//317. Shortest Distance from All Buildings
static int shortestDistance(vector<vector<int>>& grid) {
    int res = INT_MAX, buildingCnt = 0, m = grid.size(), n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, 0)), cnt = dist;
    vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                ++buildingCnt;
                queue<pair<int, int>> q;
                q.push({i, j});
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                int level = 1;
                while (!q.empty()) {
                    int size = q.size();
                    for (int s = 0; s < size; ++s) {
                        int a = q.front().first, b = q.front().second; q.pop();
                        for (int k = 0; k < dirs.size(); ++k) {
                            int x = a + dirs[k][0], y = b + dirs[k][1];
                            if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0 && !visited[x][y]) {
                                dist[x][y] += level;
                                ++cnt[x][y];
                                visited[x][y] = true;
                                q.push({x, y});
                            }
                        }
                    }
                    ++level;
                }
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0 && cnt[i][j] == buildingCnt) {
                res = min(res, dist[i][j]);
            }
        }
    }
    return res == INT_MAX ? -1 : res;
}

//815. Bus Routes
static int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
    if(S==T)
        return 0;
    //build stop to routes mapping
    unordered_map<int,unordered_set<int>> s2r;
    for(int i=0;i<routes.size();i++){
        for(int j=0;j<routes[i].size();j++){
            s2r[routes[i][j]].insert(i);
        }
    }
    //build graph
    unordered_map<int,unordered_set<int>> graph;
    for(int i=0;i<routes.size();i++){
        for(int j=0;j<routes[i].size();j++){
            for(auto r:s2r[routes[i][j]]){
                if(r!=i)
                    graph[i].insert(r);
            }
        }
    }

    queue<int> q;
    unordered_set<int> targets(s2r[T].begin(),s2r[T].end());
    unordered_set<int> visited;
    for(auto i:s2r[S]){
        q.push(i);
        visited.insert(i);
    }
    int dist=0;
    while(!q.empty()){
        dist++;
        int sz=q.size();
        for(int i=0;i<sz;i++){
            auto t=q.front();q.pop();
            if(targets.count(t)){
                return dist;
            }
            for(auto neibor:graph[t]){
                if(!visited.count(neibor)){
                    q.push(neibor);
                    visited.insert(neibor);
                }
            }
        }
    }
    return -1;
}
