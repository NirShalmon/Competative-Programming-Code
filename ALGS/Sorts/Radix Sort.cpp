/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, a[100000];

void countingSort(int digit) {
	vector<vector<int>> count;
	count.resize(10);
	for (int i = 0; i < n; ++i) count[(a[i]/digit)%10].push_back(a[i]);
	int k = 0;
	for (int i = 0; i < count.size(); ++i) {
		for (int v : count[i]) a[k++] = v;
	}
}

void radixSort() {
	for (size_t d = 1; d <= 1000000; d*=10) {
		countingSort(d);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	radixSort();
	for (size_t i = 0; i < n; i++) {
		cout << a[i] << ' ';
	}
} 