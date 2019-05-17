/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

int n, a[2][100000];

void merge(char o,int l, int m, int r) {
	int i = l,j = m;
	int k = l;
	while (i < m && j < r) {
		a[o^1][k++] = a[o][i] <= a[o][j] ? a[o][i++] : a[o][j++];
	}
	while (i < m) a[o^1][k++] = a[o][i++];
	while (j < r) a[o^1][k++] = a[o][j++];
}

void mergeSort() {
	char o = 0;
	int l;
	for (int s = 1; s < n; s *= 2) {
		for (l = 0; l+s < n; l += 2 * s) {
			merge(o,l, l + s, min(l + 2 * s, n));
		}
		while(l < n) {
			a[o ^ 1][l] = a[o][l];
			l++;
		}
		o ^= 1;
	}
	if (o == 1) swap(a[1], a[0]);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n;)cin >> a[0][i++];
	mergeSort();
	for (int i = 0; i < n;)cout << a[0][i++]<<' ';
}