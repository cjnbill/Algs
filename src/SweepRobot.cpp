//
// Created by cjn on 2018/4/16.
//
#include <vector>
#include <unordered_set>

using namespace std;

class Robot {
    // returns true if next cell is open and robot moves into the cell.
    // returns false if next cell is obstacle and robot stays on the current cell.
    bool Move();

    // Robot will stay on the same cell after calling Turn*. k indicates how
    // many turns to perform.
    void TurnLeft(int k);
    void TurnRight(int k);

    // Clean the current cell.
    void Clean();
    vector<vector<int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};
    void DfsClean(int x,int y,int d,unordered_set<pair<int,int>>& visited){
        Clean();
        visited.insert({x,y});
        for(int i=0;i<4;i++){
            if(i!=0)TurnRight(1);
            int nd=(d+i)%4;
            int i=x+dirs[nd][0],j=y+dirs[nd][1];
            if(visited.count({i,j}))
                continue;
            if(Move()){
                DfsClean(i,j,nd,visited);
                //turn opposite direction
                TurnRight(2);
                //move to original pos
                Move();
                //turn to original dir
                TurnRight(2);
            }
            else{
                visited.insert({i,j});
            }
        }
        //after 4 loops, it still need to turn right 1
        TurnRight(1);
    }
};