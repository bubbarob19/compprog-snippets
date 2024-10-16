struct LCAHelper {
	int n, lg;
	vector<int> par;
	vector<int> depth;
	vector<vector<int>> adj;
	vector<vector<int>> blift;

	/**
	 * Build from adjacency list.
	 */
	LCAHelper(vector<vector<int>>& adj) : adj(adj) {
		n = adj.size();
		lg = 31 - __builtin_clz(n);
		par = vector<int>(n);
		depth = vector<int>(n);
		dfs_build(0, -1, 0);
		build_blift();
	}

	/**
	 * Build from parent array. Assuming par[0] = -1;
	 */
	LCAHelper(vector<int>& par) : par(par) {
		int n = par.size();
		depth = vector<int>(n);
		lg = 31 - __builtin_clz(n);
		adj = vector<vector<int>>(n);
		for (int i = 1; i < n; i++) {
			adj[i].push_back(par[i]);
			adj[par[i]].push_back(i);
			depth[i] = depth[par[i]];  
		}
		build_blift();
	}

	int kth_parent(int node, int k) {
		for (int l = 0; l <= lg; l++) {
			if (!(k & (1 << l)))
				continue;
			node = blift[node][l];
			if (node == -1)
				break;
		}
		return node;
	}

	int lca(int a, int b) {
		if (depth[a] < depth[b])
			swap(a, b);
		a = kth_parent(a, depth[a] - depth[b]);
		if (a == b)
			return a;
		for (int l = lg; l >= 0; l--)
			if (blift[a][l] != blift[b][l])
				a = blift[a][l], b = blift[b][l];
		return par[a];
	}

	void dfs_build(int node, int prev, int dep) {
		par[node] = prev;
		depth[node] = dep;
		for (int next : adj[node])
			if (next != prev)
				dfs_build(next, node, dep + 1);
	}

	void build_blift() {
		blift = vector<vector<int>>(n, vector<int>(lg + 1));
		for (int i = 0; i < n; i++)
			blift[i][0] = par[i];
		for (int l = 1; l <= lg; l++) {
			for (int i = 0; i < n; i++) {
				int ans = blift[i][l-1];
				if (ans != -1)
					ans = blift[ans][l-1];
				blift[i][l] = ans;
			}
		}
	}
};

// Not really a data structure persay, but removes a lot of the boilerplate for LCA
