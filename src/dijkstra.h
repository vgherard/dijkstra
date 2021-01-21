#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <queue>
#include <unordered_set>
#include <limits>

const long long INFTY = 1e+15;
const int NULL_VTX = -1;

template <class weight_t>
struct CompareBy {
	const std::vector<weight_t> & dist;
	CompareBy (const std::vector<weight_t> & dist_) : dist(dist_) {}
	bool operator() (const size_t & l, const size_t & r) const
		{ return dist[l] > dist[r]; };
};

// Light wrapper class around std::unordered_set<size_t>
class IndexSet {
	std::unordered_set<size_t> set_;
	std::unordered_set<size_t>::iterator end_;
public:
	IndexSet () : set_(std::unordered_set<size_t>()), end_(set_.end()) {}
	void insert (size_t i) { set_.insert(i); end_ = set_.end(); }
	bool operator() (size_t i) const { return set_.find(i) != end_; }
};

template <class weight_t>
weight_t distance(const WeightedGraph<weight_t> &g, size_t start, size_t end) {
	weight_t INFTY = std::numeric_limits<weight_t>::max();
	size_t n_vert = g.n_vertices();

	std::vector<weight_t> dist(n_vert, INFTY);
	std::vector<size_t> prev(n_vert, NULL_VTX);
	dist[start] = 0;

	CompareBy<weight_t> cmp(dist);
	std::priority_queue<size_t, std::vector<size_t>, decltype(cmp)> H(cmp);
	for (int i = 0; i < n_vert; i++)
		H.push(i);

	IndexSet processed;
	while (not H.empty()) {
		size_t u = H.top();
		H.pop();
		if (u == end)
			break;
		if (processed(u))
			continue;
		processed.insert(u);
		if (dist[u] == INFTY)
			continue;
		for (const auto & e : g.edges(u)) { // e ~ {vertex v, weight of u->v}
			size_t v = e.first;
			weight_t weight_uv = e.second;
			weight_t new_dist_v = dist[u] + weight_uv;
			if (dist[v] > new_dist_v) {
				dist[v] = new_dist_v;
				prev[v] = u;
				H.push(v);
			}
		}
	}

	if (dist[end] < INFTY)
		return dist[end];
	else
		return -1;
}


#endif // DIJKSTRA_H
