//
// Created by cjn on 2018/4/16.
//
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Door;
class Room;
class Key {
public:
    int ID;
    Door* door;
    bool found = false;
};
class Door {
public:
    int ID;
    pair<Room*, Room*> rooms;
    bool locked;
    Key* key;
};

class Room {
public:
    int ID;
    vector<Door*> doors;
    bool hasTreasure;
    vector<Key*> keys;
    bool visited = false;
};

int maze(Room* start){
    stack<Room*> rooms;
    queue<Door*> locked_doors;
    rooms.push(start);
    start->visited=true;
    while(!rooms.empty()||!locked_doors.empty()){
        if(rooms.empty()){
            int sz=locked_doors.size();
            for(int i=0;i<sz;i++){
                auto cur=locked_doors.front();
                locked_doors.pop();
                if(cur->key->found){
                    cur->locked=false;
                }
                if(cur->locked){
                    locked_doors.push(cur);
                } else{
                    auto r1=cur->rooms.first,r2=cur->rooms.second;
                    if(r1->visited&&!r2->visited)
                        r2->visited=true;
                    if(!r1->visited&&r2->visited)
                        r1->visited=true;
                }
            }
        }
        if(!rooms.empty()){
            auto t_room=rooms.top();rooms.pop();
            if(t_room->hasTreasure)
                return t_room->ID;
            for(auto key:t_room->keys){
                key->found=true;
            }
            for(auto door:t_room->doors){
                if(door->key->found){
                    door->locked=false;
                } else{
                    locked_doors.push(door);
                }
                auto r1=door->rooms.first,r2=door->rooms.second;
                if(r1->ID=t_room->ID&&!r2->visited){
                    rooms.push(r2);
                    r2->visited;
                }
                if((r2->ID=t_room->ID&&!r1->visited){
                    rooms.push(r1);
                    r1->visited;
                }
            }
        }
    }
}