/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

unordered_map<char,int> m;
int sum;

int main(){
    ios::sync_with_stdio(false);
    int g,s;
    string w;
    int ans = 0;
    string f;
    cin>>g>>s>>w>>f;
    sum = g;
    for(char c : w) m[c]++;
    for(int i = 0; i < g; ++i){
        if(--m[f[i]] >= 0) --sum;
        else ++sum;
    }
    ans += sum==0;
    for(int i = g; i < s; ++i){
        if(--m[f[i]] >= 0) --sum;
        else ++sum;
        if(++m[f[i-g]] <= 0) --sum;
        else ++sum;
        ans += sum==0;
    }
    cout<<ans;
}

