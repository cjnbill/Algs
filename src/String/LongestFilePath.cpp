//
// Created by cjn on 2018/5/21.
//

#include <stdio.h>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;
class LongestFilePath {
public:
    int lengthLongestPath(string input) {
        stringstream ss(input);
        string line;
        unordered_map<int,int> hash;
        hash[0]=0;
        int res=0;
        while(getline(ss,line)){
            size_t pos = line.find_last_of('\t');
            int level = (pos == string::npos) ? 1 : (level = pos + 2);
            int num_tab=level-1;
            hash[level]=hash[level-1]+line.size()-num_tab+1;
            if(line.find(".")!=string::npos){
                res=max(res,hash[level]-1);
            }
        }
        return res;
    }
};