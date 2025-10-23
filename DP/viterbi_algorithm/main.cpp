#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Graph{
    public:
    int V;
    vector<vector<pair<int, string>>>adj_list; // adj_list[u] contains (v, s) => edge u->v makes a sound s
    Graph(int V){
        this->V = V;
        adj_list = vector<vector<pair<int, string>>>(V);
    }
    void addEdge(int u, int v, string s){
        this->adj_list[u].push_back({v, s});
    }
};

bool search_helper(int node, vector<string>&sounds, int word_ind, Graph &g){
    if(word_ind >= sounds.size()){
        return true;
    }
    string currSound = sounds[word_ind];
    for(auto child : g.adj_list[node]){
        bool temp = true;
        if(child.second == currSound){
            temp = temp && search_helper(child.first, sounds, word_ind + 1, g);
            if(temp == true){
                return true;
            }
        }
    }
    return false;
}

bool search(int node, vector<string>sounds, Graph &g){
    return search_helper(node, sounds, 0, g);
}

int main(){
    Graph g(5);
    g.addEdge(0, 1, "hello,");
    g.addEdge(0, 1, "hi,");
    g.addEdge(1, 2, "how");
    g.addEdge(2, 3, "are");
    g.addEdge(3, 4, "you");
    vector<string>s = {"hello,", "how", "ar", "you"};
    cout << search(0, s, g);
}

