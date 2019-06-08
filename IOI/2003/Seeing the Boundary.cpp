/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n,r,x,y;

int l[2000001];

pair<double,double> getp(int x1, int y1, int x2, int y2) {
	x2 -= x1;
	y2 -= y1;
	double t = 1e10, k = 1e10;
	if (x2 != 0) {
		t = ((x2 > 0 ? (double)n : 0) - x1) / x2;
	}
	if (y2 != 0) {
		k = ((y2 > 0 ? (double)n : 0) - y1) / y2;
	}
	pair<double,double> f;
	if (k <= t) {
		f = y2 > 0 ? make_pair(x1 + x2*k,n) : make_pair( x1 + x2*k,0);
	} else {
		f= x2 > 0 ? make_pair(n,y1 + y2*t) : make_pair(0,y1 + y2*t);
	}
	return f;
}

double getv(double x, double y) {
	if (x == 0 && y == 0) return 0;
	if (y == 0) return x;
	if (y == n) return 3 * n - x;
	if (x == n) return n + y;
	return 4 * n - y;
}

int up(double d) {
	return (int)(ceil(d) + 0.1);
}

int down(double d) {
	return (int)d;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n>>r>>x>>y;
	for (size_t i = 0; i < r; i++) {
		int p;
		cin >> p;
		double lv;
		for (size_t j = 0; j < p; j++) {
			int a, b;
			cin >> a >> b;
			pair<double, double> np = getp(x, y, a, b);
			double nv = getv(np.first,np.second);
			auto inters = getp(np.first, np.second, x, y);
			double iv = getv(inters.first,inters.second);
			if (j != 0) {
				double q = min(lv, nv);
				double w = max(lv, nv);
				if (!(q <= iv && iv <= w)) {
					++l[up(q)];
					--l[down(w) + 1];
				} else {
					++l[0];
					--l[down(q) + 1];
					++l[up(w)];
					--l[4 * n];
				}
			}
			lv = nv;
		}
	}
	int ans = 0;
	int q = 0;
	for (size_t i = 0; i < 4*n; i++) {
		q += l[i];
		if (q == 0)++ans;
		if (q < 0) {
			cout << "problem";
		}
	}
	cout << ans;
}

//x + ta=100/0 -> t=(100-x)/a
//y + kb=100/0 -> y + (100-x)b/a
//min(
