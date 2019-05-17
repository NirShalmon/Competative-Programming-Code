/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

bool offset;
int n;

void print(int r1, int c1, int r2, int c2) {
	cout << r1 + offset << ' ' << c1 + offset << ' ' << r2 + offset << ' '<<c2 + offset << endl;
}

void up(int r, int c) {
	print(r, c, r + 2, c);
}

void down(int r, int c) {
	print(r, c, r - 2, c);
}

void left(int r, int c) {
	print(r, c, r, c+2);
}

void right(int r, int c) {
	print(r, c, r , c-2);
}

void finish() {
	right(1, 2);
	right(2, 2);
	down(2, 0);
}

void peel3() {
	for (size_t i = 1; i <= n-3; i++) {
		right(n-2, i+1);
		down(n, i);
		left(n-2, i-1);
	}
	for (int i = n; i > 3; i--) {
		up(i - 1, n - 2);
		right(i, n);
		down(i + 1, n - 2);
	}
	for (int i = n; i > n - 3; --i) {
		left(1, i - 1);
		down(3, i);
		right(1, i + 1);
	}
}

void peel2() {
	for (size_t i = 1; i < n; i+= 3) {
		up(n-1, i);
		right(n, i + 2);
		down(n + 1, i);
	}
	for (int i = n-2; i >= 0; i-=3) {
		left(i, n - 1);
		down(i + 2, n);
		right(i, n + 1);
	}
	for (int i = n; i >= 3; i -= 3) {
		down(2, i - 2);
		right(1, i);
		up(0, i - 2);
	}
	for (size_t i = 1; i < n; i += 3) {
		right(i + 2, 2);
		up(i, 1);
		left(i + 2, 0);
	}
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		offset = false;
		cin >> n;
		if (n % 3 == 0) {
			cout << -1 << endl;
			continue;
		}
		cout << n*n - 1 << endl;
		if (n % 3 == 1) {
			peel2();
			offset = true;
			n -= 2;
		}
		while (n > 2) {
			peel3();
			n -= 3;
		}
		finish();
	}
}