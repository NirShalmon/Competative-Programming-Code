/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int maxd = 10000;

pair<int,int> dp[300][31];
bool pl[10000];
int a[300];
int c[300][300];

int main(){
	ios::sync_with_stdio(false);
	int v,p;
	cin>>v>>p;
	for(int i = 0; i < v; ++i){
		cin>>a[i];
		pl[--a[i]] = true;;
	}
	for(int i = 1; i < v; ++i){
		dp[i][1].first = dp[i-1][1].first + i * (a[i] - a[i-1]);
	}
	for(int i = 0; i < v; ++i){
		for(int j = i+1; j < v; ++j){
			for(int k = i+1; k < j; ++k){
				c[i][j] += min(a[j] - a[k] ,a[k] - a[i]);
			}
		}
	}
	for(int i = 2; i <=p; ++i){
		for(int j = i-1; j < v; ++j){
			dp[j][i].first = 1000000000;
			for(int k = i-2; k < j; ++k){
				if(dp[j][i].first > dp[k][i-1].first + c[k][j]){
					dp[j][i] = make_pair(dp[k][i-1].first + c[k][j],k); 
				}
			}
		}
	}
	int ans = dp[v-1][p].first,ansi = v-1;
	int extra = 0,cnt = 1;
	for(int i = v-2; i >= p; --i){
		extra += cnt * (a[i+1] - a[i]);
		if(dp[i][p].first + extra < ans){
			ans = dp[i][p].first + extra;
			ansi = i;
		}
		++cnt;
	}
	cout<<ans<<endl;
	vector<int> vv;
	for(int i = p; i >= 1; --i){
		vv.push_back(a[ansi]+1);
		ansi = dp[ansi][i].second;
	}
	for(int i = vv.size()-1; i >= 0; --i) cout<<vv[i]<<' ';
}
