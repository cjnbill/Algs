//
// Created by cjn on 2018/4/16.
//
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <iostream>
using namespace std;

class Door;
class Room;
class Key {
public:
    int ID;
    Door* door;
};
class Door {
public:
    int ID;
    pair<Room*, Room*> rooms;
    bool visited=false;
    Key* key_;
};

class Room {
public:
    int ID;
    vector<Door*> doors;
    bool hasTreasure;
    vector<Key*> keys;
    bool visited = false;
};

/*
 * set of key
 * set of locked doors
 * queue of doors which are going to be visited
 *
 *

 */
static void AddKeys(vector<Key*> keys,unordered_set<Key*>& keys_found,unordered_set<Door*>& locked_doors,queue<Door*>& q){
    for(auto k:keys){
        if(locked_doors.count(k->door)) {
            locked_doors.erase(k->door);
            q.push(k->door);
        }
        keys_found.insert(k);
    }
}
static void AddDoors(vector<Door*> doors,unordered_set<Key*>& keys_found,unordered_set<Door*>& locked_doors,queue<Door*>& q){
    for(auto d:doors){
        if(d->visited)
            continue;
        if(keys_found.count(d->key_)){
            q.push(d);
        } else{
            locked_doors.insert(d);
        }
    }
}
static int FindTreasure(Room* start){
    unordered_set<Key*> keys_found;
    unordered_set<Door*> locked_doors;
    queue<Door*> q;
    if(start->hasTreasure)
        return start->ID;
    AddKeys(start->keys, keys_found, locked_doors, q);
    AddDoors(start->doors, keys_found, locked_doors, q);
    while(!q.empty()){
        auto t_door=q.front();q.pop();
        auto room1=t_door->rooms.first,room2=t_door->rooms.second;
        if(room1->visited)
            continue;
        else {
            if(room1->hasTreasure)
                return room1->ID;
            AddKeys(room1->keys, keys_found, locked_doors, q);
            AddDoors(room1->doors, keys_found, locked_doors, q);
        }
        if(room2->visited)
            continue;
        else {
            if(room2->hasTreasure)
                return room2->ID;
            AddKeys(room2->keys, keys_found, locked_doors, q);
            AddDoors(room2->doors, keys_found, locked_doors, q);
        }
    }
}

static int test(){
    auto r1=new Room();
    cout<< FindTreasure(r1);
}
