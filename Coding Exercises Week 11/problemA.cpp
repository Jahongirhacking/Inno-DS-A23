// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

template <typename V>
class Node {
public:
    Node(V val) {
        this->val = val;
    }
    // connect this node with
    void connect(Node* node) {
        childsList.push_back(node);
    }
    V val;
    vector<Node*> childsList;
    bool isVisited = false;
};

template <typename V>
void DFS(Node<V>* node, int &count) {
    node->isVisited = true;
    if(node->childsList.size() == 0) return;
    for(Node<V>* child : node->childsList) {
        if(!child->isVisited) {
            count++;
            DFS(child, count);
        }
    }
}

int main() {
    ll n;
    cin>>n;
    vector<Node<int>*> nodes;
    // create vector of nodes
    for(int i=0; i<n; i++) {
        nodes.push_back(new Node(i));
    }
    // store connection states
    vector<vector<ll>> connections(n, vector<ll>(n));
    rep(i, n) {
        rep(j, n) {
            cin>>connections[i][j];
            if(connections[i][j]==1) {
                // ith node with jth node
                nodes[i]->connect(nodes[j]);
            }
        }
    }
    // implement DFS search
    int count = 1;
    DFS(nodes[0], count);
    if(count==n) cout<<"YES";
    else cout<<"NO";
    return 0;
}
