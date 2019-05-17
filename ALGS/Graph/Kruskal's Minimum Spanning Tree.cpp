/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

class disjoint_set {
private:
	vector<int> id;
	vector<int> rank;
public:

	disjoint_set(int size) {
		id = vector<int>(size);
		rank = vector<int>(size);
		for (size_t i = 0; i < size; i++) {
			id[i] = i;
		}
	}

	int size() {
		return id.size();
	}

	int getRoot(int x) {
		if (x != id[x]) {
			id[x] = getRoot(id[x]);
		}
		return id[x];
	}

	bool same(int x, int y) {
		return getRoot(x) == getRoot(y);
	}

	void merge(int x, int y) {
		int xRoot = getRoot(x);
		int yRoot = getRoot(y);
		if (xRoot == yRoot) return;
		if (rank[xRoot] < rank[yRoot]) {
			id[xRoot] = yRoot;
		} else if (rank[xRoot] > rank[yRoot]) {
			id[yRoot] = xRoot;
		} else {
			id[xRoot] = yRoot;
			rank[yRoot]++;
		}
	}
};

pair<int,pair<int,int>> edj[200000];

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i = 0; i < m; ++i){
        cin>>edj[i].second.first>>edj[i].second.second>>edj[i].first;
        --edj[i].second.second;
        --edj[i].second.first;
    }
    sort(edj,edj+m);
    disjoint_set s(n);
    vector<pair<int,int>> ans;
    for(int i = 0; i < m; ++i){
        if(!s.same(edj[i].second.first,edj[i].second.second)){
            ans.push_back({edj[i].second.first+1,edj[i].second.second+1});
            s.merge(edj[i].second.first,edj[i].second.second);
        }
    }
    cout<<ans.size()<<endl;
    for(auto a : ans) cout<<a.first<<' '<<a.second<<'\n';
}
