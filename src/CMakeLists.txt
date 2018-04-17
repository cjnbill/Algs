cmake_minimum_required(VERSION 3.10)
project(algs)

set(CMAKE_CXX_STANDARD 11)

add_executable(algs main.cc LongestSubwithK.cc LongestSubwithK.h UnionFind.cc
        UnionFind.h Trie.cc Trie.h SegmentTree.cc SegmentTree.h MedianFinder.cc
        FiboHeap QuickSortAndSelect.cc StringSerializer.cc StringSerializer.h SweepRobot.cc TreasureFind.cc GuessNumber.cc)