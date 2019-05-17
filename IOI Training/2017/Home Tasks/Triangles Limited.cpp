/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

vector<pair<int,int>> p;
vector<pair<int,int>> selected;

long long det(pair<int,int> a,pair<int,int> b, pair<int,int>c){
    long long dx1 = b.first - a.first;
    long long dx2 = c.first - a.first;
    long long dy1 = b.second - a.second;
    long long dy2 = c.second - a.second;
    return dx1 * dy2 - dx2*dy1;
}

int main() {
	ios::sync_with_stdio(false);
    int k,ni,n;
    cin>>k;
    for(int i = 0; i < k; ++i){
        cin>>ni;
        ++ni;
        n += ni;
        for(int j = 0; j < ni; ++j){
            int x,y;
            cin>>x>>y;
            p.push_back({abs(x),y});
        }
    }
    sort(p.begin(),p.end());
    int my = 1500000000;
    for(auto x : p){
        if(x.second < my){
            my = x.second;
            while(selected.size() >= 2 && det(selected[selected.size()-2],selected.back(),x) <= 0){
                selected.pop_back();
            }
            selected.push_back(x);
        }
    }
    double ans = 0;
    for(int i = 0; i < selected.size()-1; ++i){
        double x1 = selected[i].first;
        double y1 = selected[i].second;
        double x2 = selected[i+1].first;
        double y2 = selected[i+1].second;
        double m = (y2-y1)/(x2-x1);
        double b = x1 - y1/m;
        double h = y1-x1*m;
        ans = max(ans,b*h);
    }
    cout.precision(17);
    cout<<fixed<<ans;
}
