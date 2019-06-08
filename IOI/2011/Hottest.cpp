/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int a[1000000];

int main() {
	ios::sync_with_stdio(false);
	int n,k;
	cin >> n>>k;
	int sum = 0;
	for (size_t i = 0; i < k; i++) {
		cin >> a[i];
		sum += a[i];
	}
	int ans = sum;
	for (size_t i = k; i < n; i++) {
		cin >> a[i];
		sum += a[i] - a[i - k];
		ans = max(ans, sum);
	}
	cout << ans;
}
