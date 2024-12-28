template <class B> struct LazySegTree : public B {
	using T = typename B::T;
	using L = typename B::L;

	size_t n;
	vector<T> tree;
	vector<L> lazy;
	vector<bool> lazyFlag;

	LazySegTree(size_t n) : n(n) {
		tree = vector<T>(4 * n, B::base);
		lazy = vector<L>(4 * n, B::lazyBase);
		lazyFlag = vector<bool>(4 * n);
	}

	LazySegTree(vector<T>& data) {
		n = data.size();
		tree = vector<T>(4 * n, B::base);
		lazy = vector<L>(4 * n, B::lazyBase);
		lazyFlag = vector<bool>(4 * n);
		buildTree(1, 0, n - 1, data);
	}

	void propagate(int node, int start, int end) {
		if (!lazyFlag[node])
			return;

		tree[node] = B::apply(tree[node], lazy[node], start, end);

		if (start != end) {
			lazy[node * 2] = B::compose(lazy[node * 2], lazy[node]);
			lazy[node * 2 + 1] = B::compose(lazy[node * 2 + 1], lazy[node]);
			lazyFlag[node * 2] = lazyFlag[node * 2 + 1] = true;
		}

		lazy[node] = B::lazyBase;
		lazyFlag[node] = false;
	}

	void buildTree(int node, int start, int end, vector<T>& data) {
		if (start == end) {
			tree[node] = data[start];
			return;
		}
		int mid = (start + end) / 2;
		buildTree(node * 2, start, mid, data);
		buildTree(node * 2 + 1, mid + 1, end, data);
		tree[node] = B::merge(tree[node * 2], tree[node * 2 + 1]);
	}

	void updateRange(int node, int start, int end, int l, int r, L& val) {
		propagate(node, start, end);

		if (start > r || end < l)
			return;
		if (start >= l && end <= r) {
			lazy[node] = val;
			lazyFlag[node] = true;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		updateRange(node * 2, start, mid, l, r, val);
		updateRange(node * 2 + 1, mid + 1, end, l, r, val);

		tree[node] = B::merge(tree[node * 2], tree[node * 2 + 1]);
	}

	T queryRange(int node, int start, int end, int l, int r) {
		propagate(node, start, end);

		if (start > r || end < l)
			return B::base;
		if (start >= l && end <= r)
			return tree[node];

		int mid = (start + end) / 2;
		T left = queryRange(node * 2, start, mid, l, r);
		T right = queryRange(node * 2 + 1, mid + 1, end, l, r);
		return B::merge(left, right);
	}

	void update(int l, int r, L val) {
		updateRange(1, 0, n - 1, l, r, val);
	}

	T query(int l, int r) {
		return queryRange(1, 0, n - 1, l, r);
	}
};

enum UpdateType { ADD, SET };

struct Update {
	UpdateType type = ADD;
	ll val = 0;
};

struct AddSet {
	using T = ll;
	using L = Update;

	const T base = 0;
	const L lazyBase = {};

	T merge(T& a, T& b) { return a + b; }

	T apply(T& a, L& val, int start, int end) {
		if (val.type == SET)
			return (end - start + 1) * val.val;
		else if (val.type == ADD) 
			return a + (end - start + 1) * val.val;
		else 
			return a;
	}

	L compose(L& bottom, L& top) { 
		if (top.type == SET)
			return top;

		if (bottom.type == SET)
			return {SET, bottom.val + top.val};

		return {ADD, bottom.val + top.val};
	}
};
