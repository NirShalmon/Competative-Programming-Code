/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition.
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
int parent[1000];
vector<int> children[1000];
int height[1000];

//Input format: number of nodes n followed by the list of parents of nodes 1,...,n-1(0 is the root node)
void read_tree() {
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		parent[i] = p;
		children[p].push_back(i);
	}
}

void calc_height(int node) {
	for (int child : children[node]) {
		height[child] = height[node] + 1;
		calc_height(child);
	}
}

int lca(int a, int b) {
	if (height[a] > height[b]) swap(a, b); //now height[a] <= height[b]
	while (height[b] > height[a]) b = parent[b]; //climb up until a and b are in the same height
	while (a != b) { //climb up from both a and b until they meet
		a = parent[a];
		b = parent[b];
	}
	return a;
}

int main() {
	read_tree();
	height[0] = 0;
	calc_height(0);

	while (true) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b)<<endl;
	}
}													