/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

long long a[700000];

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	long long sum = 0;
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	long long q = sum / n;
	a[0] -= q;
	for (size_t i = 1; i < n; i++) {
		a[i] += a[i - 1] - q;
	}
	sort(a, a + n);
	int c = 1, m = 1;
	for (size_t i = 1; i < n; i++) {
		if (a[i] == a[i - 1]) ++c;
		else {
			m = max(m, c);
			c = 1;
		}
	}
	m = max(m, c);
	cout << n - m;
}