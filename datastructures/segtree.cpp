template<typename T> struct SegTree {
	int n = 1;
	T base;
	vector<T> data;
	vector<T> tree;
	function<T(T,T)> merge;

	SegTree(vector<T>& data, T base, function<T(T,T)> merge) : data(data), base(base), merge(merge) {
		while (n < data.size())
			n <<= 1;
		tree = vector<T>(n << 1, base);
		buildTree();
	}

	T query(int l, int r) {
		l += n; r += n;
		T ans = base;
		while (l <= r) {
			if (l % 2 == 1) ans = merge(ans, tree[l++]);
			if (r % 2 == 0) ans = merge(ans, tree[r--]);
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
			tree[i] = merge(tree[2*i], tree[2*i+1]);
	}

	void buildTree() {
		for (int i = n; i < n + data.size(); i++)
			tree[i] = data[i-n];
		for (int i = n-1; i >= 1; i--)
			tree[i] = merge(tree[2*i], tree[2*i+1]);
	}
};
