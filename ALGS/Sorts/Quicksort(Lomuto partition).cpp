/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>

using namespace std;

int n, a[100000];

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

void insertionSort(int l, int r) {
	for (int i = l + 1; i < r; ++i) {
		int j = i;
		while (--j >= 0 && a[j] > a[j + 1]) {
			swap(a[j], a[j + 1]);
		}
	}
}

void quicksort(int l, int r) {
	if (l + 5 >= r) {
		insertionSort(l, r);
		return;
	}
	int p = l + rand() % (r - l);
	int m = partition(l, r - 1, p);
	if (m > l + 1) quicksort(l, m);
	if (r > m + 2) quicksort(m + 1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n;)cin >> a[i++];
	quicksort(0, n);
	for (int i = 0; i < n;)cout << a[i++] << ' ';
}