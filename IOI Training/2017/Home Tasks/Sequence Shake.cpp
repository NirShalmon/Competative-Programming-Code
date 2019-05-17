/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, m;
long long dp[2][10001];
const int mod = 1000000007;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	dp[1][0] = 1;
	for (int i = 2; i <= n; ++i) {
		int o = i & 1;
		int p = o ^ 1;
		dp[o][0] = 1;
		for (int j = 1; j <= i - 1; ++j) dp[o][j] = (dp[o][j - 1] + dp[p][j]) % mod;
		for (int j = i; j <= m; ++j) dp[o][j] = (dp[o][j - 1] + dp[p][j] - dp[p][j - i] + mod) % mod;
	}
	cout << dp[n & 1][m];
}