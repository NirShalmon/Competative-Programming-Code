/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
int a[2][2001];
int b[2][2001];
short x[20001], y[20001];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	x[0] = 1000;
	y[0] = 1000;
	for (int i = 1; i <= n; ++i) {
		cin >> x[i] >> y[i];
		x[i] += 1000;
		y[i] += 1000;
	}
	for (short  i = 0; i < 2001; i++) {
		a[0][i] = abs(1000-i);
		b[0][i] = abs(1000 - i);
	}
	for (size_t p = 1; p <= n; p++) {
		int q = p % 2;
		int w = (p + 1) % 2;
		for (short i = 0; i <= 2000; i++) {
			a[q][i] = min(b[w][x[p]] + abs(y[p - 1] - i), a[w][i] + abs(x[p - 1] - x[p]));
			b[q][i] = min(a[w][y[p]] + abs(x[p - 1] - i), b[w][i] + abs(y[p - 1] - y[p]));
		}
	}
	int ans = 999999999;
	for (int i = 0; i <= 2000; ++i) {
		ans = min(ans, min(a[n % 2][i], b[n % 2][i]));
	}
	cout << ans;
}
