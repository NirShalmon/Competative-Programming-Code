/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int a[2000000];
int n, k;

int bSearch(int v) {
	int lo = 0, hi = n - 1;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (a[mid] > v) hi = mid - 1;
		else lo = mid;
	}
	return a[lo];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (size_t i = 0; i < k; i++) {
		int v;
		cin >> v;
		cout << bSearch(v)<<'\n';
	}
}