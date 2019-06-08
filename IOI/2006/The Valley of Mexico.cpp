/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

typedef struct info {
	bool side;
	int l, r;
} info;

int c, n;
bool edj[1000][1000];
info dp[2][1000][1000];

void out(bool side, int l, int r) {
	while (l != r) {
		if (side == 0) cout << l+1 << '\n';
		else cout << r +1<< '\n';
		auto tmp = dp[side][l][r];
		side = tmp.side;
		l = tmp.l;
		r = tmp.r;
	}
	cout << l+1;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> c >> n;
	for (int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		edj[--a][--b] = true;
		edj[b][a] = true;
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < c; ++j) {
			for (int k = 0; k < c; ++k) dp[i][j][k] = {0, -1,-1 };
		}
	}
	for (int i = 0; i < c; ++i) {
		if (edj[i][(i + 1) % c]) {
			dp[0][i][(i + 1) % c] = {0, (i+1)%c,(i+1)%c };
			dp[1][i][(i + 1) % c] = {1, i,i };
		}
	}
	for (int d = 2; d < c; ++d) {
		for (int l = 0; l < c; ++l) {
			int r = (l + d) % c;
			if (edj[l][(l + 1) % c] && dp[0][(l + 1) % c][r].l != -1) {
				dp[0][l][r] = { 0,(l + 1) % c,r };
			}
			else if (edj[l][r] && dp[1][(l + 1) % c][r].l != -1) {
				dp[0][l][r] = { 1,(l + 1) % c,r };
			}
			if (edj[(r + c - 1) % c][r] && dp[1][l][(r + c - 1) % c].l != -1) {
				dp[1][l][r] = { 1,l,(r + c - 1) % c };
			}
			else if (edj[l][r] && dp[0][l][(r + c - 1) % c].l != -1) {
				dp[1][l][r] = { 0,l,(r + c - 1) % c };
			}
			if (d == c - 1 && dp[0][l][r].l != -1) {
				out(0, l, r);
				exit(0);
			}
			else if (d == c - 1 && dp[1][l][r].l != -1) {
				out(1, l, r);
				exit(0);
			}
		}
	}
	cout << -1;
}
