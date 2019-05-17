/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int rnd() {
	return (rand() % (1 << 15)) << 15 + (rand() % (1 < 15));
}

struct node {
	node *l, *r;
	int key, value, sz;

	node(int value) {
		l = r = NULL;
		this->value = value;
		key = rnd();
		update();
	}

	int size() {
		return this == NULL ? 0 : sz;
	}

	void update() {
		sz = (l == NULL ? 0 : l->sz) + (r == NULL ? 0 : r->sz) + 1;
	}
};

node* root;

int rnk(int x,node* p) {
	if (p == NULL) return -2000000000;
	if (p->value == x) return p->l->size();
	if (p->value > x) return rnk(x, p->l);
	return rnk(x, p->r) + 1 + p->l->size();
}

node* select(int i, node* p) {
	if (p == NULL) return NULL;
	int lsz = p->l->size();
	if (i < lsz) return select(i,p->l);
	if (i == lsz) return p;
	return select(i - lsz-1, p->r);
}

node* merge(node *a, node *b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->key < b->key) {
		a->r = merge(a->r, b);
		a->update();
		return a;
	}else {
		b->l = merge(a, b->l);
		b->update();
		return b;
	}
}

pair<node*, node*> split(int x, node* p) {
	if (p == NULL) return{ NULL,NULL };
	if (p->value == x) {
		auto t = p->l;
		p->l = NULL;
		p->update();
		return{ t,p };
	}
	if (p->value < x) {
		auto b = split(x, p->r);
		p->r = b.first;
		p->update();
		return{ p,b.second };
	}
	auto b = split(x, p->l);
	p->l = b.second;
	p->update();
	return{ b.first,p };
}

void init() {}

void remove_element(int x) {
	auto a = split(x, root);
	auto b = split(x + 1, a.second);
	root = merge(a.first, b.second);
	delete b.first;
}

bool element_exists(int x) {
	return rnk(x, root) >= 0;
}

void insert_element(int x) {
	if (element_exists(x)) return;
	node* p = new node(x);
	auto a = split(x, root);
	auto b = merge(a.first, p);
	root = merge(b, a.second);
}

int get_size() {
	return root->size();
}

int index_select(int i) {
	if (i <= 0 || i > get_size()) return -2000000000;
	return select(i - 1, root)->value;
}

int element_rank(int x) {
	auto t = rnk(x, root);
	return t >= 0 ? t+1 : -2000000000;
}

/*int main() {
	ios::sync_with_stdio(false);
	init();
	set<int> s;
	for (int i = 0; i < 1000; ++i) {
		auto t = rnd();
		insert_element(t);
		s.insert(t);
	}
	for (size_t i = 0; i < 10000; i++) {
		int t = rnd();
		assert(s.size() == get_size());
		if (rand() & 1) {
			insert_element(t);
			s.insert(t);
		}
		else {
			t = rand() % get_size();
			int v = *next(s.begin(), t);
			s.erase(v);
			remove_element(v);
		}
		t = rnd();
		assert((s.find(t) != s.end()) == element_exists(t));
		t = rand() % get_size();
		assert(*next(s.begin(), t) == index_select(t + 1));
		assert(element_rank(index_select(t + 1)) == t + 1);
	}
}*/