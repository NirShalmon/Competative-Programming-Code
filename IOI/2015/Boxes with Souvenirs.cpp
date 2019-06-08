/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>
#pragma GCC optimize ("O3")

using namespace std;

long long n,k,s;
deque<long long> l,r;
long long lm[10000000],rm[10000000];
long long center = 0;
const long long inf = 999999999999999999ll;

inline int scan(){
    int x = 0;
    char c = getchar_unlocked();
    while(c < '0' || c > '9') c = getchar_unlocked();
    while(c >= '0' && c <= '9'){
        x = x*10 + c - '0';
        c = getchar_unlocked();
    }
    return x;
}

void work(long long *m,deque<long long> &a){
    fill_n(m,k,inf);
    for(int i = k; i < a.size(); ++i) a[i] += a[i-k];
    for(int i = 0; i < a.size(); ++i){
        m[i%k] = min(m[i%k],a[a.size()-i-1]*2 + (i/k) * s);
    }
    for(int i = a.size(); i < a.size() + k; ++i) m[i%k] = min(m[i%k],(i/k)*s);
}

int main(){
    //ios::sync_with_stdio(false);
    n = scan(); k = scan(); s = scan();
    int t = s + (s&1);
    for(int i = 0; i < n; ++i) {
        int x = scan();
        if(x == 0) continue;
        if(s & 1 && x * 2 > s) ++x;
        if(x * 2 < t) l.push_back(x);
        else if(x * x == t) ++center;
        else r.push_front(t - x);
    }
    work(lm,l);
    work(rm,r);
    long long baseCost = (center / k) * s;
    center %= k;
    long long ans = inf;
    for(int i = 0; i < k; ++i){
        int j = (2*k - i - center) % k;
        ans = min(ans,lm[i] + rm[j] + ((i+j+center)/k) *s);
    }
    cout<<ans + baseCost;
}

