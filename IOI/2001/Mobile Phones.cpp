/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>

using namespace std;

int arr[1025][1025];
int s;

int sum(int px, int py) {
	int ret = 0;
	for (int x = px; x; x -= x & (-x)) {
		for (int y = py; y; y -= y & (-y)) {
			ret += arr[x][y];
		}
	}
	return ret;
}

void update(int px, int py, short d) {
	for (int x = px; x <= s; x += x & (-x)) {
		for (int y = py; y <= s; y += y & (-y)) {
			arr[x][y] += d;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t != 3) {
		if (t == 0) {
			cin >> s;
		} else if (t == 1) {
			short x, y, a;
			cin >> x >> y >> a;
			update(++x, ++y, a);
		} else if (t == 2) {
			int l, b, r, t;
			cin >> l >> b >> r >> t;
			++r, ++l, ++b, ++t;
			int ans = sum(r, t);
			if (l > 1) {
				ans -= sum(l - 1, t);
			}
			if (b > 1) {
				ans -= sum(r, b - 1);
			}
			if (b > 1 && l > 1) {
				ans += sum(l - 1, b - 1);
			}
			cout << ans << endl;
		}
		cin >> t;
	}
}
