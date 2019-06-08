/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
bool d[1000000];
bool f[1000000];

int calc() {
	int mx1 = 0,mx2 = 0;
	int cur1 = 0, cur2 = 0;
	int l1 = 0,l2 = 0;
	for (size_t i = 0; i < n; i++) {
		if (d[i]) {
			mx1 = max(mx1, cur1);
			cur1 = 0;
			if (cur1 == i) {
				l1 = cur1;
			}
		} else {
			++cur1;
		}
		if (f[i]) {
			mx2 = max(mx2, cur2);
			cur2 = 0;
			if (cur2 == i) {
				l2 = cur2;
			}
		} else {
			++cur2;
		}
	}
	return max(max(mx1, cur1 + l1), max(mx2, cur2 + l2));
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	int s = 0;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		int t = i - --p + n;
		d[t % n] = true;
		f[(2 * n - 1 - i - p) % n] = true;
	}
	int cc = calc();
	if (--n & 1) {
		if (cc == 0) {
			cout << n / 2 + 1;
		} else {
			cout << n / 2 - (cc - 1) / 2;
		}
	} else {
		cout << n / 2 - cc / 2;
	}
}
