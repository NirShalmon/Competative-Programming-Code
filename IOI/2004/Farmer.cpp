/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int w[150001];
int c[151];

int main() {
	ios::sync_with_stdio(false);
	int q, m, k;
	cin >> q >> m>> k;
	int tot = 0;
	for (size_t i = 1; i <= q; i++) {
		w[i] = -1;
	}
	int ans = 0;
	for (size_t i = 0; i < m; i++) {
		int t;
		cin >> t;
		c[t]++;
		tot += t;
		for (int j = q; j >= t; j--) {
			if(w[j - t] != -1 && w[j] == -1){
				w[j] = j - t;
			}
		}
	}
	int b = 0;
	for (size_t i = 0; i <= q; i++) {
		if (w[i] != -1) {
			b = i;
		}
	}
	int cur = b;
	while (cur > 0) {
		int tcur = w[cur];
		c[cur - tcur]--;
		cur = tcur;
	}
	for (size_t i = 0; i < k; i++) {
		int t;
		cin >> t;
		c[t]++;
	}
	cur = 150;
	q -= b;
	ans = b;
	while (cur >= 2 && c[cur] == 0) --cur;
	while (cur >= 2 && q > 0) {
		ans += min(cur, q) - 1;
		c[cur]--;
		q -= cur;
		while (cur >= 2 && c[cur] == 0) --cur;
	}
	cout << ans;
}
