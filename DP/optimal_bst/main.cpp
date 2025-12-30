#include <vector>
#include <iostream>

using namespace std;

/*
State space
===========
S = {(i, j) | 1 <= i <= n, i - 1 <= j <= n}
(i, j) represents the set {ki....kj} U {d_(i - 1).....d_j}

1.	e(i, j) denotes the expected search cost of the optimal subtree with state (i, j)

2.	-	w(i, j) denotes the surplus search cost incurred when the optimal subtree
        is appended to a root node.
    -	w(i, j) = (pi + .. + pj) + (q_(i - 1) + .. q(j))

3.	-	root(i, j) denotes the root of the optimal subtree for (i, j).
    -	root nodes can only be amoung the ki's and not the dummy nodes.

Base states
===========
Base states = {(i, i - 1) | 1 <= i <= n + 1}
(i, i - 1) is the set {d_(i - 1)}
e(i, i - 1) = q_(i - 1) since there is only one node so, (0 + 1) * (q_(i - 1)) = q_(i - 1)
w(i, i - 1) = q_(i - 1)
root(i, i - 1) = null since there should not be any root to this empty subtree.

Recursion
=========
given (i, j):
we precompute w(i, j) = w(i, j - 1) + p(j - 1) + q(j);
and then for each r such that i <= r <= j
- we have to make kr the root node
- put ki..k_(r-1) to the left.
- put k_(r + 1)..kj to the right subtree.
- calcuate expected cost in each shape and update e(i, j) = min(e(i, j), curr exp cost).
  Also update the root to kr.

so assume r is what results in the optimal subtree:
e(i, j) = pr + e(i, r - 1) + w(i, r - 1) + e(r + 1, j) + w(r + 1, j)
now since w(i, r - 1) + pr + w(r + 1, j) = w(i, j) we get:
e(i, j) = e(i, r - 1) + e(r + 1, j) + w(i, j)
*/

class Node
{
public:
    string val;
    Node *left, *right;
};

Node *build(int i, int j, vector<vector<int>> &roots, vector<string> &keys)
{
    if (j < i)
    {
        return nullptr;
    }
    else
    {
        Node *curr = new Node();
        int r = roots[i][j];
        curr->val = keys[r - 1];
        curr->left = build(i, r - 1, roots, keys);
        curr->right = build(r + 1, j, roots, keys);
        return curr;
    }
}

void show(Node *node)
{
    if (node)
    {
        cout << node->val << ' ';
        show(node->left);
        show(node->right);
    }
}

double bottom_up(vector<double> p, vector<double> q, vector<string> keys, Node *&root)
{

    // input validation
    if (p.size() != keys.size() || q.size() != p.size() + 1)
    {
        cout << "\ninput validation failure\n";
        return -1;
    }

    else
    {

        // initialise dp tables
        int n = keys.size();
        vector<vector<double>> e(n + 2, vector<double>(n + 2, 0)), w(n + 2, vector<double>(n + 2, 0));
        vector<vector<int>> roots(n + 2, vector<int>(n + 2, -1));

        // base states
        for (int i = 1; i <= n + 1; i++)
        {
            e[i][i - 1] = q[i - 1];
            w[i][i - 1] = q[i - 1];
        }

        // recursion
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n - k + 1; i++)
            {
                int j = i + k - 1;

                // calculating e(i, j), w(i, j) and r(i, j)
                double temp = 1e9;
                w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
                for (int r = i; r <= j; r++)
                {
                    double curr = e[i][r - 1] + e[r + 1][j] + w[i][j];
                    if (curr < temp)
                    {
                        temp = curr;
                        roots[i][j] = r;
                    }
                }

                e[i][j] = temp;
            }
        }

        root = build(1, n, roots, keys);

        return e[1][n];
    }
}

int main()
{
    vector<string> keys = {"about", "ask", "did", "what", "you"};
    vector<double>
        p = {0.15, 0.10, 0.05, 0.10, 0.20},
        q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    Node *root;
    cout << bottom_up(p, q, keys, root) << endl;
    show(root);
    return 0;
}