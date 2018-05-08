//
// Created by cjn on 2018/5/5.
//
#include <map>
#include <iostream>
using namespace std;
class BalancedTree{
public:
    //
    void test(int val){
        //find first value which is greater or equal to val
        auto l=m.lower_bound(val);
        //find first value bigger than val
        auto r=m.upper_bound(val);
        cout<<(l->first)<<" "<<r->first<<endl;
    }

private:
    map<int,int> m;
};