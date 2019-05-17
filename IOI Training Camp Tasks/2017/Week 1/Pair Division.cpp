/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int a[6000001];

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i = 0; i < n+1; ++i){
		int t;
		cin>>t;
		a[t] = t;
	}
	for(int i = 1; i <= n; ++i){
		if(a[i] != 0){
			if(a[2*i] != 0){
				cout<<a[i]<<' '<<2*i;
				return 0;
			}
			a[2*i] = a[i];
		}
	}
}