/**
 * Tarjan's Bridge Finding Algorithm
 *
 * Algorithm Premise:
 * - Find bridges by creating a DFS Tree structure
 * - Start at some arbitrary node (0 in this case), and dfs
 * - Store the time at which each node was discovered (order them based on when found)
 * - Have low[current_node] store the lowest discovery time that can be reached
 *   by all nodes below it (also including itself)
 * - We can find this by:
 * 	- If an adjacent node has already been visited (not parent), and is thus in the DFS tree,
 * 	  it has to be a back-edge, and the lowest discovery time for our current node could be
 * 	  the discovery time of the adjacent node
 * 	- If it has not been visited, it is not a back edge. The lowest discovery time for our
 * 	  current node could be the lowest discovery time of this adjacent node
 * - If the discovery_time[node] < low[adjacent_node], we know the edge (node -> adjacent_node)
 *   must be a bridge. This is because no back edges were found at adjacent_node or below it
 *   that would have decreased low[adjacent_node] to equal the discovery time of a node above
 *   it in the DFS tree
 *
 * EXAMPLE USAGE:
 * Given a graph, output all of the bridges
 */

#include <bits/stdc++.h>
using namespace std;

#define ii array<int, 2>

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b; a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	set<ii> bridges;

	vector<bool> visited(n);		
	vector<int> discovery_time(n);  
	vector<int> low(n); 			
	int time = 0;				    

	auto dfs_find_bridges = [&](int node, int prev, auto&& self) -> void {
		visited[node] = true;
		discovery_time[node] = time;
		low[node] = time;
		time++;
		bool parent_skipped = false; // Necessary for cases where there are multiple of the same edge

		for (int next : adj[node]) {
			if (next == prev && !parent_skipped) {
				parent_skipped = true;
				continue;
			}
			if (visited[next]) {
				low[node] = min(low[node], discovery_time[next]);
			} else {
				self(next, node, self);
				low[node] = min(low[node], low[next]);
				if (low[next] > discovery_time[node]) {
					// BRIDGE!
					ii bridge = {node+1, next+1};
					sort(bridge.begin(), bridge.end());
					bridges.insert(bridge);
				}
			}
		}
	};

	dfs_find_bridges(0, -1, dfs_find_bridges);

	cout << "BRIDGES:\n";
	if (!bridges.empty()) {
		for (auto& bridge : bridges) {
			cout << bridge[0] << " " << bridge[1] << '\n';
		}
	} else {
		cout << "NONE\n";
	}
}

int main() {
	int t; cin >> t;
	while (t--) {
		solve();
	}
}
