/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int deg[700000];
bool assigned[700000];
vector<int> edj[700000];
int ans[700000];

int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i = 0; i < m; ++i){
		int u,v;
		cin>>u>>v;
		--u;--v;
		deg[u]++; deg[v]++;
		edj[u].push_back(v);
		edj[v].push_back(u);
	}
	int s,nx = -1;
	int dir = 1;
	int v = 1;
	for(int i = 0; i < n; ++i){
		if(deg[i] > 1){
			int cnt = 0;
			for(int j = 0; j < edj[i].size(); ++j){
				if(deg[edj[i][j]] > 1){
					++cnt;
				}
			}
			if(cnt >= 2) continue;
			s = i;
			break;
		}
	}
	//cout<<s;
	ans[s] = 1;
	assigned[s] = true;
	while(v < n){
		for(int i = 0; i < edj[s].size(); ++i){
			int o = edj[s][i];
			if(!assigned[o]){
				if(edj[edj[s][i]].size() == 1){
					ans[o] = ans[s] + (n - v) * dir;
					++v;
				}else{
					nx = o;
				}
				assigned[o] = true;
			}
		}
		if(nx != 1){
			ans[nx] = ans[s] + (n - v) * dir;
			++v;
		}
		dir *= -1;
		s = nx;
		nx = -1;
	}
	for(int i = 0; i < n; ++i) cout<<ans[i]<<'\n';
//	cin>>n;
}