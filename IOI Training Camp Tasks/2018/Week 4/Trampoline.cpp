/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

long long p[1100000];
long long edj[1100000];
long long vis[1100000];
bool cycle[1100000];
long long cycleback[1100000];
long long ans[1100000];
vector<int> redj[1100000];
long long cyclelen;
long long dfsloop[1100000];
long long n,k,m;
bool dfsrun[1100000];

void dfs(long long u,long long d){
	dfsrun[u] = true;
	vis[u] = true;
	if(d <= m) ans[u] = cycleback[ans[edj[u]]]; //go back in the cycle
	else ans[u] = redj[ans[edj[u]]][dfsloop[ans[edj[u]]]]; //go back down the dfs tree
	for(dfsloop[u] = 0;  dfsloop[u] < redj[u].size(); ++dfsloop[u]){
		if(redj[u][dfsloop[u]] != cycleback[u]){ //if this is out of the circle
			dfs(redj[u][dfsloop[u]],d+1);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k>>m;
	for(int i = 0; i < n ;++i)cin>>p[i],vis[i] = -1,ans[i]=-1,cycleback[i]=-1;
	int l = 0,r=k;
	for(int i = 0; i < n; ++i){
		while(r < n-1 && p[r+1] - p[i] < p[i] - p[l])++l,++r;
		//cout<<l<<' '<<r<<endl;
		if(l == i) edj[i] = r;
		else if(r == i) edj[i] = l;
		else if(p[r] - p[i] > p[i] - p[l]) edj[i] = r;
		else edj[i] = l;
		redj[edj[i]].push_back(i);
	}
	//for(int i = 0; i < n; ++i) cout<<edj[i]<<endl;
	for(int i = 0; i < n; ++i){
		if(vis[i]== -1){
			//cout<<i<<endl;
			vis[i] = 0;
			long long pos = i;
			while(vis[edj[pos]] == -1){
				vis[edj[pos]] = vis[pos]+1;
				pos = edj[pos];
			}
			//cout<<pos<<' '<<vis[pos]<<' '<<vis[edj[pos]]<<endl;
			cyclelen = 1+vis[pos]-vis[edj[pos]];
			while(!cycle[edj[pos]]){
				cycleback[edj[pos]] = pos;
				pos = edj[pos];
				cycle[pos] = true;
			}
			ans[pos] = pos;
			for(int j = 0; j < m%cyclelen; ++j) ans[pos] = edj[ans[pos]];
			while(ans[edj[pos]] == -1){
				ans[edj[pos]] = edj[ans[pos]];
				pos = edj[pos];
			}
			while(!dfsrun[edj[pos]]){
				dfs(edj[pos],0);
				pos = edj[pos];
			}
		}
	}
	for(int i = 0; i < n; ++i)cout<<ans[i]+1<<' ';
}


