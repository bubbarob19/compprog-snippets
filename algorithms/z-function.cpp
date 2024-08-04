/**
 * Z-Function
 * 
 * Premise:
 * - z[i] stores the maximum length of string prefix starting at 0 that
 *   coincides with the string prefix starting at i
 * - This is the efficient implementation of the algorithm that stores
 *   the farthest processed substring. We can use the fact that if i < r 
 *   (where r = exclusive right bound of substring above), sub[0, r-l) = sub[l, r)
 *   to get a "headstart" on our processing and start at a minimum value,
 *   greatly speeding up the process.
 */
vector<int> z_function(string s) {
	int n = s.size(), l = 0, r = 0;
	vector<int> z(n);
	for (int i = 1; i < n; i++) {
		if (i < r)
			z[i] = min(r-i, z[i-l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
