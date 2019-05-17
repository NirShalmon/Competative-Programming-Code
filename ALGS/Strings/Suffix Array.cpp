/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

vector<char> s;
int sa[1<<18];
int pa[2][1<<18];
int q = 1;
int o;
int bs;
vector<int> cnt[1<<18];

bool cmp1(const int &a,const int &b){
    return s[a] < s[b];
}

bool cmp2(const int &a,const int &b){
    return pa[o^1][a] != pa[o^1][b] ? pa[o^1][a] < pa[o^1][b] : pa[o^1][a + (1<<(q-1))] < pa[o^1][b + (1<<(q-1))];
}

void srt(int n,int d){
    for(int i = 0; i < 1<<bs; ++i) cnt[i].clear();
    for(int i = 0; i < n; ++i) cnt[pa[o^1][sa[i]+d]].push_back(sa[i]);
    int j = 0;
    for(int i = 0; i < 1<<bs; ++i){
        for(int x : cnt[i]) sa[j++] = x;
    }
}

int main() {
	ios::sync_with_stdio(false);
    string t;
    cin>>t;
    for(int i = 0; i < t.size(); ++i) s.push_back(t[i]);
	int osz = s.size();
	bs = 0;
	while(1<<bs < 2*s.size()) ++bs;
    while(s.size() < 1<<bs) s.push_back((char)127);
    for(int i = 0; i < 1<<bs; ++i) sa[i] = i;
    sort(sa,sa+(1<<bs),cmp1);
    pa[o][sa[0]] = 0;
    for(int i = 1; i < 1<<bs; ++i){
        if(!cmp1(sa[i-1],sa[i])) pa[o][sa[i]] = pa[o][sa[i-1]];
        else pa[o][sa[i]] = i;
    }
    for(q = 1; q < bs; ++q){
        o = q&1;
        for(int i = 0; i < 1<<bs; ++i) sa[i] = i;
        int n = (1<<bs) - (1<<q) + 1;
        srt(n,1<<(q-1));
        srt(n,0);
        pa[o][sa[0]] = 0;
        for(int i = 1; i < n; ++i){
            if(!cmp2(sa[i-1],sa[i])) pa[o][sa[i]] = pa[o][sa[i-1]];
            else pa[o][sa[i]] = i;
        }
    }
    for(int i = 0; i < osz; ++i) cout<<sa[i]<<' ';
}
