/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n,m,s;
vector<vector<int>> edj;
int d[100000],p[100000];

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    edj = vector<vector<int>>(n);
    for(int i = 0; i < m; ++i){
        int u,v;
        cin>>u>>v;
        edj[--u].push_back(--v);
        edj[v].push_back(u);
    }
    cin>>s;
    for(int i = 0; i < n;++i)d[i] = -1,p[i]=-2;
    d[--s] = 0;
    queue<int> q;
    q.push(s);
    p[s] = s;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : edj[u]){
            if(d[v] == -1){
                d[v] = d[u] + 1;
                p[v] = u;
                q.push(v);
            }
        }
    }
    for(int i = 0; i < n; ++i) cout<<d[i]<<' ';
    cout<<endl;
    for(int i = 0; i < n; ++i)cout<<p[i]+1<<' ';
}
