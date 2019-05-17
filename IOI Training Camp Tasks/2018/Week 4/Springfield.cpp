/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool vis[30000];
vector<int> edj[30000];
int out[30000];
bool on[30000];
int p[30000];

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		vector<pair<int,int>> ans;
		for(int i = 0; i < 20000; ++i){
			vis[i] = false;
			edj[i].clear();
			out[i] = 0;
			on[i] = false;
			p[i] = -1;
		}
		for(int i = 0; i < m; ++i){
			int u,v;
			cin>>u>>v;
			edj[--u].push_back(--v);
			edj[v].push_back(u);
		}
		for(int i = 0; i < n; ++i){
			if(!vis[i]){
				queue<int> q;
				q.push(i);
				vis[i] = true;
				int sz = 0;
				vector<int> comp;
				while(!q.empty()){
					int u = q.front();
					q.pop();
					++sz;
					comp.push_back(u);
					for(int j = 0; j < edj[u].size(); ++j){
						int v = edj[u][j];
						if(!vis[v]){
							vis[v] = true;
							p[v] = u;
							q.push(v);
							++out[u];
						}
					}
					if(q.size() > n) exit(99);
				}
				if(sz%2 == 1){
					cout<<-1<<endl;
					goto end;
				}
				vector<int> leaf;
				for(int j = 0; j < comp.size(); ++j){
					if(out[comp[j]]==0){
						leaf.push_back(comp[j]);
					}
				}
				while(!leaf.empty()){
					int u = leaf.back();
					leaf.pop_back();
					if(p[u] != -1){
						if(!on[u]){
							ans.push_back(make_pair(u,p[u]));
							on[p[u]] = !on[p[u]];
						}
						if(--out[p[u]]==0) leaf.push_back(p[u]);
					}
				}
			}
		}
		cout<<ans.size()<<endl;
		for(int i = 0; i < ans.size(); ++i){
			cout<<ans[i].first+1<<endl<<ans[i].second+1<<endl;
		}
end:
		t=t;
	}
}