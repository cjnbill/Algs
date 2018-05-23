//
// Created by cjn on 2018/5/19.
//
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;



//527. Word Abbreviation
class WordsAbbr {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n=dict.size();
        unordered_map<string,int> cnt;
        vector<int> prefix(n,1);
        vector<string> res(n);
        for(int i=0;i<n;i++){
            string ab=abbr(dict[i],1);
            cnt[ab]++;
            res[i]=ab;
        }
        while(true){
            bool unique=true;
            for(int i=0;i<n;i++){
                if(cnt[res[i]]>1){
                    prefix[i]++;
                    res[i]=abbr(dict[i],prefix[i]);
                    cnt[res[i]]++;
                    unique=false;
                }
            }
            if(unique)
                break;
        }
        return res;
    }
    string abbr(string s,int p){
        if(p+2>=s.size())
            return s;
        return s.substr(0,p)+to_string(s.size()-1-p)+s.back();
    }
};


//408. Valid Word Abbreviation
class ValidWordAbbr {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int i=0,j=0;
        int m=word.size(),n=abbr.size();
        int num=0;
        while(i<m&&j<n){
            if(isdigit(abbr[j])){
                num=0;
                if(abbr[j]=='0')
                    return false;

                while(j<n&&isdigit(abbr[j])){
                    num=10*num+abbr[j]-'0';
                    j++;
                }
                i+=num;
            }
            else{
                if(word[i++]!=abbr[j++])
                    return false;
            }
        }
        return i==m&&j==n;
    }
};


class DecodeStr {
public:
    string decodeString(string s) {
        string t = "";
        stack<int> s_num;
        stack<string> s_str;
        int cnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                cnt = 10 * cnt + s[i] - '0';
            } else if (s[i] == '[') {
                s_num.push(cnt);
                s_str.push(t);
                cnt = 0; t.clear();
            } else if (s[i] == ']') {
                int k = s_num.top(); s_num.pop();
                for (int j = 0; j < k; ++j) s_str.top() += t;
                t = s_str.top(); s_str.pop();
            } else {
                t += s[i];
            }
        }
        return t;
    }
};


//Encode repeat char

void AppendChars(string s, int start, int end, string sb)
{
    char c = s[start];
    int lenght = end - start;

    // Handle the case when there is a number befor the sub string.
    bool afterNumber = (start > 0 && s[start - 1] >= '1' && s[start - 1] <= '9');
    int n = afterNumber ? 4 : 3;

    if (afterNumber)
    {
        lenght--;
        sb.push_back(c);
    }

    if (lenght <= 3)
        sb=sb+string(lenght,c);
    else
        sb=sb+to_string(lenght)+"x"+ c;
}
static string Encode(string s)
{
    string res;
    int j = 0;
    for (int i=0; i < s.size(); i++)
    {
        if (i > 0 && (s[i] == 'x' || s[i] == 'X') && s[i-1] >= '1' && s[i-1] <= '9')
        {
            res.push_back(s[i - 1]);
            res=res+"1x"+s[i];
            j = i+1;
            continue;
        }
        if (s[i] == s[j])
            continue;

        AppendChars(s, j, i, res);
        j = i;
    }

    AppendChars(s, j, s.size(), res);

    return res;
}

