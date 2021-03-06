/*
 * graph.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: qamar-ud-din
 */
#include "graph.h"

Graph::Graph() {
	N = M = 0;
	this->read("SCC.txt");
//	this->read("graph.in");
//	this->read("test_case_1.in");
//	this->read("test_case_2.in");
//	this->read("test_case_3.in");
//	this->read("test_case_4.in");
//	this->read("test_case_5.in");
//	this->read("test_case_6.in");
//	this->read("test_case_7.in");
//	this->read("test_case_8.in");
//	this->read("test_case_9.in");
//	this->read("test_case_10.in");
//	this->read("test_case_11.in");
//	this->read("test_case_12.in");
//	this->read("test_case_13.in");
//	this->read("test_case_14.in");
	this->init();
//	this->display(dir_graph);
//	this->display(rev_graph);
	this->kosaraju();
}

void Graph::read(string infile) {
	fstream fs;
	fs.open(infile.c_str(), fstream::in);
	int u, v; // E:U->V
	while (fs >> u >> v) {
		gitr itr_u = find_vertex(dir_graph, u, true);
		gitr itr_v = find_vertex(dir_graph, v, true);
		(*itr_u).second.push_back(v);

		itr_u = find_vertex(rev_graph, u);
		itr_v = find_vertex(rev_graph, v);
		(*itr_v).second.push_back(u);

		M = M + 1; // Inc |E|
	}
}

void Graph::display(G& g) {
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	cout << "N := |V| = " << setw(15) << N << endl;
	cout << "M := |E| = " << setw(15) << M << endl;
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	for (int i = 1; i <= N; i++) {
		cout << "U:" << setw(15) << i << endl;
		for (vi::size_type j = 0; j < g[i].size(); j++) {
			cout << setw(15) << g[i][j];
		}
		cout << endl << endl;
	}
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
}

void Graph::display_mp_ii(mp_ii& m) {
	const int max_count = 5;
	int max[max_count] = { 0, 0, 0, 0, 0 };
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	for (int i = 1; i <= N; i++) {
//		if (m[i] < 59)
//			continue;
		cout << "LEADER:" << setw(15) << i << endl;
		cout << "SCC SIZE:" << setw(15) << m[i];
		for (int j = max_count - 1; j >= 0; j--) {

			if (m[i] >= max[j]) {
				for (int k = 0; k < j; k++) {
					max[k] = max[k + 1];
				}
				max[j] = m[i];
				break;
			}
		}

		cout << endl << endl;
	}
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	for (int j = 0; j < max_count; j++) {
		cout << "SCC MAX SZ:" << setw(10) << max[j] << endl;
	}
}

void print_vi(vi in) {
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	for (vi::size_type i = 0; i < in.size(); i++) {
		cout << setw(5) << i << setw(5) << in[i] << endl;
	}
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
}

void print_vb(vb in) {
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
	for (vi::size_type i = 0; i < in.size(); i++) {
		cout << setw(5) << i << setw(5) << boolalpha << in[i] << endl;
	}
	cout << setfill('X') << setw(20) << 'X' << setfill(' ') << endl;
}

/**
 * precondition: N := |V| is already set
 */
void Graph::init() {
	vis.resize(N + 1); // labels start from 1
	fill(vis.begin(), vis.end(), false); // initially all nodes unexplored

//	time_fn.resize(N + 1); // labels start from 1
//	fill(time_fn.begin(), time_fn.end(), -1); // initially all nodes unexplored
}

gitr Graph::find_vertex(G& g, int label, bool inc) {
	gitr itr_l = g.find(label); // O(lgN)
	if (itr_l == g.end()) {
		vi new_adj_list;
		pr_itr_bl ret_pair = g.insert(make_pair(label, new_adj_list)); // O(lgN)
		itr_l = ret_pair.first;
		if (inc)
			N = N + 1; // Inc |V|
	}
	return itr_l;
}

gitr Graph::insert_vertex(G& g, int label, bool inc) {
	gitr itr_l = g.find(label); // O(lgN)
	if (itr_l == g.end()) {
		vi new_adj_list;
		pr_itr_bl ret_pair = g.insert(make_pair(label, new_adj_list)); // O(lgN)
		itr_l = ret_pair.first;
		if (inc)
			N = N + 1; // Inc |V|
	}
	return itr_l;
}

//1  procedure DFS(G,v):
//2      label v as discovered
//3      for all edges from v to w in G.adjacentEdges(v) do
//4          if vertex w is not labeled as discovered then
//5              recursively call DFS(G,w)
void Graph::dfs(G& g, int v, bool first) {
	vis[v] = true;
	if (!first) {
		ldr_grp[cur_ldr_lbl].push_back(v);
		ldr_grp_cnts[cur_ldr_lbl] = ldr_grp_cnts[cur_ldr_lbl] + 1;
	}
	for (vi::size_type j = 0; j < g[v].size(); j++) {
		int w = g[v][j];
		if (!vis[w]) {
			cout << "(V->W)" << setw(15) << v << setw(15) << w << endl;
			Graph::dfs(g, w, first);
		}
	}
	cur_time_order = cur_time_order + 1;
//	time_fn[v] = cur_time_order;
	if (first) {
		time_pq.push(make_pair(cur_time_order, v));
	}
}

void Graph::dfs_loop(G& g, bool first) {
	for (int i = N; i > 0; i--) {
		cout << i << endl;
		cout << boolalpha << vis[i] << endl;
		if (!vis[i]) {
			if (!first) {
				cur_ldr_lbl = i;
			}
			dfs(g, i, first);
		}
	}
}

void Graph::dfs_loop_pq(G& g, bool first) {

	while (!time_pq.empty()) {
		pii mx = time_pq.top();
		time_pq.pop();
		cout << "MAX:" << setw(10) << mx.first << setw(10);
		cout << "INDEX:" << setw(10) << mx.second;
		cout << endl;
		int i = mx.second;
		cout << i << endl;
		cout << boolalpha << vis[i] << endl;
		if (!vis[i]) {
			cur_ldr_lbl = i;
			dfs(g, i, first);
		}
	}
}

/**
 * Kosaraju's algorithm works as follows:
 Let G be a directed graph and S be an empty stack.
 While S does not contain all vertices:
 // Choose an arbitrary vertex v not in S.
 // Perform a depth-first search starting at v.
 // Each time that depth-first search finishes expanding a vertex u, push u onto S.
 Reverse the directions of all arcs to obtain the transpose graph.
 While S is nonempty:
 // Pop the top vertex v from S.
 // Perform a depth-first search starting at v in the transpose graph.
 // The set of visited vertices will give the strongly connected component containing v;
 // record this and remove all these vertices from the graph G and the stack S.
 // Equivalently, breadth-first search (BFS) can be used instead of depth-first search.
 */
void Graph::kosaraju() {
	cur_time_order = 0;
	dfs_loop(rev_graph, true);
//	print_vi (time_fn);

	fill(vis.begin(), vis.end(), false); // reset all nodes unexplored
//	ldr_grp.clear(); // clear leaders

	// exchange labels with the calculated time order function

	cur_ldr_lbl = -1;
	dfs_loop_pq(dir_graph, false);
	//display(ldr_grp);
	display_mp_ii(ldr_grp_cnts);
	cout << "TERMINATED!" << endl;
}
