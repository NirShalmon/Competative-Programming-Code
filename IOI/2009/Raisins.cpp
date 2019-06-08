/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n,m;
int a[50][50];
long long dp[50][50][50][50];
bool done[50][50][50][50];
int ps[50][50];

int getRect(int up, int left, int bottom, int right){
    int l = left > 0 ? ps[bottom][left-1] : 0;
    int t = up > 0 ? ps[up-1][right] : 0;
    int lt = up > 0 && left > 0 ? ps[up-1][left-1] : 0;
    return ps[bottom][right] - l - t + lt;
}

long long calc(int i,int j, int t,int k){
    if(i == t && j == k) return 0;
    if(done[i][j][t][k]) return dp[i][j][t][k];
     dp[i][j][t][k] = 1000000000000000ll;
    int rectVal = getRect(i,j,t,k);
    for(int c = i; c < t; ++c){
        dp[i][j][t][k] = min(dp[i][j][t][k],rectVal + calc(i,j,c,k)+ calc(c+1,j,t,k));
    }
    for(int c = j; c < k; ++c){
        dp[i][j][t][k] = min(dp[i][j][t][k],rectVal + calc(i,j,t,c) + calc(i,c+1,t,k));
    }
    done[i][j][t][k] = true;
    return dp[i][j][t][k];
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin>>a[i][j];
            ps[i][j] = a[i][j];
            if(i) ps[i][j] += ps[i-1][j];
            if(j) ps[i][j] += ps[i][j-1];
            if(i&&j) ps[i][j] -= ps[i-1][j-1];
        }
    }
    cout<<calc(0,0,n-1,m-1);
}

