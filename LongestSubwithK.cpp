//
// Created by cjn on 2018/4/5.
//

#include "LongestSubwithK.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int lengthOfLongestSubstringKDistinct(string s, int k) {
    if(s.empty()||k<0)
        return 0;
    int n=s.size();
    vector<int> m(256);
    int l=0,r=0,cnt=0,res=0;
    while(r<n){
        if(++m[s[r++]]==1)cnt++;
        //exceed k distinct
        if(cnt>k){
            if(--m[s[l++]]==0)cnt--;
        }
        res=max(res,r-l);
    }
    return res;
}
