/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, a[100000];

//[l,r]
int partition(int l, int r, int val) {
	while (l <= r) {
		while (a[l] < val && l <= r)++l;
		while (a[r] > val && r >= l)--r;
		if (l <= r)swap(a[l++], a[r--]);
	}
	return l;
}

void quicksort(int l, int r) {
	if (l + 1 >= r) return;
	int p = rand() % (r - l) + l;
	swap(a[r - 1], a[p]);
	int t = partition(l, r - 2, a[r - 1]);
	swap(a[r - 1], a[t]);
	quicksort(l, t);
	quicksort(t + 1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	quicksort(0, n);
	for (size_t i = 0; i < n; i++) {
		cout << a[i] << ' ';
	}
}