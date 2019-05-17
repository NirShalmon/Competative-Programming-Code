/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int a[100000];

int main() {
	ios::sync_with_stdio(false);
    int n,k;
    cin>>n>>k;
    int c = 0;
    for(int i = 0; i < n; ++i){
        int p;
        cin>>p;
        if(p == k){
            c = i;
        }else{
            a[i] = p > k ? 1 : -1;
        }
    }
    map<int,int> l;
    l[0] = 1;
    long long sum = 0;
    for(int i = c+1; i < n; ++i){
        sum += a[i];
        l[sum]++;
    }
    sum = 0;
    long long ans = l[0];
    for(int i = c-1; i >= 0; --i){
        sum += a[i];
        ans += l[-sum];
    }
    cout<<ans;
}
