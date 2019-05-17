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

int n;
int x[8001],y[8001];
long long xc[8001][2],yc[8001][2]; //xc[i] is correct x and y[i]

int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	x[0] = 0,y[0]=0;
	for(int i = 1; i <= n; ++i){
		cin>>x[i]>>y[i];
	}
	for(int i = 0; i < n+1; ++i){
		xc[i][0] = abs(y[i]);
		yc[i][0] = abs(x[i]);
	}
	for(int i = 1; i <= n; ++i){
		for(int j = 0; j <= n; ++j){
			xc[j][i%2] = min(xc[j][(i+1)%2]+abs(x[i] - x[i-1]),yc[i][(i+1)%2]+abs(y[j]-y[i-1]));
			yc[j][i%2] = min(xc[i][(i+1)%2]+abs(x[j] - x[i-1]),yc[j][(i+1)%2]+abs(y[i]-y[i-1]));
		}
	}
	long long ans = 1000000000000000000ll;
	for(int i = 0; i <= n; ++i){
		ans = min(ans,min(xc[i][n%2],yc[i][n%2]));
	}
	cout<<ans;
}
//ll