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
    vector<TrieNode*> child;
    bool isWord;
};
class Trie {
    TrieNode* root;
public:
    /** Initialize your data structure here. */
    Trie();

    /** Inserts a word into the trie. */
    void insert(string& word);

    /** Returns if the word is in the trie. */
    bool search(string& word);


    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string& prefix);


    /** Returns word end where in the trie. */
    TrieNode* searchWordNode(string& word);
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

#endif //GOOGLE_TRIE_H
