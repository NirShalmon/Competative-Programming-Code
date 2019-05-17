/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXLG 10

int n;
int rmq[MAXLG][1000];
int pot[1000];

void build() {
	for (size_t s = 1, j = 1; s * 2 <= n; s *= 2, ++j) {
		for (size_t i = 0; i + 2 * s <= n; i++) {
			rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + s]);
		}
	}
}

int hibit(unsigned int n) {
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	return pot[n - (n >> 1)];
}

int query(int l, int r) {
	int s = r - l;
	int lp = pot[s];
	return min(rmq[lp][l], rmq[lp][r - (1 << lp)]);
}

int main() {
	ios::sync_with_stdio(false);
	int q;
	cin >> n>>q;
	int p = 0;
	for (size_t i = 1; i < 1000; i++) {
		if (1 << (p+1) < i) {
			++p;
		}
		pot[i] = p;
	}
	for (size_t i = 0; i < n; i++) {
		cin >> rmq[0][i];
	}
	build();
	for (size_t i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		cout << query(l, r)<<endl;
	}
}