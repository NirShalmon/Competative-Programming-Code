/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, a[100000];

void insertionSort() {
	for (size_t i = 1; i < n; i++) {
		int v = a[i];
		int j = i;
		while (j > 0 && a[j - 1] > v) {
			a[j] = a[j - 1];
			--j;
		}
		a[j] = v;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i)cin >> a[i];
	insertionSort();
	for (size_t i = 0; i < n; i++) cout << a[i]<<' ';
}