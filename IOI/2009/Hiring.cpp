/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

const int m = 1<<19;
int n;
long long w;
pair<long long,int> seg[2*m];
int s[500000];
pair<int,int> q[500000];
int rorder[500000];
int idxmp[500000];

bool cmp(int a,int b){
    return s[a] * q[b].first < s[b] * q[a].first;
}

void enable(int p,int v){
    seg[p+m] = {v,1};
    p = (p+m)/2;
    while(p){
        seg[p] = {seg[p*2].first + seg[p*2+1].first,seg[p*2].second+seg[p*2+1].second};
        p/=2;
    }
}

pair<long long,int> bs(long long ms,long long mq){
    int p = 1;
    if(seg[p].first * ms <= mq * w) return seg[1];
    int l = 0,r = 0;
    while(p < m){
        if((l + seg[p*2].first)* ms <= mq * w){
            l += seg[p*2].first;
            r += seg[p*2].second;
            p = p*2+1;
        }else p*=2;
    }
    return {l,r};
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>w;
    for(int i = 0; i < n; ++i){
        cin>>s[i]>>q[i].first;
        rorder[i] = i;
        q[i].second = i;
    }
    sort(rorder,rorder+n,cmp);
    sort(q,q+n);
    for(int i = 0; i < n; ++i){
        idxmp[q[i].second] = i;
    }
    int bestNum = 0,bestI;
    long long bestSum,bestms,bestmq;
    for(int i = 0; i < n; ++i){
        enable(idxmp[rorder[i]],q[idxmp[rorder[i]]].first);
        int ms = s[rorder[i]];
        int mq = q[idxmp[rorder[i]]].first;
        auto e = bs(ms,mq);
        if(e.second > bestNum || (e.second == bestNum && e.first * bestmq * ms < bestSum * bestms * mq)){
            bestNum = e.second;
            bestSum = e.first;
            bestms = ms;
            bestmq = mq;
            bestI = i;
        }
    }
    vector<int> selected;
    for(int i = 0; i < n; ++i){
        long long cidx = q[i].second;
        long long cq = q[i].first;
        long long cs = s[cidx];
        if(selected.size() == bestNum) break;
        if(cs * bestmq <= cq * bestms){
            selected.push_back(cidx);
        }
    }
    sort(selected.begin(),selected.end());
    cout<<bestNum<<'\n';
    for(int k : selected) cout<<k+1<<'\n';
}

