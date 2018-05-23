//
// Created by cjn on 2018/5/21.
//
#include <string>
using namespace std;
class FontSize{
public:
    static int getHeight(char c,int font);
    static int getWidth(char c,int font);

    int GetLargestFont(string s,int H,int W,int smallest,int largest){
        int l=smallest,r=largest;
        while(l+1<r){
            int mid=l+(r-l)/2;
            if(CanFit(s,H,W,mid))
                l=mid;
            else
                r=mid;
        }
        if(CanFit(s,H,W,r))
            return r;
        return l;
    }
    bool CanFit(string s,int H,int W,int font){
        int n=s.size();
        int i=0,totalH=0,curW=0,curH=0;
        while(i<n){
            if (curW+getWidth(s[i],font)<=W){
                curW+=getWidth(s[i],font);
                curH=max(curH,getHeight(s[i],font));
            }
            else{
                curW=getWidth(s[i],font);
                curH=getHeight(s[i],font);
            }
            i++;
            if(totalH+curH>H)
                return false;
        }
        return true;
    }
};