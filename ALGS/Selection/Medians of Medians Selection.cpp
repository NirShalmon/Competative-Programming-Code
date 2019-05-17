/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int n,k, a[1000000];

int partition(int l, int r, int p) {
	int v = a[p];
	swap(a[p], a[r]);
	int i = l - 1;
	for (int j = l; j < r; ++j) {
		if (a[j] <= v) {
			swap(a[j], a[++i]);
		}
	}
	swap(a[r], a[++i]);
	return i;
}

int mot(int d, int b, int c) {
	if (a[b] < a[c] && a[b] < a[d]) { //a[b] is min
		if (a[c] < a[d]) return c;
		return d;
	} 
	if (a[c] < a[b] && a[c] < a[d]) { //a[c] is min
		if (a[b] < a[d]) return b;
		return d;
	}
	//a[d] is min
	if (a[b] < a[c]) return b;
	return c;
}

int pivot(int l,int r) {
	vector<int> v[2];
	for (size_t i = l; i < r; i++) {
		v[0].push_back(i);
	}
	int o = 1;
	while (v[o^1].size() > 1) {
		v[o].clear();
		for (int i = 0; i < v[o ^ 1].size(); i += 3) {
			if (i >= v[o^1].size() - 2) {
				v[o].push_back(v[o ^ 1][i]);
			} else v[o].push_back(mot(v[o ^ 1][i], v[o ^ 1][i + 1], v[o ^ 1][i + 2]));
		}
		o ^= 1;
	}
	return v[o^1][0];
}

int quickselect(int l, int r) {
	int p = pivot(l,r);
	int m = partition(l, r - 1, p);
	if (m == k) return a[m];
	if (m < k) return quickselect(m+1,r);
	else return quickselect(l, m);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n>>k;
	--k;
	for (int i = 0; i < n;)cin >> a[i++];
	cout<<quickselect(0, n);
}