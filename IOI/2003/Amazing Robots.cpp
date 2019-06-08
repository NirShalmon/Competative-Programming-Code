/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

#define sz (401*401*12)

class gaurd {
public:
	int pos;
	int d;
	int dis;
	int disl;
	int prevpos;

	gaurd(int pos, int d, int dis) {
		dis -= 1;
		(*this).pos = pos;
		(*this).d = d;
		(*this).dis = dis;
		disl = dis;
		prevpos = pos;
	}
};

void advance(gaurd &g) {
	g.prevpos = g.pos;
	g.pos += g.d;
	if (--g.disl == 0) {
		g.disl = g.dis;
		g.d = -g.d;
	}
}

int r[2],c[2];
bool mp[2][401];
vector<gaurd> gaurds[2];
pair<int,int> v[sz];
int dt = 401 * 401;
int rb1, rb2;

int toD(char d) {
	switch (d) {
		case 'E':
			return 1;
			break;
		case 'W':
			return -1;
			break;
		case 'N':
			return -20;
			break;
		case 'S':
			return 20;
			break;
	}
}

char fromD(int d) {
	//int d = a - b;
	switch (d) {
		case 1:
			return 'E';
			break;
		case -1:
			return 'W';
			break;
		case -20:
			return 'N';
			break;
		case 20:
			return 'S';
			break;
		/*default:
			/*if (b % 20 == 0) return 'W';
			if (b / 20 == 0) return 'N';
			if (b % 20 == c[e] - 1) return 'E';
			return 'S';*/
	}
}

void read(int mpn,int &rb){
	cin >> r[mpn] >> c[mpn];
	//cout << r[mpn] << ' ' << c[mpn] << endl;
	for (size_t i = 0; i < r[mpn]; i++) {
		string s;
		cin >> s;
		//cout << s<<endl;
		for (size_t j = 0; j < c[mpn]; j++) {
			mp[mpn][i*20+j] = s[j] != '#';
			if (s[j] == 'X') rb = i * 20 + j;
		}
	}
	int gc;
	cin >> gc;
	for (size_t i = 0; i < gc; i++) {
		int y, x, l;
		char d;
		cin >> y >> x >> l >> d;
		//cout << y << ' ' << x << ' ' << l << ' ' << d << endl;
		gaurds[mpn].push_back(gaurd((--y) * 20 + (--x), toD(d), l));
	}
}

vector<pair<int,int>> edj(int u) {
	int d[] = { 20,-20,1,-1 };
	int a = (u%dt) / 401;
	int b = (u%dt) % 401;
	vector<pair<int,int>> ans;
	for (int w : d) {
		int na = 400, nb = 400;
		if (a != 400 && a + w >= 0 && a + w<20*r[0] && !(a % 20  == c[0]-1 && w == 1) && !(a % 20 == 0 && w == -1)) {
			if (!mp[0][a + w]) {
				na = a;
			} else na = a + w;
			for (auto g : gaurds[0]) {
				if (g.pos == na || (g.pos == a && g.prevpos == a + w)) {
					goto skp;
				}
			}
		}
		if (b != 400 && b + w >= 0 && b + w < 20 * r[1] && !(b % 20 == c[1] - 1 && w == 1) && !(b % 20 == 0 && w == -1)) {
			if (!mp[1][b + w]) {
				nb = b;
			} else nb = b + w;
			for (auto g : gaurds[1]) {

				if (g.pos == nb || (g.pos == b && g.prevpos == b + w)) {
					goto skp;
				}
			}
		}
		ans.push_back(make_pair( (401 * na + nb + (u / dt + 1)*dt) % sz,w ));
		nb = nb;
	skp:
		nb = nb;
	}
	return ans;
}

void advanceAll() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < gaurds[i].size(); ++j) {
			advance(gaurds[i][j]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	read(0,rb1);
	read(1,rb2);
	queue<int> q;
	advanceAll();
	for (int i = 0; i < sz; ++i) v[i] = { -1,-1 };
	q.push(rb1 * 401 + rb2);
	v[rb1 * 401 + rb2] = { rb1 * 401 + rb2,0 };
	int lt = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u / dt != lt % 12) {
			++lt;
			advanceAll();
		}
		for (auto w : edj(u)) {
			if (w.first % dt == 400 * 401 + 400) {
				pair<int,int> z = w;
				v[w.first] = { u,w.second };
				z = v[w.first];
				//cout << lt+1 << endl;
				vector<char> ans;
				while (z.first != v[z.first].first) {
					int a = z.first%dt % 401;
					//int c = v[z]%dt%401;
					int b = z.first%dt / 401;
					//int e = v[z] % dt / 401;
					//char d = a == c ? fromD(b,e,0) : fromD(a,c,1);*/
					char d = fromD(z.second);
					int t = z.first / dt;
					ans.push_back(d);
					//cout << v[964427].second << endl;
					z = v[z.first];
				}
				char d = fromD(z.second);
				ans.push_back(d);
				cout << ans.size() << endl;
				for (int i = ans.size()-1; i >= 0; --i) cout << ans[i] << endl;
				return 0;
			}
			if (v[w.first].first == -1) {
				//cout << lt << " (" << w.first % 401 / 20 << ',' << w.first % 401 % 20 << ") (" << w.first %dt/ 401 / 20 << ',' << w.first %dt/ 401 % 20<<')' << endl;
				//cout << v[964427].second << endl;
				int a = w.first%dt % 401;
				//int c = v[z]%dt%401;
				int b = w.first%dt / 401;
				if (w.first == 964427) {

					a = a;
				}
				v[w.first] = { u,w.second };
				q.push(w.first);
			}
		}
	}
	cout << -1;
	return 0;

}
