/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include <bits/stdc++.h>
using namespace std;

int n,m;
pair<int,int> p[100000];
map<int,pair<int,int>> c;

int main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i = 0; i < n; ++i){
		int a,b;
		cin>>a>>b;
		if(a < b) {
			c[a].first++;
			c[b].first--;
		}else{
			c[b].second++;
			c[a].second--;
		}
	}
	long long ans = m;
	int lc = 0,rc = 0;
	int prx = 0;
	long long mult = 0;
	for(auto &x : c){
		ans += (mult * (x.first - prx))*2;
		lc += x.second.first;
		rc += x.second.second;
		mult = max(lc-1,rc);
		prx = x.first;
	}
//	ans += mult * ((*c.rbegin()).first - prx);
	cout<<ans;
}
