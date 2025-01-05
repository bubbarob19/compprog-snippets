template<class B> struct SegTree : public B {
	using T = typename B::T;

	size_t n; vector<T> tree;

	SegTree(vector<T>& data) {
		n = 1 << (32 - __builtin_clz(data.size()));
		tree = vector<T>(n * 2, B::base);
		buildTree(data);
	}

	SegTree(size_t sz) {
		n = 1 << (32 - __builtin_clz(sz));
		tree = vector<T>(n * 2, B::base);
	}

	T query(int l, int r) {
		l += n; r += n;
		T left = B::base, right = B::base;
		while (l <= r) {
			if (l % 2 == 1) left = B::merge(left, tree[l++]);
			if (r % 2 == 0) right = B::merge(tree[r--], right);
			l >>= 1; r >>= 1;
		}
		return B::merge(left, right);
	}

	T get(int i) {
		return tree[i + n];
	}

	void update(int i, T val) {
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
