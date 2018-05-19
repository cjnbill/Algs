//
// Created by cjn on 2018/5/18.
//
#include <vector>
using namespace std;

class NextPermutation {
public:
    void nextPermutation(vector<int> &num) {
        int j=0,i=0;
        for(i=num.size()-1;i>0;i--){
            if(num[i-1]<num[i]){
                j=num.size()-1;
                while(j>i-1){
                    if(num[j]>num[i-1]){
                        swap(num[i-1],num[j]);
                        break;
                    }
                    j--;
                }
                reverse(num.begin()+i,num.end());
                return;
            }
        }
        reverse(num.begin(),num.end());
    }
};