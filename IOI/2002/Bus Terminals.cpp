/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
pair<int, int> pos[500];
pair<int,int> d[500][500];
pair<int, int> cmb[500];

inline int dis(int i, int j) {
	return abs(pos[i].first - pos[j].first) + abs(pos[i].second - pos[j].second);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (size_t i = 0; i < n; i++) {
		cin >> pos[i].first >> pos[i].second;
	}
	if (n == 2) {
		cout << dis(0, 1);
		return 0;
	}
	for (size_t i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i][j] = {dis(i,j) ,j };
		}
		sort(d[i], d[i] + n);
	}
	int mx = 999999999;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = i+1; j < n; j++) {
			//int ci = 0,di=0,cj=0,dj=0;
			int ij = dis(i, j);
			for (size_t k = 0; k < n; k++) {
				cmb[k] = { d[i][k].first,dis(j,d[i][k].second) };
			}
			mx = min(mx, cmb[n - 2].first + cmb[n - 1].first);
			mx = min(mx, max(cmb[n - 3].first + cmb[n - 2].first, cmb[n - 2].first + ij+ cmb[n - 1].second));
			mx = min(mx, max(cmb[n - 3].first + cmb[n - 1].first, cmb[n - 1].first + ij+ cmb[n - 2].second));
			int mn[3] = {n-1 ,n-2,n-3};
			if (cmb[mn[0]].second < cmb[mn[1]].second) {
				swap(mn[0], mn[1]);
			}
			if (cmb[mn[1]].second < cmb[mn[2]].second) {
				swap(mn[1], mn[2]);
			}
			if (cmb[mn[0]].second < cmb[mn[1]].second) {
				swap(mn[0], mn[1]);
			}
			for (int k = n-4; k >= 0; --k) {
				int a2 = cmb[k].first;
				//choosing a with k+1
				int a1 = cmb[k + 1].first;
				int b1 = cmb[k + 1 == mn[0] ? mn[1] : mn[0]].second;
				int b2 = cmb[k + 1 == mn[0] || k+1 == mn[1] ? mn[2] : mn[1]].second;
				mx = min(mx,max(a1 + a2, max(b1 + b2, a1 + ij + b1)));
				//choosing a with mn[0]
				a1 = cmb[mn[0]].first;
				b1 = cmb[mn[1]].second;
				b2 = cmb[mn[2]].second;
				mx = min(mx,max(a1 + a2, max(b1 + b2, a1 + ij + b1)));
				//choosing a with mn[1]
				a1 = cmb[mn[1]].first;
				b1 = cmb[mn[0]].second;
				b2 = cmb[mn[2]].second;
				mx = min(mx,max(a1 + a2, max(b1 + b2, a1 + ij + b1)));
				//update mn
				if (k> 0 && cmb[k].second > cmb[mn[2]].second) {
					mn[2] = k;
					if (cmb[mn[2]].second > cmb[mn[1]].second) {
						swap(mn[2], mn[1]);
						if (cmb[mn[1]].second > cmb[mn[0]].second) {
							swap(mn[0], mn[1]);
						}
					}
				}
			}
			mx = min(mx, max(cmb[0].first + ij + cmb[mn[0]].second, cmb[mn[0]].second + cmb[mn[1]].second));
			//Dirty code reuse to update mn for k=0(no a connections)
			int k = 0;
			if (cmb[k].second > cmb[mn[2]].second) {
				mn[2] = k;
				if (cmb[mn[2]].second > cmb[mn[1]].second) {
					swap(mn[2], mn[1]);
					if (cmb[mn[1]].second > cmb[mn[0]].second) {
						swap(mn[0], mn[1]);
					}
				}
			}
			mx = min(mx, cmb[mn[0]].second + cmb[mn[1]].second);
		}
	}
	cout << mx;
}

//REMEMBER ALL AT A/B AND ONE AT A/B
