//
// Created by cjn on 2018/4/6.
//

#ifndef GOOGLE_TRIE_H
#define GOOGLE_TRIE_H

#include <vector>
#include <string>
using namespace std;

class TrieNode{
public:
    TrieNode();
    vector<TrieNode*> child_;
    bool is_word_;
};
class Trie {
    TrieNode* root_;
public:
    /** Initialize your data structure here. */
    Trie();

    /** Inserts a word into the trie. */
    void Insert(string &word);

    /** Returns if the word is in the trie. */
    bool Search(string &word);


    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool StartWith(string &prefix);


    /** Returns word end where in the trie. */
    TrieNode* SearchWordNode(string &word);
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

#endif //GOOGLE_TRIE_H
