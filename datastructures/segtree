struct segtree {
	int n;
	int base;
	vector<int> tree;
	function<int(int,int)> merge;

	segtree(vector<int>& arr, const function<int(int,int)>& merge, const int base) {
		this->merge = merge;
		this->base = base;
		n = 1;
		while (n < arr.size())
			n <<= 1;
		tree = vector<int>(n * 2, base);
		for (int i = 0; i < arr.size(); i++) {
			set(i, arr[i]);
		}
	}

	void set(int i, int val) {
		i += n; tree[i] = val;
		for (i >>= 1; i >= 1; i >>= 1) {
			tree[i] = merge(tree[2*i], tree[2*i+1]);
		}
	}

	void add(int i, int val) {
		set(i, tree[i+n] + val);
	}

	void subtract(int i, int val) {
		set(i, tree[i+n] - val);
	}

	int query(int l, int r) {
		l += n; r += n;
		int ans = base;
		while (l <= r) {
			if (l % 2 == 1) ans = merge(ans, tree[l++]);
			if (r % 2 == 0) ans = merge(ans, tree[r--]);
			l >>= 1; r >>= 1;
		}
		return ans;
	}
};
