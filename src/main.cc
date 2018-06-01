#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Graph/BFS/TreasureFind.cc"
#include "BinarySearch/KthMissingNumber.cpp"
using namespace std;

struct Node{
    string id;
    vector<Node*> childs;
    Node(string ID):id(ID){}
};
class Tree{
public:
    Node* root;
    unordered_map<string, Node*> m;
    void birth(string parent, string child){
        if(m.find(parent)==m.end())
            return;
        auto p_parent=m[parent];
        auto p_child= new Node(child);
        m[child]=p_child;
        p_parent->childs.push_back(p_child);
    }
    void death(string name){
        if(m.find(name)==m.end())
            return;
        m[name]=nullptr;
    }
    vector<string> getOrderOfSuccession(){
        vector<string> res;
        dfs(root,res);
        return res;
    }
    void dfs(Node* cur,vector<string>& res){
        if(!cur)
            return;
        if(m[cur->id]!=nullptr){
            res.push_back(cur->id);
        }
        for(auto c:cur->childs){
            dfs(c,res);
        }
    }



};




int main()
{
    vector<int> nums={2,3,4,7,10};
    cout<<kthMissingHelper(nums,0,4,3)<<endl;
    cout<<kthMissingHelper(nums,2,3,2)<<endl;
}