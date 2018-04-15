//
// Created by cjn on 2018/4/14.
//

#include "StringSerializer.h"

std::string StringSerializer::Encode(std::vector<std::string> strs){
    std::string res;
    for(const auto& str:strs){
        res+=std::to_string(str.size())+"@"+str;
    }
    return res;
}
std::vector<std::string> StringSerializer::Decode(std::string str){
    std::vector<std::string> res;
    int i=0;
    while(i<str.size()){
        auto cur=str.find_first_of('@',i);
        int len=std::stoi(str.substr(i,cur-i));
        res.push_back(str.substr(cur+1,len));
        i=cur+len+1;
    }
    return res;
}