/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

struct node {
	long long d = 0, sd = 0, h = 0;
	long long l = -1, r = -1;
};

long long n,d;
long long nu;
node t[5000000];
long long ti = 0;

pair<int,int> lh(int l, int r) {
	return{ l ,(l + r) / 2 };
}

pair<int, int> rh(int l, int r) {
	return{ (l + r+1) / 2 ,r};
}

bool in(pair<int, int> a, pair<int, int> b) {
	return a.first >= b.first && a.second <= b.second;
}

bool inter(pair<int, int> a, pair<int, int> b) {
	return (a.first <= b.second && a.second >= b.first);
}

void f(int l, int r,int p, pair<int, int> range) {
	if (in(range, { l,r })) {
		t[p].d = d;
		t[p].h = max(0ll, d*(1+range.second - range.first));
		t[p].l = -1;
		t[p].r = -1;
		t[p].sd = d*(1+range.second - range.first);
	} else {
		if (t[p].l == -1) {
			t[p].l = ti;
			t[ti].h = max(0ll, t[p].d*(1+range.second - range.first) / 2);
			t[ti].sd = t[p].d*(1+range.second - range.first) / 2;
			t[ti++].d = t[p].d;
			t[p].r = ti;
			t[ti].h = max(0ll, t[p].d*(1+range.second - range.first) / 2);
			t[ti].sd = t[p].d*(1+range.second - range.first) / 2;
			t[ti++].d = t[p].d;
		}
		bool ok = false;
		if (inter({ l,r }, lh(range.first,range.second))) {
			f(l, r, t[p].l, lh(range.first, range.second));
			ok = true;
		}
		if (inter({ l,r }, rh(range.first, range.second))) {
			f(l, r, t[p].r, rh(range.first, range.second));
			ok = true;
		}
		if (!ok) 
			cout << "err";
		t[p].h = max(t[t[p].l].h, t[t[p].l].sd + t[t[p].r].h);
		t[p].sd = t[t[p].l].sd + t[t[p].r].sd;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	nu = 1;
	while (nu < n) nu *= 2;
	ti++;
	while (true) {
		char c;
		cin >> c;
		if (c == 'E') return 0;
		pair<int, int> range = { 0,nu-1 };
		if (c == 'I') {
			int l, r;
			cin >> l >> r >> d;
			--l; --r;
			f(l, r, 0, range);
		} else if (c == 'Q') {
			long long h;
			cin >> h;
			long long nd = 0;
			long long sm = 0;
			if (t[nd].h <= h) {
				cout << n << endl; continue;
			}
			while (t[nd].h + sm > h) {
				if (t[nd].l != -1 && t[t[nd].l].h + sm > h) {
					nd = t[nd].l;
					range = lh(range.first, range.second);
				} else if (t[nd].r != -1) {
					range = rh(range.first, range.second);
					sm += t[t[nd].l].sd;
					nd = t[nd].r;
				} else break;
			}
			cout << (t[nd].d == 0 ? range.second : range.first + (h - sm) / t[nd].d) << endl;
		}
	}
}
