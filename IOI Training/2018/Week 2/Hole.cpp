/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, k,a[1000000];
long long sum,ans;
deque<pair<int,int>> d;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (!d.empty() && d.front().second <= i - k) d.pop_front();
		while (!d.empty() && d.back().first >= a[i]) d.pop_back();
		d.push_back({ a[i],i });
		sum += a[i] - (i-k >= 0 ? a[i-k] : 0);
		ans = max(ans, sum - d.front().first);
	}
	cout << ans;
}