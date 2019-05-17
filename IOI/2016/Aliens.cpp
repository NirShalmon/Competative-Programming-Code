/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include "aliens.h"
#include<map>
#include<set>

using namespace std;

int N,M,K;
map<int,int> mp;
vector<long long> r,l;
long long g[1000000];
long long a[1000000],b[1000000];
vector<pair<long long,long long>> lines;
vector<int> pc;

long long sqr(long long x){
return x*x;
}

//notation from official solution
pair<int,long long> getPval(long long c){
    g[0] = 0;
    lines.clear();
    pc.clear();
    lines.push_back({2*(-l[0]),sqr(-l[0])+c});
    pc.push_back(0);
    int lastLine = 0;
    long long vt = 0;
    int lineId = 0;
    for(int i = 1; i <= N; ++i){
        long long v0 = sqr(r[i-1]);
        if(lastLine >= lines.size()) lastLine = lines.size()-1;
        while(lastLine < lines.size() - 1){
            long long a1 = lines[lastLine].first;
            long long a2 = lines[lastLine+1].first;
            long long b1 = lines[lastLine].second;
            long long b2 = lines[lastLine+1].second;
            long long x = r[i-1];
            if(a1*x + b1 > a2*x+b2) ++lastLine;
            else break;
        }
        vt = v0 + lines[lastLine].first * r[i-1] + lines[lastLine].second;
        g[i] = vt;
        lineId = pc[lastLine];
        long long a = 2*(-l[i]);
        long long b = g[i] + sqr(-l[i]) - sqr(max(0ll,r[i-1]-l[i]))+c;
        while((lines.size() > 0 && lines.back().second > b)
              || (lines.size() > 1 && (lines.back().second-b)*(lines.back().first - lines[lines.size()-2].first) < (lines[lines.size()-2].second-lines.back().second)*(a-lines.back().first))){
            lines.pop_back(),pc.pop_back();
        }
        lines.push_back({a,b});
        pc.push_back(pc[lastLine]+1);
    }
    return {lineId+1,vt};
}

long long take_photos(int n, int m, int k, std::vector<int> R, std::vector<int> C) {
    for(int i = 0; i < n; ++i){
        if(R[i] > C[i]) swap(R[i],C[i]);
        if(mp.find(R[i]) != mp.end()){
            mp[R[i]] = max(mp[R[i]],C[i]+1);
        }else mp.insert({R[i],C[i]+1});
    }
    for(auto &x : mp) {
        if(r.size() == 0 || x.second > r.back()){
            r.push_back(x.second);
            l.push_back(x.first);
        }
    }
    n = r.size();
    N = n;
    M = m;
    K = k;
    long long lo = 0;
    long long hi = (long long)(m) * m;
    while(lo < hi){
        long long mid = (lo+hi+1)/2;
        int val = getPval(mid).first;
        if(val >= k) lo = mid;
        else hi = mid-1;
    }
    auto pv = getPval(lo);
    auto p2v = getPval(lo+1);
    long long f1 = pv.second - pv.first*lo;
    long long f2 = p2v.second - p2v.first * (lo+1);
    long long f = p2v.first != pv.first ? (k-pv.first) * f2 / (p2v.first - pv.first) + f1 - (k-pv.first) *f1 / (p2v.first - pv.first) : f1;
    return f;
}
