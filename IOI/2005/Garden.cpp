/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int s[255][255];
int a[255], b[255], c[255], d[255];

int r(int x1, int y1, int x2, int y2) {
	return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}

int main() {
	int l, w, n, k;
	cin >> l >> w >> n >> k;
	for (size_t i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		s[x][y]++;
	}
	for (int y = 1; y <= w; ++y) {
		for (int x = 1; x <= l; ++x) {
			s[x][y] += s[x - 1][y] + s[x][y - 1] - s[x - 1][y - 1];
		}
	}
	for (size_t i = 0; i < 255; i++) {
		a[i] = 999999999;
		b[i] = 999999999;
		c[i] = 999999999;
		d[i] = 999999999;
	}
	for (int y1 = 1; y1 <= w; ++y1) {
		for (int y2 = y1; y2 <= w; ++y2) {
			int x1 = 1, x2 = 1;
			while (x2 <= l) {
				while (r(x1, y1, x2, y2) < k && x2 <= l) {
					++x2;
				}
				while (r(x1, y1, x2, y2) > k && x1 < x2) {
					++x1;
				}
				if (r(x1, y1, x2, y2) == k) {
					int p = 2 * (x2 - x1 + y2 - y1 + 2);
					a[y2 + 1] = min(a[y2 + 1], p);
					b[y1] = min(b[y1], p);
					c[x2 + 1] = min(c[x2 + 1], p);
					d[x1] = min(d[x1], p);
					if (x1 == x2) {
						++x2;
					}
					int t = r(++x1, y1, x2, y2), q = r(x1 + 1, y1, x2, y2);
					while (t == q && x1 < x2) {
						t = r(++x1, y1, x2, y2);
						q = r(x1 + 1, y1, x2, y2);
					}
				}
				if (x1 == x2 && r(x1, y1, x2, y2) > k) {
					++x1; ++x2;
				}
			}
		}
	}
	int ans = 999999999;
	for (int i = 1; i < 255; ++i) {
		a[i] = min(a[i], a[i - 1]);
		c[i] = min(c[i], c[i - 1]);
	}
	for (int i = 253; i >= 0; --i) {
		b[i] = min(b[i], b[i + 1]);
		d[i] = min(d[i], d[i + 1]);
	}
	for (int i = 1; i < 255; ++i) {
		ans = min(ans, a[i] + b[i]);
		ans = min(ans, c[i] + d[i]);
	}
	if (ans >= 99999999) {
		cout << "NO";
	} else {
		cout << ans;
	}
}
