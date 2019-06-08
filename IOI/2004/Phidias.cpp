/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int w,h,n;
int dp[601][601];
unordered_set<int> plates;

int conv(int x,int y){
    return x * 1000 + y;
}

int main(){
    ios::sync_with_stdio(false);
    cin>>w>>h>>n;
    for(int i = 0; i < n; ++i){
        int x,y;
        cin>>x>>y;
        plates.insert(conv(x,y));
    }
    for(int i = 1; i <= w; ++i){
        for(int j = 1; j <= h; ++j){
            if(plates.find(conv(i,j)) != plates.end()){
                dp[i][j] = 0;
            }else{
                dp[i][j] = i * j;
                for(int c = 1; c < i; ++c){
                    dp[i][j] = min(dp[i][j],dp[c][j] + dp[i-c][j]);
                }
                for(int c = 1; c < j; ++c){
                    dp[i][j] = min(dp[i][j],dp[i][c] + dp[i][j-c]);
                }
            }
        }
    }
    cout<<dp[w][h];
}

