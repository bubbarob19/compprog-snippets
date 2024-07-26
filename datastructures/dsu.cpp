struct DSU {
	vector<int> parent;
	vector<int> setsize;

	DSU(int n) {
		parent = vector<int>(n);
		iota(parent.begin(), parent.end(), 0);
		setsize = vector<int>(n, 1);
	}

	int find(int node) {
		if (node == parent[node])
			return node;
		return (parent[node] = find(parent[node]));
	}

	bool same(int n1, int n2) {
		return find(n1) == find(n2);
	}

	bool unite(int n1, int n2) {
		int p1 = find(n1);
		int p2 = find(n2);
		if (p1 != p2) {
			if (setsize[p2] > setsize[p1])
				swap(p1, p2);
			setsize[p1] += setsize[p2];
			parent[p2] = p1;
			return true;
		}
		return false;
	}
};
