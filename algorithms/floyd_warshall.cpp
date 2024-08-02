/**
 * Floyd-Warshall Algorithm
 * 
 * Algorithm Premise:
 * - We can build up our shortest distances by increasing the set of nodes that we use,
 *   as we know that when we introduce a new node, the shortest path between any nodes
 *   will either remain the same or decrease in length
 * - We can achieve this by looping through N transition states, k, and then for each
 *   pair of nodes (i, j), see if the distance between nodes i & k + j & k < i & j. If
 *   so update our distance array.
 * - Complexity: O(V^3)
 * 
 * EXAMPLE USAGE:
 * Given a graph and weighted edges, output the shortest distance between
 * nodes given from q queries
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

constexpr ll INF = 1e18;

void solve() {
	int n, m, q; cin >> n >> m >> q;
	vector<vector<ll>> dist(n, vector<ll>(n, INF));
	for (int i = 0; i < m; i++) {
		ll a, b, c; cin >> a >> b >> c; a--; b--;
		dist[a][b] = min(dist[a][b], c);
		dist[b][a] = min(dist[b][a], c);
	}

	for (int i = 0; i < n; i++)
		dist[i][i] = 0;

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b; a--; b--;
		cout << (dist[a][b] != INF ? dist[a][b] : -1) << '\n';
	}
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int t = 1;
	while (t--) {
		solve();
	}
}
