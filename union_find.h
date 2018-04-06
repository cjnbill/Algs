//
// Created by cjn on 2018/4/5.
//

#ifndef GOOGLE_UNION_FIND_H
#define GOOGLE_UNION_FIND_H

#include <vector>

class union_find {
public:
    union_find(std::vector<std::vector<char>>& grid);
    int find(int x);
    void unin(int a,int b);

    std::vector<int> father;
    int count=0;
};

int numIslands(std::vector<std::vector<char>>& grid);
#endif //GOOGLE_UNION_FIND_H
