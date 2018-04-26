//
// Created by cjn on 2018/4/5.
//

#ifndef GOOGLE_UNION_FIND_H
#define GOOGLE_UNION_FIND_H

#include <vector>

class UnionFind {
public:
    explicit UnionFind(std::vector<std::vector<char>>& grid);
    int Find(int x);
    void Union(unsigned long a, unsigned long b);

    std::vector<int> father_;
    int count_=0;
};

int NumOfIslands(std::vector<std::vector<char>> &grid);
#endif //GOOGLE_UNION_FIND_H
