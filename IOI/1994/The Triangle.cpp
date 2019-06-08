/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

int a[2][100];

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n >> a[1][0];
	for (int i = 2; i <= n - 1; ++i) {
		cin >> a[i & 1][0];
		a[i & 1][0] += a[(i + 1) & 1][0];
		for (int j = 1; j < i - 1; ++j) {
			cin >> a[i & 1][j];
			a[i & 1][j] += max(a[(i + 1) & 1][j - 1], a[(i + 1) & 1][j]);
		}
		cin >> a[i & 1][i - 1];
		a[i & 1][i - 1] += a[(i + 1) & 1][i - 2];
	}
	//code doubled to calc max only on last line
	cin >> a[n & 1][0];
	a[n & 1][0] += a[(n + 1) & 1][0];
	int ans = a[n&1][0];
	for (int j = 1; j < n - 1; ++j) {
		cin >> a[n & 1][j];
		a[n & 1][j] += max(a[(n + 1) & 1][j - 1], a[(n + 1) & 1][j]);
		ans = max(ans, a[n & 1][j]);
	}
	cin >> a[n & 1][n - 1];
	a[n & 1][n - 1] += a[(n + 1) & 1][n - 2];
	ans = max(ans, a[n & 1][n-1]);
	cout << ans;
}
