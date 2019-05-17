/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int t;
long long pw[1000000];
long long mod = 100000007;

int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    pw[0] = 1;
    for(int i = 1; i < 1000000; ++i) pw[i] = (pw[i-1] * 26 )% mod;
    while(t--){
        string s;
        cin>>s;
        int n = s.size();
        int partCount = 0;
        int lastP = -1;
        long long l = 0;
        long long r = 0;
        for(int i = 0; i * 2 < n-1; ++i){
            bool ok = true;
            l = (l * 26 + s[i] - 'a') % mod;
            r =(r+ (s[n-1-i]-'a') * pw[i - lastP-1] )% mod;
          //  cout<<l<<' '<<r<<endl;
            if(l != r) ok = false;
            else{
                int k = 0;
                for(int j = n-1-i; j <= n-lastP-2; ++j){
                    if(s[lastP + k++ + 1] != s[j]){
                        ok = false;
                        break;
                    }
                }
            }
            if(ok){
            l = 0;
            r = 0;
                lastP = i;
                partCount += 2;
            }
        }
        if(n%2 == 1 || lastP != n/2-1) ++partCount;
        cout<<partCount<<endl;
    }
}
