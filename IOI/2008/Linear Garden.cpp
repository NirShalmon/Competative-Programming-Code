/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int dp[1000001][3][3];
int n, mod;
string s;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> mod >> s;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			dp[0][i][j] = 1;
			if (i) dp[1][i][j]++;
			if (j) dp[1][i][j]++;
		}
	}
	for (int l = 2; l <= n; ++l) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i) dp[l][i][j] = (dp[l][i][j] + dp[l-1][i - 1][min(j + 1, 2)]) % mod;
				if (j) dp[l][i][j] = (dp[l][i][j] + dp[l - 1][min(i + 1, 2)][j - 1]) % mod;
			}
		}
	}
	int ans = 1;
	int cur = 0;
	int top = 2;
	int bot = -2;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'L') {
			--cur;
			top = min(top, cur + 2);
		}
		else {
			int tempCur = cur - 1;
			int tempTop = min(top, tempCur + 2);
			if(tempCur - bot >= 0)ans += dp[n - i - 1][min(tempTop - tempCur,2)][min(2,tempCur - bot)];
			ans %= mod;
			cur++;
			bot = max(bot, cur - 2);
		}
	}
	cout << ans;
}
