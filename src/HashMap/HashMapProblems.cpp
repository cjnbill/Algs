//
// Created by cjn on 2018/5/16.
//

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//49. Group Anagrams
//sort
//hashmap
class GroupAnagrams {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> m;
        for (string str : strs) {
            vector<int> cnt(26, 0);
            string t = "";
            for (char c : str) ++cnt[c - 'a'];
            for (int d : cnt) t += to_string(d) + "/";
            m[t].push_back(str);
        }
        for (auto a : m) {
            res.push_back(a.second);
        }
        return res;
    }
};

//438. Find All Anagrams in a String
class AllAnagrams {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> pv(26,0), sv(26,0);
        vector<int> res;
        int m=s.size(),n=p.size();
        for(int i=0;i<n;i++){
            pv[p[i]-'a']++;
            sv[s[i]-'a']++;
        }
        if(pv==sv)
            res.push_back(0);
        for(int i=n;i<m;i++){
            sv[s[i]-'a']++;
            sv[s[i-n]-'a']--;
            if(sv==pv)
                res.push_back(i-n+1);
        }
        return res;
    }
};

//242. Valid Anagram
class IsAnagram {
public:
    bool isAnagram(string s, string t) {
        // simple way
        int check[26] = {0};
        if(s.length() != t.length()) return false;

        for(int i = 0; i < s.length(); i++)
        {
            check[s[i]-'a']++;
            check[t[i]-'a']--;
        }

        for(int i = 0;i< 26; i++)
        {
            if(check[i] != 0)
                return false;
        }
        return true;

    }
};


//760. Find Anagram Mappings
vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
    //handle duplicates
    unordered_map<int, vector<int>> m;
    for (int i = 0; i < B.size(); ++i) m[B[i]].push_back(i);

    vector<int> out(A.size(), 0);
    for (int i = 0; i < A.size(); ++i) {
        vector<int>& v = m[A[i]];
        out[i] = v.back();
        v.pop_back();
    }
    return out;
}

//659. Split Array into Consecutive Subsequences
class ConsecutiveSeq {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> freq, need;
        for (int num : nums) ++freq[num];
        for (int num : nums) {
            if (freq[num] == 0) continue;
            else if (need[num] > 0) {
                --need[num];
                ++need[num + 1];
            } else if (freq[num + 1] > 0 && freq[num + 2] > 0) {
                --freq[num + 1];
                --freq[num + 2];
                ++need[num + 3];
            } else return false;
            --freq[num];
        }
        return true;
    }
};

//205. Isomorphic Strings
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size()!=t.size())
            return false;
        return helper(s,t)&&helper(t,s);
    }
    bool helper(string s,string t){
        unordered_map<char,char> m1;
        for(int i=0;i<s.size();i++){
            if(m1.count(s[i])){
                if(m1[s[i]]!=t[i])
                    return false;
            }
            m1[s[i]]=t[i];
        }
        return true;
    }
};