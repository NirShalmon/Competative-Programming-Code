/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n;

pair<int,int> gcd(int x,int y){
    if(y == 0)return {1,0};
    pair<int,int> a = gcd(y,x%y);
    return {a.second,a.first - (x/y)*a.second};
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    while(n--){
        int x,y;
        cin>>x>>y;
        auto t = gcd(abs(x),abs(y));
        if(x < 0) t.first *=-1;
        if(y < 0) t.second *=-1;
        cout<<t.first<<' '<<t.second<<'\n';
    }
}
