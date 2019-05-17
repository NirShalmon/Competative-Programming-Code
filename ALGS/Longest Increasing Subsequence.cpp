/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int n, a[200001];
int p[200001];
int m[200001];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n;)cin >> a[i++];
	int l = 1;
	a[200000] = -1;
	p[0] = 200000;
	m[1] = 0;
	m[0] = 200000;
	for (size_t i = 1; i < n; i++) {
		int lo = 0;
		int hi = l;
		while (lo < hi) {
			int mid = (lo + hi + 1) / 2;
			if (a[i] > a[m[mid]]) lo = mid;
			else hi = mid - 1;
		}
		p[i] = m[lo];
		m[lo + 1] = i;
		if (lo == l)++l;
	}
	vector<int> rev;
	int q = m[l];
	while (q != 200000) {
		rev.push_back(a[q]);
		q = p[q];
	}
	for (int i = rev.size() - 1; i >= 0; --i) cout << rev[i] << ' ';
}