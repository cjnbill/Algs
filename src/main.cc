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

vector<vector<int>> gen_table(int n){
    if(n<0)
        return {};
    vector<vector<int>> table(n,vector<int>(n,-1));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            auto color=rand()%3;
            if(i<2&&j<2) {
                table[i][j] = color;
                continue;
            }

            bool flag =  false;
            while(!flag){
                if((j>=2&&(table[i][j-1]==color&&table[i][j-2]==color))
                   ||(i>=2&&(table[i-1][j]==color&&table[i-2][j]==color)))
                    color=rand()%3;
                else flag=true;
            }
            table[i][j]=color;
        }
    }
    return table;
}


int main()
{
    vector<int> nums={2,7};
    cout<<countingSort(nums,2,0,2);
}