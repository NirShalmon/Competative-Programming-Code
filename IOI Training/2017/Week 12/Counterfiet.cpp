/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

long long inf = 999999999999999ll;
long long dp[1000001];
long long n,e,u;

long long calc1(long long i, long long k){
    return  u + dp[k]-(e + dp[i-2*k]);
}

long long calc2(long long i, long long k){
    return max(u + dp[k],(e + dp[i-2*k]));
}

long long ok(){
    dp[1] = 0;
    dp[0] = -inf;
    for(long long i = 2; i <= n; ++i){
        dp[i] = inf;
        for(long long k = 1; k * 2 <= i; ++k){
            dp[i] = min(dp[i],max(u + dp[k],e + dp[i-2*k]));
        }
        if(n > i) dp[i] = min(dp[i],u+max(dp[i/2],dp[(i+1)/2]));
    }
    return dp[n];
}

long long bug(){
    dp[1] = 0;
    dp[0] = -inf;
    for(long long i = 2; i <= n; ++i){
        dp[i] = inf;
        int bk = 0;
        long long lo = 1,hi = (i/2);
        while(lo < hi){
            long long mid = (lo+hi)/2;
            long long t = calc1(i,mid);
            if(t < 0){
                lo = mid+1;
            }else if(t > 0){
                hi = mid-1;
            }else{
                lo = mid;
                hi = mid;
            }
        }
        if(lo > 1 && calc2(i,lo) > calc2(i,lo-1))--lo;
        if(lo < i/2 && calc2(i,lo) > calc2(i,lo+1))++lo;
        dp[i] = min(min(calc2(i,lo),calc2(i,1)),calc2(i,i/2));
        if(n > i) dp[i] = min(dp[i],u+max(dp[i/2],dp[(i+1)/2]));
        /*if(dp[i] < dp[i-1]){
            cout<<"err";
        }*/
       // cout<<i<<' '<<dp[i]<<' '<<(double)i/bk<<endl;
    }
    return dp[n];
}

int main(){
    ios::sync_with_stdio(0);
    cin>>n>>e>>u;
    /*while(true){
        n = rand() % 10;
        e = rand() % 8;
        u=  rand() % 8;
        long long a = ok();
        long long b = bug();
        if(a != b){
            cout<<"f!";
        }
    }*/
    bug();
    cout<<dp[n];
}
