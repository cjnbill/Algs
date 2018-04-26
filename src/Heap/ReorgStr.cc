//
// Created by cjn on 2018/4/22.
//
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
class ReorgStr {
public:
    struct cmp{
        bool operator()(pair<char,int> p1,pair<char,int> p2){
            return p1.second<p2.second;
        }
    };
    string reorganizeString(string S) {
        priority_queue<pair<char,int>,vector<pair<char,int>>,cmp> pq;
        unordered_map<char,int> count;
        for(auto c:S){
            count[c]++;
            if(count[c]>(S.size()+1)/2)
                return "";
        }
        for(auto p:count){
            pq.push(p);
        }
        string res="";
        while(!pq.empty()){
            auto t=pq.top();pq.pop();
            if(res.size()>0&&res.back()==t.first){
                auto sec=pq.top();pq.pop();
                res+=sec.first;
                sec.second--;
                if(sec.second>0)
                    pq.push(sec);
            }
            else{
                res+=t.first;
                t.second--;
            }
            if(t.second>0)
                    pq.push(t);
        }
        return res;
    }
};