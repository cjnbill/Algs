//
// Created by cjn on 2018/4/21.
//

#include <string>
#include <stack>
using namespace std;
static int BasicCalculator1(string s){
    int res=0,sign=1,n=s.size();
    stack<int> st;
    for(int i=0;i<n;i++){
        char c = s[i];
        if(isdigit(c)){
            int tmp=0;
            while(i<n&&isdigit(s[i])){
                tmp=tmp*10+s[i]-'0';
                i++;
            }
            res+=tmp*sign;
            i--;
        }
        else if(c=='-'){
            sign=-1;
        }
        else if(c=='+'){
            sign=1;
        }
        else if(c=='('){
            st.push(res);
            st.push(sign);
            res=0;
            sign=1;
        } else if(c==')'){
            res*=st.top();st.pop();
            res+=st.top();st.pop();
        }
    }
    return res;
}