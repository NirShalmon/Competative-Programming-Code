/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

bool a[2000][2000];
bool b[2002][2002];
set<pair<int, int>> s;
vector<int>q,w,e,r;

void g() {
	while (true) {
		pair<int, int> t, y = { -1,-1 };
		for (auto z : s) {
			for (auto x : s) {
				if (z.first != x.first && z.second != x.second) {
					if (b[ z.first][x.second] && b[ x.first][z.second]) {
						t = z; y = x;
						goto e;
					}
				}
			}
		}
		break;
	e:
		s.erase(t);
		s.erase(y);
		s.erase({ t.first,y.second });
		s.erase({ y.first,t.second });
		if (b[t.first][t.second] == false ||
			b[y.first][t.second] == false ||
			b[t.first][y.second] == false ||
			b[y.first][y.second] == false) {
			cout << "qf";
		}
		b[t.first][t.second] = false;
		b[y.first][t.second] = false;
		b[t.first][y.second] = false;
		b[y.first][y.second] = false;
		e.push_back(min(t.first, y.first) + 1);
		r.push_back(max(t.first, y.first));
		q.push_back(1 + min(t.second, y.second));
		w.push_back(max(t.second, y.second));
		if (t.first == 2001 || y.first == 2001) {
			cout << "uf";
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (size_t i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	b[0][0] = a[0][0];
	b[0][n] = a[0][n - 1];
	b[n][0] = a[n - 1][0];
	b[n][n] = a[n - 1][n - 1];
	for (size_t i = 1; i < n; i++) {
		b[0][i] = a[0][i - 1] != a[0][i];
		b[n][i] = a[n - 1][i - 1] != a[n - 1][i];
		b[i][0] = a[i - 1][0] != a[i][0];
		b[i][n] = a[i - 1][n - 1] != a[i][n - 1];
	}
	for (size_t i = 1; i < n; i++) {
		for (size_t j = 1; j < n; j++) {
			b[i][j] = a[i][j] ^ a[i - 1][j] ^ a[i - 1][j - 1] ^ a[i][j - 1];
			if (b[i][j])s.insert({ i,j });
			//else if (s == 2 && ((a[i - 1][j - 1] && a[i][j]) || a[i - 1][j] && a[i][j - 1])) b[i][j] = 1;
		}
	}
	g();
	for (size_t i = 0; i <= n; i++) {
		int as = 0, bs = 0;
		for (size_t j = 0; j < n+1; j++) {
			as += b[i][j];
			bs += b[j][i];
		}
		if (as & 1 || bs & 1) {
			cout << "F";
		}
	}
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (b[i][j]) {
				int k = i + 1, l = j + 1;
				while (!b[k][j])++k;
				while (!b[i][l])++l;
				if (b[k][l]){
					//cout << "ee";
					s.erase({ k,l });
				}else s.insert({ k,l });
				b[i][j] ^= 1;
				b[i][l] ^= 1;
				b[k][j] ^= 1;
				b[k][l] ^= 1;
				s.erase({ i,j });
				s.erase({ i,l });
				s.erase({ k,j });
				q.push_back(j + 1);
				w.push_back(l);
				e.push_back(i + 1);
				r.push_back(k);
				if (i == 2000) {
					cout << "tf";
				}
				if (k == 2001) {
					cout << "yf";
				}
				g();
			}
		}
	}
	cout << q.size()<<'\n';
	for (size_t i = 0; i < q.size(); i++) {
		cout << q[i] << ' ' << w[i] << ' ' << e[i] << ' ' << r[i] << '\n';
	}
}