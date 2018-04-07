//
// Created by cjn on 2018/4/6.
//

#include "Trie.h"

TrieNode::TrieNode():child(26, nullptr),isWord(false){}

Trie::Trie() {
    root = new TrieNode();
}

/** Inserts a word into the trie. */
void Trie::insert(string& word) {
    auto cur=root;
    for(auto &c : word) {
        int i=c-'a';
        if(!cur->child[i])cur->child[i] = new TrieNode();
        cur=cur->child[i];
    }
    cur->isWord=true;
}

/** Returns if the word is in the trie. */
bool Trie::search(string& word) {
    auto node = searchWordNode(word);
    if(!node)
        return false;
    return node->isWord;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool Trie::startsWith(string& prefix) {
    auto node=searchWordNode(prefix);
    return node!=nullptr;
}
/** Returns word end where in the trie. */
TrieNode* Trie::searchWordNode(string& word){
    auto cur = root;
    for (auto &c : word) {
        int i = c - 'a';
        if(!cur->child[i])return nullptr;
        cur = cur -> child[i];
    }
    return cur;
}