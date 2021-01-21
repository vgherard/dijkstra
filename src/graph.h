// A minimalist implementation of directed weighted graph

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stdexcept>
#include <unordered_map>

template <class weight_t>
class WeightedGraph {

	using AdjList = std::vector<std::unordered_map<size_t, weight_t> >;

	AdjList adj_;
public:
	// Construct a graph with n_vert disconnected vertexes
	WeightedGraph(size_t n_vert) : adj_(AdjList(n_vert)) {}

	size_t n_vertices () const { return adj_.size(); }

	// Return edges
	const std::unordered_map<size_t, weight_t> & edges (size_t start) const
		{ return adj_[start]; }

	// Add a new disconnected vertex
	void add_vertex ()
		{ adj_.push_back( std::unordered_map<size_t, weight_t>() ); }

	// Add a weighted edge edge connecting existing vertices
	void add_edge (size_t start, size_t end, weight_t weight)
	{
		if (start >= n_vertices() )
			throw std::domain_error("'start' is not a vertex.");
		if (end >= n_vertices() )
			throw std::domain_error("'end' is not a vertex.");

		adj_[start][end] = weight;
	}
}; // class WeightedGraph

#endif // GRAPH_H
