/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

string a, b;
int dp[2001][2001];

void printLCS(int i,int j) {
	if (i * j == 0) return;
	if (a[i-1] == b[j-1]) {
		printLCS(i - 1, j - 1);
		cout << a[i-1];
	} else if (dp[i - 1][j] >= dp[i][j - 1]) printLCS(i - 1, j);
	else printLCS(i, j - 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> a >> b;
	for (size_t i = 1; i <= a.size(); i++) {
		for (size_t j = 1; j <= b.size(); j++) {
			if (a[i-1] == b[j-1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	printLCS(a.size(), b.size());
}