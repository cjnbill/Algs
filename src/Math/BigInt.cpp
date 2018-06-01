//
// Created by cjn on 2018/5/26.
//
#include <string>
using namespace std;

//use carry digit by digit
static string addStrings(string num1, string num2) {
    // Write your code here
    string ans = "";

    int carry = 0;
    for (int i = num1.size() - 1, j = num2.size() - 1; i >= 0 || j >= 0; i--, j--) {
        int sum = carry;
        sum += (i >= 0) ? num1[i] - '0' : 0;
        sum += (j >= 0) ? num2[j] - '0' : 0;
        ans = (sum % 10) + ans;
        carry = sum / 10;
    }
    if (carry != 0) {
        ans = carry + ans;
    }
    return ans;
}

//calculate first then process carry
static string multiply(string num1, string num2) {
    // Write your code here
    int l1 = num1.size();
    int l2 = num2.size();

    int ans[l1 + l2 + 1];
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < l2; j++) {
            ans[i + j] += (num1[l1 - 1 - i] - '0') * (num2[l2 - 1 - j] - '0');
        }
    }

    for (int i = 0; i < l1 + l2; i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }

    int i = l1 + l2;
    while (ans[i] == 0 && i >= 1) {
        i--;
    }
    string str = "";
    while (i >= 0) {
        str += ans[i--];
    }
    return str;
}