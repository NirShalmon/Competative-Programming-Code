/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

#define pos(x) ps[x+500000]

int n, k;
vector<int> a[110001];
pair<int, int> ps[1000001];

long long seg(int l, int r, int vi, vector<int> &v) {
	int x = l;
	int h = 0;
	int mn = 0;
	int mx = 0;
	pos(0) = { 0,l };
	pos(1) = { 0,0 };
	long long ans = 0;
	while (++x < r) {
		if (vi < v.size() && v[vi] == x) {
			++h;
			++vi;
			pos(h - 1).second = -2;
		} else {
			pos(h).second = x-1;
			--h;
		}
		if (h < mn) pos(h).first = 0;
		else if (h > mx) pos(h).first = x - l;
		else {
			if(pos(h).second != -2)pos(h).first += x - pos(h).second - 1;
		}
		mn = min(mn, h);
		mx = max(mx, h);
		ans += pos(h).first;
	}
	return ans;
}

long long calc(vector<int> &v) {
	if (v.size() == 0) return 0;
	vector<int> rcool = { v[0] };
	int mn = -v[0];
	int h = -v[0] + 1;
	int x = v[0];
	int i = 1;
	while (++x < n) {
		if (i < v.size() && v[i] == x) {
			++h;
			++i;
		} else --h;
		if (h > mn) rcool.push_back(x);
		if (h < mn) {
			if (i == v.size()) break;
			h -= v[i] - x - 2;
			x = v[i++];
			rcool.push_back(x);
			mn = h - 1;
		}
	}
	i = v.size() - 2;
	int mx = n - v[i + 1];
	vector<int> lcool = { v[i + 1] - 1 };
	x = v[i + 1];
	h = mx - 1;
	while (x > 0) {
		--x;
		if (i >= 0 && v[i] == x) {
			--h;
			--i;
		} else ++h;
		if (h < mx) lcool.push_back(x - 1);
		if (h > mx) {
			if (i == -1) break;
			h += x - v[i] - 2;
			mx = h + 1;
			x = v[i--];
			lcool.push_back(x - 1);
		}
	}
	reverse(lcool.begin(), lcool.end());
	int l = lcool[0];
	int r = l;
	int li = 1;
	int ri = 0;
	int vi = 0;
	long long ans = 0;
	while (r < n) {
		bool ok = false;
		++r;
		if (li < lcool.size() && lcool[li] == r) {
			ok = true;
			++li;
		}
		if (ri < rcool.size() && rcool[ri] == r) {
			ok = true;
			++ri;
		}
		if (!ok) {
			while (v[vi] <= l)++vi;
			ans += seg(l, r, vi, v);
			if (li == lcool.size()) break;
			l = lcool[li++];
			r = l;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	/*n = 15;
	vector<int> v = { 0,1,6,7,9 };
	calc(v);*/
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		a[c].push_back(i);
	}
	long long ans = 0;
	for (int i = 0; i <= k; ++i) ans += calc(a[i]);
	cout << ans;
}