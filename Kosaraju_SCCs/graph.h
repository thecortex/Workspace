/*
 * graph.h
 *
 *  Created on: Nov 13, 2014
 *      Author: qamar-ud-din
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef map<int, vi> G;
typedef vector<bool> vb;
typedef long long int ll;
typedef unsigned long long int ull;
typedef G::iterator gitr;
typedef pair<gitr, bool> pr_itr_bl;
typedef pair<int, int> pii;
typedef priority_queue<pii> pq;
typedef map<int, int> mp_ii;

class Graph {
public:
	Graph();
	void read(string);
	void dfs(G&, int, bool);
	void dfs_loop(G&, bool);
	void dfs_loop_pq(G&, bool);
	void kosaraju();
	void output();
	void display(G&);
	void display_mp_ii(mp_ii&);
	void init();
	gitr find_vertex(G&, int, bool = false);
	gitr insert_vertex(G&, int, bool = false);
private:
	G dir_graph;
	G rev_graph;
	//vi time_fn; // Kosaraju's time order
	pq time_pq; // Kosaraju's time order
	int cur_time_order;
	G ldr_grp; // Kosaraju's leader vertex
	mp_ii ldr_grp_cnts; // SCCs' sizes
	int cur_ldr_lbl;
	vb vis;
	ll N; // |V|
	ll M; // |E|
};

#endif /* GRAPH_H_ */
