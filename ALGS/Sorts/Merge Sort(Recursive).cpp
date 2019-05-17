/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, a[100000];

void merge(int l, int c, int r) {
	static int buffer[100000];
	int i = 0;
	int lp = l, rp = c;
	while (lp < c && rp < r) {
		if (a[lp] < a[rp]) buffer[i++] = a[lp++];
		else buffer[i++] = a[rp++];
	}
	while (lp < c) buffer[i++] = a[lp++];
	while (rp < r) buffer[i++] = a[rp++];
	while (i > 0) a[--rp] = buffer[--i];
}

void mergeSortRecursive(int l, int r) {
	if (l + 1 >= r) return;
	mergeSortRecursive(l, (l + r) / 2);
	mergeSortRecursive((l+r)/2,r);
	merge(l, (l + r) / 2, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i)cin >> a[i];
	mergeSortRecursive(0,n);
	for (size_t i = 0; i < n; i++) cout << a[i]<<' ';
}