/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n,vv;
int p[100000];
vector<int> edj[100000];
long long dp[100000][101][2];
long long ans = 0;
long long sum[100000];
int parent[100000];
pair<long long,int> sp[101][3][2];
const long long inf = 999999999999999999ll;
bool splited[100000];

long long dfs(int u, int k,bool down){
    if(dp[u][k][down] != -1) return dp[u][k][down];
    dp[u][k][false] = 0;
    dp[u][k][true] = 0;
    if(sum[u] == -1){
        sum[u] = 0;
        for(int q = 0; q < edj[u].size(); ++q){
            int v = edj[u][q];
            if(v != parent[u]) parent[v] = u;
            sum[u] += p[v];
        }
    }
    long long pu = parent[u] < 0 ? 0 : p[parent[u]];
    for(int q = 0; q < edj[u].size(); ++q){
        int v = edj[u][q];
        if(v != parent[u]){
            dp[u][k][true] = max(dp[u][k][true],dfs(v,k,true));
            dp[u][k][false] = max(dp[u][k][false],dfs(v,k,false));
            if(k < vv) {
                dp[u][k][true] = max(dp[u][k][true],dfs(v,k+1,true)+sum[u]- pu);
            }
            if(k > 0){
                dp[u][k][false] = max(dp[u][k][false],dfs(v,k-1,false)+sum[u]-p[v]);
            }
        }
    }
    /*if(k < vv){ useless
        dp[u][k][true] = max(dp[u][k][true],sum[u]-pu);
    }
    if(k )*/
    if(k > 0) dp[u][k][false] = max(dp[u][k][false],sum[u]);
    if(!splited[u]){
        splited[u] = true;
        for(int w = 0; w <= vv; ++w){
            sp[w][0][0] = {-inf,-1};
            sp[w][0][1] = {-inf,-1};
            sp[w][1][0] = {-inf,-1};
            sp[w][1][1] = {-inf,-1};
            sp[w][2][0] = {-inf,-1};
            sp[w][2][1] = {-inf,-1};
            for(int q = 0; q < edj[u].size(); ++q){
                if(edj[u][q] != parent[u]){
                    auto x = dfs(edj[u][q],w,true);
                    if(x > sp[w][true][0].first){
                        sp[w][true][1] = sp[w][true][0];
                        sp[w][true][0] = {x,q};
                    }else if(x > sp[w][true][1].first) sp[w][true][1] = {x,q};
                    x = dfs(edj[u][q],w,false);
                    if(x > sp[w][false][0].first){
                        sp[w][false][1] = sp[w][false][0];
                        sp[w][false][0] = {x,q};
                    }else if(x > sp[w][false][1].first) sp[w][false][1] = {x,q};
                    x -= p[edj[u][q]];
                    if(x > sp[w][2][0].first){
                        sp[w][2][1] = sp[w][2][0];
                        sp[w][2][0] = {x,q};
                    }else if(x > sp[w][2][1].first) sp[w][2][1] = {x,q};
                }
            }
        }
        for(int w = 0; w <= vv; ++w){
            if(sp[w][0][0].second != sp[w][1][0].second) ans = max(ans,sp[w][0][0].first + sp[w][1][0].first);
            else{
                ans = max(ans,max(sp[w][0][1].first + sp[w][1][0].first,sp[w][0][0].first + sp[w][1][1].first));
            }
            if(w < vv){
                if(sp[vv-w][1][0].second != sp[vv-w-1][2][0].second) ans = max(ans,sp[vv-w][1][0].first + sp[vv-w-1][2][0].first + sum[u]);
                else{
                    ans = max(ans,sum[u] + max(sp[vv-w][1][1].first + sp[vv-w-1][2][0].first,sp[vv-w][1][0].first + sp[vv-w-1][2][1].first));
                }
            }
        }
    }
    /*for(int q = 0; q < edj[u].size(); ++q){
        if(edj[u][q] == parent[u]) continue;
        for(int e = q+1; e < edj[u].size(); ++e){
            if(edj[u][e] == parent[u]) continue;
            for(int w = 0; w <= vv; ++w){
                ans = max(ans,max(dfs(edj[u][q],w,true)+dfs(edj[u][e],w,false),dfs(edj[u][q],vv-w,false)+dfs(edj[u][e],vv-w,true)));
                if(w < vv){
                    ans = max(ans,max(dfs(edj[u][q],vv-w,true)+dfs(edj[u][e],vv-w-1,false) + sum[u] - p[edj[u][e]],dfs(edj[u][q],w,false)+dfs(edj[u][e],w+1,true) + sum[u] - p[edj[u][q]]));
                }
            }
        }
    }*/
    for(int q = 0; q < edj[u].size(); ++q){
        int v = edj[u][q];
        if(v != parent[u]){
            ans = max(ans,sum[u] + dfs(v,1,true));
        }
    }
    ans = max(ans,max(dp[u][k][true],dp[u][k][false]));
    auto dn = dp[u][k][true];
    auto up = dp[u][k][false];
    return dp[u][k][down];
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>vv;
    if(vv == 0 || n == 1){
        cout<<0;
        return 0;
    }
    for(int i = 0; i < n;)cin>>p[i++];
    for(int i = 0; i < n-1; ++i){
        int a,b;
        cin>>a>>b;
        edj[--a].push_back(--b);
        edj[b].push_back(a);
    }
    for(int i = 0; i < n; ++i){
        parent[i] = -1;
        for(int j = 0; j <= vv; ++j){
            dp[i][j][false] = -1;
            dp[i][j][true] = -1;
        }
        sum[i] = -1;
    }
    for(int i = 0; i <= vv; ++i){
        dfs(0,i,true);
        dfs(0,i,false);
    }
    cout<<ans;
}
