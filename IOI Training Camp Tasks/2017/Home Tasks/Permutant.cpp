/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
long long l[100000],r[100000];
long long dp[4][100000];
const long long inf = 1000000000000ll;

long long dif(int i,int j){
    return abs(l[i]-r[j]);
}

long long tot(int i){
    return min(min(dp[0][i],dp[1][i]),min(dp[2][i],dp[3][i]));
}

long long reg1(int i){
    return l[i] == r[i] ? inf : dif(i,i) + tot(i-1);
}

long long reg0(int i){
    return l[i] == r[i-1] || l[i-1] == r[i] ? inf : dif(i,i-1) + dif(i-1,i) + tot(i-2);
}

long long reg2(int i){
    long long base = l[i] == r[i-1] || l[i-1] == r[i-2] || l[i-2] == r[i] ? inf :
        dif(i,i-1) + dif(i-1,i-2) + dif(i-2,i);
    if(i > 2) return base + tot(i-3);
    return base;
}

long long reg3(int i){
    long long base = r[i] == l[i-1] || r[i-1] == l[i-2] || r[i-2] == l[i] ? inf :
        dif(i-1,i) + dif(i-2,i-1) + dif(i,i-2);
    if(i > 2) return base + tot(i-3);
    return base;
}


int main() {
	ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 0; i < n;++i) cin>>l[i]>>r[i];
    sort(l,l+n);
    sort(r,r+n);
    dp[0][0] = inf;
    dp[2][0] = inf;
    dp[1][0] = l[0] == r[0] ? inf : dif(0,0);
    dp[3][0] = inf;
    if(n == 1){
        cout<<dif(0,0);
        return 0;
    }
    dp[1][1] = reg1(1);
    dp[0][1] = l[1] == r[0] || r[0] == l[1] ? inf : dif(0,1) + dif(1,0);
    dp[2][1] = inf;
    dp[3][1] = inf;
    if(n == 2){
        cout<<min(dp[0][1],dp[1][1]);
        return 0;
    }
    dp[0][2] = reg0(2);
    dp[1][2] = reg1(2);
    dp[2][2] = reg2(2);
    dp[3][2] = reg3(2);
    for(int i = 3; i < n; ++i){
        dp[0][i] = reg0(i);
        dp[1][i] = reg1(i);
        dp[2][i] = reg2(i);
        dp[3][i] = reg3(i);
    }
    cout<<tot(n-1);
}
