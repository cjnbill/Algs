//
// Created by cjn on 2018/5/17.
//

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class PyramidTransition {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_map<string, unordered_set<char>> m;
        for (string str : allowed) {
            m[str.substr(0, 2)].insert(str[2]);
        }
        return helper(bottom, "", m);
    }
    bool helper(string cur, string above, unordered_map<string, unordered_set<char>>& m) {
        if (cur.size() == 2 && above.size() == 1) return true;
        if (above.size() == cur.size() - 1) return helper(above, "", m);
        int pos = above.size();
        string base = cur.substr(pos, 2);
        if (m.count(base)) {
            for (char ch : m[base]) {
                if (helper(cur, above + string(1, ch), m)) {
                    return true;
                }
            }
        }
        return false;
    }
};

class GenAbbr {
private:
    void generateAbbreviations(vector<string>& result, string word, int begin) {
        int size = word.size(); // size of word changes during the abbreviation process; need to recalculate evey time

        if (begin >= size) {
            result.push_back(word);
            return;
        }

        // No abbreviations
        result.push_back(word);

        // Abbreviations size from 1 to size-begin
        for (int i = 1; i <= size-begin; i++) { // i is the abbreviation size
            string abbr = to_string(i);
            int abbr_size = abbr.size();
            for (int j = begin; j <= size-i; j++) { // j is the location of abbreviations
                string post = i+j < size ? word.substr(i+j) : "";
                generateAbbreviations(result, word.substr(0, j) + abbr + post, j+abbr_size+1);
            }
        }
    }

public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        generateAbbreviations(result, word, 0);

        return result;
    }
};