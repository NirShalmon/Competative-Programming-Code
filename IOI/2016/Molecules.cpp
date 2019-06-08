/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

long long n, l, u;
pair<long long, int> w[200000];

void out(int i, int j) {
	cout << i + 1 + (n-1-j)<<endl;
	for (int k = 0; k <= i; k++) {
		cout << w[k].second << ' ';
	}
	for (int k = n - 1; k > j; --k) cout << w[k].second << ' ';
	exit(0);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >>l >> u;
	for (size_t i = 0; i < n; i++) {
		cin >> w[i].first;
		w[i].second = i;
	}
	sort(w, w + n);
	long long sum = 0;
	int i = 0;
	if (w[0].first > u) {
		cout << 0;
		return 0;
	}
	sum = w[0].first;
	while (i < n - 1 && sum + w[i + 1].first <= u) {
		sum += w[i + 1].first;
		++i;
	}
	int j = n - 1;
	if (sum >= l && sum <= u) out(i, j);
	while (i >= 0) {
		sum -= w[i].first;
		sum += w[j].first;
		--j;
		--i;
		if (sum >= l && sum <= u) out(i, j);
	}
	cout << 0;
}
