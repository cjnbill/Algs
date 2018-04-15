#include <iostream>
using namespace std;

#include "QuickSortAndSelect.cpp"
#include "StringSerializer.h"

int main()
{
    vector<string> strs={"abc","cbaa","a"};
    auto encoded_str=StringSerializer::Encode(strs);
    cout<<encoded_str<<endl;
    auto decoded_strs=StringSerializer::Decode(encoded_str);
    for(auto str:decoded_strs){
        cout<<str<<endl;
    }
}