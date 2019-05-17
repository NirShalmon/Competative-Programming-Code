/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

vector<int> edj[200000];
long long ans = 0;
bool vis[200000];
int d[200000];

int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i = 0; i < m; ++i){
		int u,v;
		cin>>u>>v;
		edj[--u].push_back(--v);
		edj[v].push_back(u);
	}
	for(int i = 0; i < n; ++i){
		if(!vis[i]){
			int c[2] = {1,0};
			vis[i]= true;
			queue<int> q;
			q.push(i);
			while(!q.empty()){
				int u = q.front();
				q.pop();
				for(int j = 0; j < edj[u].size(); ++j){
					int v = edj[u][j];
					if(vis[v]){
						if(d[v] == d[u]){
							cout<<"NO";
							return 0;
						}
					}else{
						d[v] = d[u]+1;
						c[d[v]%2]++;
						vis[v] = true;
						q.push(v);
					}
				}
			}
			ans += min(c[0],c[1]);
		}
	}
	cout<<"YES"<<endl<<ans;
}
//ll