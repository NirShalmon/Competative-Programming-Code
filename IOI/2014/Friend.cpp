/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int n, p[100000],q[100000], prot[100000], h[100000];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n;)cin >> p[i++];
	for (int i = 1; i < n; i++)cin >> h[i] >> prot[i];
	for (int i = n - 1; i > 0; --i) {
		if (prot[i] == 0) {
			int t = p[h[i]] + q[i];
			q[h[i]] = max(q[i] + q[h[i]],q[h[i]]+p[i]);
			p[h[i]] = t;
		} else if(prot[i] == 1){
			int t = max(p[h[i]] + q[i],max(q[h[i]]+p[i],p[i]+p[h[i]]));
			q[h[i]] = q[h[i]] + q[i];
			p[h[i]] = t;
		} else {
			int t = max(p[h[i]] + q[i], q[h[i]] + p[i]);
			q[h[i]] = q[h[i]] + q[i];
			p[h[i]] = t;
		}
	}
	cout << max(p[0], q[0]);
}
