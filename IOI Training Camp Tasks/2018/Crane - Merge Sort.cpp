/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include <iostream>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include<ctime>

using namespace std;

vector<int> s[3];
vector<pair<int, int>> moves;

void move(int from, int to) {
	if (from == to) return;
	s[to].push_back(s[from].back());
	s[from].pop_back();
	moves.push_back({ from,to });
}

void pile() {
	while (s[0].size() > 0 || s[1].size() > 0) {
		int f = rand() % 2;
		if (s[0].size() == 0) f = 1;
		else if (s[1].size() == 0) f = 0;
		move(f, 2);
	}
}

void optimize() {
	bool changed = false;
	do {
		changed = false;
		for (int i = 0; i < moves.size(); ++i) {
			if (moves[i].first == moves[i].second) {
				moves.erase(moves.begin() + i);
				changed = true;
				--i;
			}else if (i + 1 < moves.size() && moves[i].second == moves[i + 1].first) {
				moves[i].second = moves[i + 1].second;
				moves.erase(moves.begin() + i + 1);
				changed = true;
				--i;
			}
		}
	} while (changed);
}

void transfer(int from, int to, int amount, bool inc) {
	if (amount == 0)return;
	if (amount == 1) {
		move(from, to);
		return;
	}
	int a, b;
	if (from == to) a = (from + 1) % 3;
	else a = 1 ^ 2 ^ from^to;
	b = 1 ^ 2 ^ a^to;
	transfer(from, a, amount / 2, !inc);
	transfer(from, b, (amount + 1) / 2, !inc);
	int fa = amount / 2;
	int fb = (amount + 1) / 2;
	while (fa > 0 || fb > 0) {
		int nx;
		if (fa == 0) nx = b;
		else if (fb == 0) nx = a;
		else {
			if (inc) {
				if (s[a].back() < s[b].back()) nx = a;
				else nx = b;
			} else {
				if (s[a].back() < s[b].back()) nx = b;
				else nx = a;
			}
		}
		if (nx == a)--fa;
		else --fb;
		move(nx, to);
	}
}

int main() {
	ios::sync_with_stdio(false);
	srand(time(NULL));
	int n;
	cin >> n;
	for (size_t i = 0; i < 3; i++) {
		int a;
		cin >> a;
		while (a--) {
			int t;
			cin >> t;
			s[i].push_back(t);
		}
	}
	pile();
	transfer(2, 0, n, true);
	optimize();
	cout << moves.size()<<endl;
	for (auto p : moves) {
		cout << (char)(p.first + 'A') << ' ' << (char)(p.second + 'A') << endl;
	}
}