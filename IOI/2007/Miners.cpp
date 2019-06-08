/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
string s;
int dp[2][4][4][4][4]; //[mod][a-prev2][a-prev1][b-prev2][b-prev1]

int getId(char c){
    if(c == 'M') return 0;
    if(c == 'B') return 1;
    if(c == 'F') return 2;
    return 3;
}

int getVal(int a, int b, int c){
    if(a == 3){
        return 1;
    }
    if(b == 3){
        if(a == c) return 1;
        return 2;
    }
    if(a == b){
        if(a == c) return 1;
        else return 2;
    }else{
        if(a == c || b == c) return 2;
        return 3;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>s;
    for(int p2a = 0; p2a < 4;+ ++p2a){
        for(int p1a = 0; p1a < 4;+ ++p1a){
            for(int p2b = 0; p2b < 4;+ ++p2b){
                for(int p1b = 0; p1b < 4;+ ++p1b){
                    dp[1][p2a][p1a][p2b][p1b] = -1000000000;
                }
            }
        }
    }
    dp[1][3][3][3][3] = 0;
    for(int i = 0; i < n; ++i){
        int cid = getId(s[i]);
        int o = i&1;
        for(int p2a = 0; p2a < 4;+ ++p2a){
            for(int p1a = 0; p1a < 4;+ ++p1a){
                for(int p2b = 0; p2b < 4;+ ++p2b){
                    for(int p1b = 0; p1b < 4;+ ++p1b){
                        dp[o][p2a][p1a][p2b][p1b] = -1000000000;
                    }
                }
            }
        }
        for(int p2a = 0; p2a < 4;+ ++p2a){
            for(int p1a = 0; p1a < 4;+ ++p1a){
                for(int p2b = 0; p2b < 4;+ ++p2b){
                    for(int p1b = 0; p1b < 4;+ ++p1b){
                        dp[o][p1a][cid][p2b][p1b] = max(dp[o][p1a][cid][p2b][p1b],dp[o^1][p2a][p1a][p2b][p1b] + getVal(p1a,p2a,cid));
                        dp[o][p2a][p1a][p1b][cid] = max(dp[o][p2a][p1a][p1b][cid],dp[o^1][p2a][p1a][p2b][p1b] + getVal(p1b,p2b,cid));
                    }
                }
            }
        }
    }
    int ans = -1000000000;
    for(int p2a = 0; p2a < 4;+ ++p2a){
        for(int p1a = 0; p1a < 4;+ ++p1a){
            for(int p2b = 0; p2b < 4;+ ++p2b){
                for(int p1b = 0; p1b < 4;+ ++p1b){
                    ans = max(ans,dp[(n-1)&1][p2a][p1a][p2b][p1b]);
                }
            }
        }
    }
    cout<<ans;
}

