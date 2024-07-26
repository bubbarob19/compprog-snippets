template<class B> struct SegTree : public B {
	using T = typename B::T;

	size_t n; vector<T> tree;

	SegTree(vector<T>& data) {
		n = data.size();
		tree = vector<T>(n * 2, B::base);
		buildTree(data);
	}

	SegTree(size_t n) : n(n) {
		tree = vector<T>(n * 2, B::base);
	}

	T query(int l, int r) {
		l += n; r += n;
		T ans = B::base;
		while (l <= r) {
			if (l % 2 == 1) ans = B::merge(ans, tree[l++]);
			if (r % 2 == 0) ans = B::merge(ans, tree[r--]);
			l >>= 1; r >>= 1;
		}
		return ans;
	}

	T get(int i) {
		return tree[i + n];
	}

	void update(int i, int val) {
		i += n; tree[i] = val;
		for (i >>= 1; i >= 1; i >>= 1)
			tree[i] = B::merge(tree[2*i], tree[2*i+1]);
	}

	void buildTree(vector<T>& data) {
		for (int i = n; i < n + data.size(); i++)
			tree[i] = data[i-n];
		for (int i = n-1; i >= 1; i--)
			tree[i] = B::merge(tree[2*i], tree[2*i+1]);
	}
};

struct AddInt {
	using T = int;
	const T base = 0;
	T merge(T a, T b) { return a + b; }
};

struct MinInt {
	using T = int;
	const T base = numeric_limits<int>::max();
	T merge(T a, T b) { return min(a, b); }
};

struct MaxInt {
	using T = int;
	const T base = numeric_limits<int>::min();
	T merge(T a, T b) { return max(a, b); }
};

struct XorInt {
	using T = int;
	const T base = 0;
	T merge(T a, T b) { return a ^ b; }
};
