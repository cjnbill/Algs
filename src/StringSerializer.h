//
// Created by cjn on 2018/4/14.
//

#ifndef ALGS_STRINGSERIALIZER_H
#define ALGS_STRINGSERIALIZER_H


#include <string>
#include <vector>

class StringSerializer {
public:
    StringSerializer();
    static std::string Encode(std::vector<std::string> strs);
    static std::vector<std::string> Decode(std::string str);
};


#endif //ALGS_STRINGSERIALIZER_H
