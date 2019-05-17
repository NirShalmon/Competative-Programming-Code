/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

typedef map<long long,long long,greater<long long>>::iterator iter;

int n;
long long h[100000],w[100000];
long long a[100000];
map<long long,long long,greater<long long>> lines;
map<long long,pair<long long,long long>> intersect;
const long long inf = 999999999999999999ll;

long long intersection(iter it,iter f){
    auto d = f->first - it->first;
    auto u = it->second - f->second;
    bool neg = (d < 0) ^ (u < 0);
    auto ans = (abs(u) + abs(d) - 1) / abs(d);
    if(neg) ans *= -1;
    //if((it->second - f->second) % (f->first - it->first) != 0) ++ans;   //round up
    return ans;
}

long long intersection(iter it){
    if(it == lines.begin()) return -inf;
    return intersection(it,prev(it));
}

void addLine(int i){
    long long m = -2*h[i];
    long long b = h[i] * h[i] + a[i] - w[i];
    if(lines.upper_bound(m) != lines.end()) intersect.erase(intersection(lines.upper_bound(m))); //erase the intersection of the next line
    auto it = lines.find(m);
    if(it != lines.end()){  //there is a line with slope m already
        if(b < it->second){
            intersect.erase(intersection(it));
            it->second = b;
        }else{
            if(++it != lines.end()){
                intersect.insert({intersection(it),{it->first,it->second}});
            }
            return;
        }
    }else{
        it = lines.insert({m,b}).first;
    }
    if(it != lines.begin() && next(it) != lines.end() && intersection(prev(it),next(it)) >= intersection(it,next(it))){ //if this line never becomes minimum
        auto f = next(it);
        lines.erase(it);
        intersect.insert({intersection(f),{f->first,f->second}});
    }else{  //this line becomes minimum
        while(it != lines.begin() && prev(it) != lines.begin() && intersection(prev(prev(it)),it) <= intersection(prev(prev(it)),prev(it))){
            intersect.erase(intersection(prev(it)));
            lines.erase(prev(it));
        }
        while(next(it) != lines.end() && next(next(it)) != lines.end() && intersection(it,prev(prev(it,-1),-1)) >= intersection(prev(it,-1),prev(prev(it,-1),-1))){
            intersect.erase(intersection(next(next(it))));  //keep the intersection of the line after it erased
            lines.erase(next(it));
        }
        intersect.insert({intersection(it),{m,b}});
        if(next(it) != lines.end()){
            intersect.insert({intersection(next(it)),{next(it)->first,next(it)->second}});
        }
    }
    /*auto q = lines.begin();
    auto w = intersect.begin();
    for(; q != lines.end(); ++q,++w){
        cout<<q->first<<' '<<q->second<<' '<<intersection(q)<<' '<<w->first<<' '<<w->second.first<<' '<<w->second.second;
        cout<<endl;
    }
    cout<<endl;*/
}

long long getMin(int x){
    auto it = prev(intersect.upper_bound(x));
    return it->second.first * x + it->second.second;
}

void read(){
    cin>>n;
    for(int i = 0; i < n; ++i)cin>>h[i];
    cin>>w[0];
    for(int i = 1; i < n; ++i){
        cin>>w[i];
        w[i] += w[i-1];
    }
}

void rnd(){
    lines.clear();
    intersect.clear();
    n = 3;
    for(int i = 0; i < n; ++i){
        h[i] = rand() % 10;
        w[i] = rand() % 10 - 5;
        if(i) w[i] += w[i-1];
    }
}

int main(){
    ios::sync_with_stdio(false);
    read();
    a[0] = 0;
    for(int i = 1; i < n; ++i){
        addLine(i-1);
        a[i] = getMin(h[i]) + w[i-1] + h[i] * h[i];
        /*long long test = inf;
        for(int j = 0; j < i; ++j){
            test = min(test,a[j] + w[i-1] - w[j] + (h[i] - h[j]) * (h[i] - h[j]));
        }
        if(test != a[i]){
            cout<<"err";
        }*/
    }
    cout<<a[n-1];
}
