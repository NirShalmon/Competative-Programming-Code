/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
double l[100000],r[100000];
double sl[100000],sr[100000];

double val(int i ,int j){
    return min(sl[i],sr[j]) - i - j-2;
}

bool chk(int i,int j){
    if(j == n-1) return false;
    return val(i,j) < val(i,j+1);
}

int main(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>l[i]>>r[i];
    }
    sort(l,l+n,greater<double>());
    sort(r,r+n,greater<double>());
    sl[0] = l[0];
    sr[0] = r[0];
    for(int i = 1; i < n; ++i){
        sl[i] = sl[i-1] + l[i];
        sr[i] = sr[i-1] + r[i];
    }
    double ans = 0;
    for(int i = 0; i < n; ++i){
        int lo = 0;
        int hi = n-1;
        while(lo < hi){
            int mid = (lo + hi) / 2;
            if(chk(i,mid)) lo = mid + 1;
            else hi = mid;
        }
        ans = max(ans,val(i,lo));
    }
    printf("%.4lf",ans);
}
