/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

struct cmp {
	bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
		return a.first > b.first;
	}
};

typedef map<pair<int, int>,int, cmp>::iterator iter;
const int inf = 1000000001;

class CHT { //min
	map<pair<int,int>,int,cmp> lines; //m,b -> xs. sorted by decreasing m
	map<int, pair<int, int>> xs; //lines by first x of affective range
	
public:
	//assumes different slopes
	int inter(pair<int, int> a, pair<int, int> b) {
		return (b.second - a.second + a.first - b.first - 1) / (a.first - b.first);
	}

	void rem(iter it) {
		int x = it->second;
		xs.erase(x);
		lines.erase(it);
	}

	bool fix(iter it) {
		if (it == lines.begin() || next(it) == lines.end()) return false;
		int affectStart = inter(prev(it)->first,it->first);
		int affectEnd = inter(it->first, next(it)->first);
		if (affectStart >= affectEnd) {
			xs.erase(it->second);
			lines.erase(it);
			return true;
		}
		return false;
	}

	void xUpdate(iter it) {
		int m = it->first.first;
		int b = it->first.second;
		lines[{m, b}] = it == lines.begin() ? -inf : inter(prev(it)->first, { m,b });
		xs.insert({ lines[{m,b}],{ m,b } });
	}

	void insert(int m, int b) {
		auto it = lines.lower_bound({ m,b });
		if (it != lines.end() && it->first.first == m) {
			if (it->first.second <= b) return;
			rem(it);
			it = lines.lower_bound({ m,b });
		}
		int affectStart = it == lines.begin() ? -inf : inter(prev(it)->first, { m,b });
		int affectEnd = it == lines.end() ? inf : inter({ m,b }, it->first);
		if (affectStart >= affectEnd) return;
		lines.insert({ {m,b},-inf - 1 });
		do {
			it = lines.upper_bound({ m,b });
		} while (it != lines.end() && fix(it));
		do {
			it = lines.lower_bound({ m,b });
		} while (it != lines.begin() && fix(prev(it)));
		it = lines.lower_bound({ m,b });
		if (next(it) != lines.end()) {
			xs.erase(next(it)->second);
			xUpdate(next(it));
		}
		xUpdate(it);
		assert(lines.size() == xs.size());
	}

	int getMin(int x) {
		auto line = prev(xs.upper_bound(x))->second;
		return line.first * x + line.second;
	}
};



int main() {
	ios::sync_with_stdio(false);
	vector<pair<int, int>> l;
	CHT c;
	for (size_t i = 0; i < 10000; i++) {
		l.push_back({ rand() % 100000,rand() % 100000 });
		c.insert(l.back().first, l.back().second);
		for (size_t j = 0; j < 100; j++) {
			int x = rand() % 10;
			int chtMin = c.getMin(x);
			int realMin = 999999999;
			for (auto t : l) {
				if (t.first * x + t.second < realMin) realMin = t.first * x + t.second;
			}
			assert(realMin == chtMin);
		}
	}
}