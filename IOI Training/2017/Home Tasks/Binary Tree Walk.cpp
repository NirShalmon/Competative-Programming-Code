/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

//vector<unsigned long long> v;

vector<short> add(const vector<short> &a,const vector<short> &b){
    int carry = 0;
    int maxsz = max(a.size(),b.size());
    int minsz = min(a.size(),b.size());
    vector<short> ans(maxsz);
    for(int i = 0; i < maxsz;++i){
        if(i < a.size()) ans[i] += a[i];
        if(i < b.size()) ans[i] += b[i];
        if(carry) ans[i] += carry;
        carry = ans[i] / 10;
        ans[i] = ans[i] % 10;
    }
    if(carry) ans.push_back(carry);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    string s;
    cin>>s;
    vector<short> a2 = {0},a1 = {1};
    vector<short> one = {1};
    vector<short>  pt = {1};
     vector<short> ppt = {1};
     char l = '0';
    for(int i = s.size() - 1; i >= 0; --i){
        if(s[i] != 'P'){
            ppt = pt;
            pt = add(pt,pt);
        }
        if(s[i] == 'L'){
            a1 = add(a1,a1);
        }else if(s[i] == 'R'){
            a2 = add(a1,a2);
            a1 = add(a1,a1);
        }else if(s[i] == '*'){
            auto t = add(a1,a1);
            t = add(t,t);
            a2 = add(a2,add(a2,add(a2,a1)));
            a1 = add(t,a1);
        }
        l = s[i];
    }
    auto ans = add(a1,a2);
    for(int i = ans.size() -1; i >= 0; --i)cout<<ans[i];
}
