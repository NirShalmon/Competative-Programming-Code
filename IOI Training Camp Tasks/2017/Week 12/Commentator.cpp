/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    long long ans = 0;
    int k;
    string s;
    cin>>k>>s;
    int lp = 0,rp = k-1;
    while(++rp <= s.size()){
        if(rp == s.size() || s[rp] != s[rp-k]){
           // if(rp == s.size())--rp;
            long long sz = rp - lp;
            ans += (sz - k) * (sz-k+1)/2;
            lp = rp -k+1;
            //if(rp + 1 == s.size()) break;
        }
    }
    cout<<ans;
}
