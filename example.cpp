#include <iostream>
#include "src/dijkstra.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	WeightedGraph<long long> g(n);
	for (int i = 0; i < m; i++) {
		size_t x, y;
		long long w;
		std::cin >> x >> y >> w;
		g.add_edge(x - 1, y - 1, w);
	}
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(g, s, t);
}
