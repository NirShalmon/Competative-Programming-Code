/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

vector<pair<int,int>> edj[100000];
bool v[100000];

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i = 0; i < m; ++i){
        int u,v,w;
        cin>>u>>v>>w;
        edj[--u].push_back({--v,w});
        edj[v].push_back({u,w});
    }
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> q;
    vector<pair<int,int>> ans;
    for(int i = 0; i < n; ++i){
        if(!v[i]){
            v[i] = true;
            for(auto e : edj[i]){
                q.push({e.second,{i,e.first}});
            }
            while(!q.empty()){
                auto e = q.top();
                q.pop();
                if(!v[e.second.second]){
                    ans.push_back(e.second);
                    v[e.second.second] = true;
                    for(auto et : edj[e.second.second]){
                        q.push({et.second,{e.second.second,et.first}});
                    }
                }
            }
        }
    }
    cout<<ans.size()<<'\n';
    for(auto x : ans) cout<<x.first+1<<' ' <<x.second+1<<'\n';
}
