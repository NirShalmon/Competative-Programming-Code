/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>

using namespace std;

int dp[301][301];

int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	dp[1][1] = 0;
	for(int i = 1; i <= n; ++i){
		for(int j= 1; j <= m; ++j){
			//cout<<i<<' '<<j<<endl;
			if(i == j) dp[i][j] = 0;
			else{
				dp[i][j] = 10000000;
				for(int k = 1; k < i; ++k){
					dp[i][j] = min(dp[i][j],dp[k][j] + dp[i-k][j] + 1);
				}
				for(int k = 1; k < j; ++k){
					dp[i][j] = min(dp[i][j],dp[i][k] + dp[i][j-k] + 1);
				}
			}
			//cout<<dp[i][j]<<endl;
		}
	}
	cout<<dp[n][m];
 }