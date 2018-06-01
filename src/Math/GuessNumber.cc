//
// Created by cjn on 2018/4/16.
//
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class BullsAndCows {
public:
    string getHint(string secret, string guess) {
        int m[256] = {0}, bulls = 0, cows = 0;
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) ++bulls;
            else ++m[secret[i]];
        }
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] != guess[i] && m[guess[i]]) {
                ++cows;
                --m[guess[i]];
            }
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};


//guess word
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Master {
    public:
    int guess(string word);
};
class GuessWord {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int cnt=0;
        srand(time(0));
        while(cnt<10&&!wordlist.empty()){
            cout<<cnt<<" "<<wordlist.size()<<endl;
            vector<string> tmp;
            auto cur_guess=wordlist[rand()%wordlist.size()];
            int cur_match=master.guess(cur_guess);
            if(cur_match==cur_guess.size())
                return;
            for(auto word:wordlist){
                if(guess(word,cur_guess)==cur_match)
                    tmp.push_back(word);
            }
            wordlist=tmp;
            cnt++;
        }
    }
    int guess(string t,string s){
        int res=0;
        for(int i=0;i<s.size();i++){
            if(t[i]==s[i])
                res++;
        }
        return res;
    }
};