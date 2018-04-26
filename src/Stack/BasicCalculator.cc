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
        //push the sign of this term and res before this term
        else if(c=='('){
            st.push(res);
            st.push(sign);
            res=0;
            sign=1;
        } else if(c==')'){
            //pop the sign of this term and add the res before this term
            res*=st.top();st.pop();
            res+=st.top();st.pop();
        }
    }
    return res;
}
static int BasicCalculator2(string s) {
    int res = 0, d = 0;
    char sign = '+';
    stack<int> nums;
    int n=s.size();
    for (int i=0;i<n;i++) {
        if(isdigit(s[i])){
            while (i<n&&isdigit(s[i])) {
                d = d * 10 + s[i] - '0';
                i++;
            }
            i--;
        }
        if((s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')||i==n-1){
            if (sign == '+') nums.push(d);
            if (sign == '-') nums.push(-d);
            if (sign == '*' || sign == '/') {
                int tmp = sign == '*' ? nums.top() * d : nums.top() / d;
                nums.pop();
                nums.push(tmp);
            }
            sign = s[i];
            d = 0;
        }

    }
    while (!nums.empty()) {
        res += nums.top();
        nums.pop();
    }
    return res;
}