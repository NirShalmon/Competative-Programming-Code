/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

long long a[62][62];
int m[62];

int dig(long long a) {
	int sum = 0;
	for (long long i = 1; i < 1ll << 62; i <<= 1) {
		sum += (a & i) != 0;
	}
	return sum;
}

long long f(long long hi, int j) {
	long long ans = 0;
	int d = dig(hi);
	int sofar = hi & 1;
	if (hi & 1) {
		hi ^= 1;
		if (d - 1 == j) {
			++ans;
		}
	}
	for (size_t i = 1; hi; ++i) {
		if (hi & (1ll << i)) {
			hi ^= 1ll << i;
			int t = j - (d - ++sofar);
			if (t >= 0) {
				ans += a[i][t];
			}
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	a[1][0] = 1;
	a[1][1] = 1;
	for (size_t i = 2; i < 62; i++) {
		for (size_t j = 0; j <= i; j++) {
			a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
		}
	}
	m[0] = -1;
	m[1] = 0;
	for (int i = 2; i < 62; ++i) {
		m[i] = m[dig(i)] + 1;
	}
	long long lo, hi, x;
	cin >> lo >> hi >> x;
	while (hi || lo || x) {
		long long ans = 0;
		for (long long i = lo; i <= hi && i < 62; ++i) {
			if (m[i] == x) {
				++ans;
			}
		}
		for (int i = 0; i < 62 && hi*2 >= 1ll<<i; ++i) {
			if (m[i] + 1 == x) {
				if (hi >= 62) {
					ans += f(hi + 1, i) - f(62, i);
				}
				if (lo >= 62) {
					ans -= f(lo, i) - f(62, i);
				}
			}
		}
		cout << ans << endl;
		cin >> lo >> hi >> x;
	}
}
