/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

//#define dp(i,j) dpp[i%2][j]
#define mod 100000

long long dp[2][10001];
long long ans = 0;

int main(){
	int n,k;
	cin>>n>>k;
	dp[1][1] = 1;
	for(int r = 2; r <= n; ++r){
		for(int i = 1; i <= min(r,k); ++i){
			dp[r%2][i] = ((dp[(r-1)%2][i] * ((r-1))) % mod + dp[(r-1)%2][i-1]) % mod;  
			//if(r != n) 	ans = (ans * (((r + (i != k)) * dp[r%2][i]) % mod)) % mod;
			//cout<<dp[r%2][i]<<' ';
		}
		//cout<<endl;
	}
	/*long long nfac = 1;
	for(int i = 2; i <= n; ++i) nfac = (nfac * i) % mod;
	*/for(int i = 1; i <= k; ++i) ans = (ans + dp[n%2][i]) % mod;
	/*ans = (ans * nfac) % mod; */
	cout<<ans;
}