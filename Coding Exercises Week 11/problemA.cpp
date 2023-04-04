// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

template <typename V>
class Graph {
public:
    // constructor
    Graph() {}
    
    // Add the vertex to the graph field
    void addVertex(V vertex) {
        this->vertices.push_back(vertex);
    }
    
    // get the vertex
    V getVertex(int index) {
        return this->vertices[index];
    }
    
private:
    // array of vertices in the graph
    vector<V> vertices;
};

template <typename V>
class Vertex {
public:
    // constructor
    Vertex(V val) {
        this->val = val;
    }
    
    // connect this node with
    void connect(Vertex* node) {
        this->childrenList.push_back(node);
    }
    
    // get lists of children's info
    vector<Vertex*> getChildren() {
        return this->childrenList;
    }
    
    bool getIsVisited() {
        return this->isVisited;
    }
    
    void makeVisited() {
        this->isVisited = true;
    }
    
private:
    V val;
    // To track which vertices are the children
    vector<Vertex*> childrenList;
    // check if already visited
    bool isVisited = false;
};

template <typename V>
void DFS(Vertex<V>* vertex, int &count) {
    // Make the vertex visited
    vertex->makeVisited();
    // If has no children backtracking
    if(vertex->getChildren().size() == 0) return;
    // else iterate through every children which is not visited
    // and implement DFS search for this children and also count the children
    for(Vertex<V>* child : vertex->getChildren()) {
        if(!child->getIsVisited()) {
            count++;
            DFS(child, count);
        }
    }
}

int main() {
    ll n;
    cin>>n;
    Graph<Vertex<int>*>* graph = new Graph<Vertex<int>*>();
    // create Graph which includes vertices
    for(int i=0; i<n; i++) {
        graph->addVertex(new Vertex(i));
    }
    // store connection states of vertices
    vector<vector<ll>> connections(n, vector<ll>(n));
    rep(i, n) {
        rep(j, n) {
            cin>>connections[i][j];
            if(connections[i][j]==1) {
                // connect ith vertex with jth vertex
                graph->getVertex(i)->connect(graph->getVertex(j));
            }
        }
    }
    // implement DFS search
    int count = 1;
    DFS(graph->getVertex(0), count);
    // Output
    if(count==n) cout<<"YES";
    else cout<<"NO";
    return 0;
}
