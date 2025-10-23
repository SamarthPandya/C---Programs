#include <iostream>
#include <thread>
#include<limits>

using namespace std;

/*

Problem
-------
Suppose that we are given a directed acyclic graph GD .V; E/ with real-
valued edge weights and two distinguished vertices s and t. Describe a dynamic-
programming approach for finding a longest weighted simple path from s to t.

Solution
--------
We initialise a DP vector where dp[i] denotes the max distance of node i from s
naturally, dp[s] = 0 initially and the rest of the values are -inf
relax the edges in topological order, For each node:
For each child of the given node, we relax the edge that joins it with the parent i.e.

if dp[parent] + edge weight > dp[child] then dp[child] = dp[parent] + edge weight

IMP: The solution for min path sum is analogous.
*/

const double neg_inf = numeric_limits<double>::infinity() * -1;

class Graph{
public:
vector<vector<pair<double, int>>>adj_list;
int V;
Graph(int _V) : V(_V) {adj_list = vector<vector<pair<double, int>>>(V);}
void addEdge(int u, int v, double w){
    adj_list[u].push_back({w, v});
}
};

void dfsHelper(int node, Graph &g, vector<int>&vis, vector<int>&res){
    vis[node] = true;
    for(auto child : g.adj_list[node]){
        if(!vis[child.second]){
            dfsHelper(child.second, g, vis, res);
        }
    }
    res.insert(res.begin(), node);
}

vector<int>topo_sort(Graph &g){
    int V = g.V;
    vector<int>vis(V, 0);
    vector<int>res;
    for(int i = 0; i < V; i++){
        if(!vis[i]){
            dfsHelper(i, g, vis, res);
        }
    }
    return res;
}

double get_max_weighted_path(int s, int t, Graph&g){
    int V = g.V;
    vector<double>dp(V, neg_inf);
    dp[s] = 0;
    vector<int>nodes = topo_sort(g);
    for(int i : nodes){
        for(auto child_node : g.adj_list[i]){
            dp[child_node.second] = max((double)dp[child_node.second], dp[i] + child_node.first);
        }
    }
    return dp[t];
}

int main(){
    Graph g = Graph(4);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, -2);
    g.addEdge(2, 3, 5.54);
    cout << get_max_weighted_path(0, 3, g);
}