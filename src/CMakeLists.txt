cmake_minimum_required(VERSION 3.10)
project(algs)

set(CMAKE_CXX_STANDARD 11)

add_executable(algs main.cc SlidingWindow/LongestSubwithK.cc SlidingWindow/LongestSubwithK.h Graph/UnionFind/UnionFind.cc
        Graph/UnionFind/UnionFind.h Trie/Trie.cc Trie/Trie.h SegmentTree Heap/MedianFinder.cc
        FiboHeap BinarySearch/QuickSortAndSelect.cc String/StringSerializer.cc String/StringSerializer.h
        Graph/DFS/SweepRobot.cc Graph/BFS/TreasureFind.cc Math/GuessNumber.cc Math/RandomSelectFromRectangle.cc
        Heap/ChairDistance.cc Graph/DFS/DfsProblems.cc Graph/BFS/BfsProblems.cc Stack/BasicCalculator.cc Graph/DFS/SnakeGame.cc
        Graph/DFS/SnakeGame.h Heap/ReorgStr.cc DP/Game.cpp Math/MooreVote.cpp Heap/BalancedTree.cpp Tree/TreeProblems.cpp)
