#include <vector>
#include <iostream>

using namespace std;

int neg_inf = numeric_limits<int>::infinity() * -1;

class Node
{
public:
    string name;
    int rating;
    vector<Node*>children;
    Node(string _name, int _rating) : name(_name), rating(_rating) {}
};

class Graph{
    public:
    Node *head;
    void addNode(Node *parent, Node *child){
        parent->children.push_back(child);
    }
};

struct ResultNode{
    int max_incl;
    int max_excl;
};

ResultNode helper(Node *node, Graph&g, unordered_map<Node*, ResultNode>&dp){
    if(node == nullptr){
        return {0, 0};
    }
    else if(dp.count(node)){
        return dp[node];
    }
    else{

        // precumpute the result for all children
        vector<ResultNode>childResults;
        for(auto child : node->children){
            childResults.push_back(helper(child, g, dp));
        }

        int max_incl_val = node->rating;
        for(auto res : childResults){
            max_incl_val += res.max_excl;
        }

        int max_excl_val = 0;
        for(auto res : childResults){
            max_excl_val += max(res.max_excl, res.max_incl);
        }

        ResultNode ans = {max_incl_val, max_excl_val};
        return ans;
    }
}


int main(){
    Graph g;
    Node* n1 = new Node("g1", 18), *n2 = new Node("g2", 2), *n3 = new Node("g3", 5);
    g.head  = n1;
    g.addNode(n1, n2);
    g.addNode(n1, n3);
    unordered_map<Node*, ResultNode>dp;
    auto res = helper(n1, g, dp);
    cout << res.max_excl << " " << res.max_incl;
}