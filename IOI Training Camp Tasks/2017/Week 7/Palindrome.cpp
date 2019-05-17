/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<cstdio>
#include<algorithm>

using namespace std;

int dp[10000][2];
char s[10005];

int main() {
	int n;
	scanf("%d %s", &n, s);
	for (size_t sz = 1; sz < n; sz++) {
		int q = sz & 1;
		int w = q ^ 1;
		int j = sz - 1;
		for (size_t i = 0; i < n - sz; i++) {
			if (s[i] == s[++j]) dp[i][q] = dp[i + 1][q];
			else dp[i][q] = 1 + min(dp[i + 1][w], dp[i][w]);
		}
	}
	printf("%d", dp[0][(n - 1) & 1]);
}