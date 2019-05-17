/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

double a[1000],w;

bool ok(int n, int l) {
	sort(a, a + n);
	if (a[0] > w / 2 || l - a[n - 1] > w / 2) {
		return false;
	}
	for (int i = 1; i < n; ++i) {
		if (a[i] - a[i - 1] > w) {
			return false;
		}
	}
	return true;
}

bool check(int n, int l) {
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
	}
	return ok(n, l);
}

int main() {
	ios::sync_with_stdio(false);
	while (true) {
		int nx, ny;
		cin >> nx >> ny >> w;
		if (nx == 0 && ny == 0 && w == 0) {
			break;
		}
		bool c = 1;
		c &= check(nx, 75);
		c &= check(ny, 100);
		cout << (c ? "YES" : "NO") << endl;
	}
}