/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>

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

int quickselect(int l, int r) {
	int p = (l + r) / 2;
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