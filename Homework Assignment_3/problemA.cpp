// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define INF 1e18

template<typename V>
class Vertex {
public:
    Vertex(V index) {
        this->index = index;
    }
    V index;
    vector<Vertex<V>*> adj;
};

template<typename V, typename D>
class Edge {
public:
    Edge(Vertex<V>* src, Vertex<V>* destination, D distance) {
        this->src = src;
        this->destination = destination;
        this->distance = distance;
    }
    Vertex<V>* src;
    Vertex<V>* destination;
    D distance;
};

template <typename V, typename D>
class Graph {
public:
    Graph() = default;
    void add(V index) {
        this->vertices.push_back(new Vertex<V>(index));
    }

    void connect(V i, V j, D distance) {
        Vertex<V>* src = vertices[i];
        Vertex<V>* destination = vertices[j];
        // push dest. vertex to the adjacency list
        src->adj.push_back(destination);
        // push the edge to the edges
        this->edges.push_back(new Edge<V, D>(src, destination, distance));

    }

    bool negativeCycleFinder(V sourceVertex) {
        // TODO: BELLMAN FORD'S ALGORITHM
        // number of vertices of the graph
        int n  = vertices.size();

        // TODO: Create vectors to store visited, the parent , and distances of vertices
        map<ll, bool> visited;
        vector<V> parent(n, -1);
        vector<D> dist(n, INF);

        // make the distance of the source vertex = 0
        dist[sourceVertex] = 0;
        visited[sourceVertex] = false;

        bool isChanged  = true;
        ll lastChangedIndex = -1;
        
        // |V| - 1 times
        for (int i = 0; i < n ; i++) {
            if(!isChanged) break;
            // keep track of changes
            isChanged=false;
            // Iterate through all edges in the graph
            for (int j = 0; j < edges.size(); j++)
            {
                // Get the source vertex, destination vertex, and weight of the edge
                Vertex<V>* u = this->edges[j]->src;
                Vertex<V>* v = this->edges[j]->destination;
                D distance = this->edges[j]->distance;

                // check if there is near vertex than the current vertex
                if (dist[u->index] != INF && dist[u->index] + distance < dist[v->index])
                {
                    // We find near path so update distance and other info
                    isChanged = true;
                    visited[v->index] = true;
                    dist[v->index] = dist[u->index] + distance;
                    parent[v->index] = u->index;
                    lastChangedIndex = v->index;
                }
            }
        }

        set<ll> cycleElem;
        // store the vertices in the negative cycle
        vector<V> cycleVertices;
        
        if(isChanged) {
            ll temp = lastChangedIndex;
            
            // find base parent
            for (int i = 0; i < n; i++) temp = parent[temp];

            // Store the vertices in the negative weight cycle
            for(V vertex = temp; true; vertex = parent[vertex]) {
                if (vertex == temp && cycleVertices.size() >= 1) {
                    break;
                }
                cycleVertices.push_back(vertex);

            }
            
            reverse(cycleVertices.begin(), cycleVertices.end());
            cout<<"YES\n"<<cycleVertices.size()<<endl;
            for(ll i : cycleVertices) cout<<i+1<<" ";
            return true;
        }
        return false;
    }

    vector<Vertex<V>*> vertices; // Vertex
    vector<Edge<V, D>*> edges; // Edges
};

int main() {
    auto *graph = new Graph<ll, ll>();
    ll n;
    ll distance;
    cin >> n;
    rep(i, n) graph->add(i);
    for(ll i=0; i<n; i++) {
        for(ll j=0; j<n; j++) {
            cin >> distance;
            // check if self negative loop exists
            if(i==j && distance<0) {
                cout << "YES\n1\n"<<i+1;
                return 0;
            } else {
                // if distance=100000 there is no edge
                if(distance != 100000) graph->connect(i, j, distance);
            }
        }
    }

    bool res = false;
    rep(i, n) {
        res |= graph->negativeCycleFinder(i);
        if(res) return 0;
    }
    cout << "NO";
    return 0;
}
