// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define INF 1e18

template <typename W, typename I>
class PriorityQueueMIN {
public:
    PriorityQueueMIN() = default;
    void push(pair<W, pair<I, I>> length) {
        this->arr.push_back(length);
        this->size++;
        // keep track of the last added element
        ll index = this->size-1;
        while(index-1>=0 && this->arr[(index-1)/2].first > this->arr[index].first) {
            swap(this->arr[(index-1)/2], this->arr[index]);
            index = (index-1)/2;
        }
    }

    void pop() {
        swap(arr[0], arr[this->size-1]);
        this->arr.pop_back();
        this->size--;
        // keep track of the new first element
        ll index = 0;
        // repeat until there is no child
        while(index*2+1 < this->size) {
            ll left = index*2+1, right = index*2+2;
            bool flag = false;
            // if both children exist
            if(right < this->size) {
                // if the right child is less than the left
                if(arr[right].first < arr[left].first) {
                    if(arr[right] < arr[index]) {
                        swap(arr[right], arr[index]);
                        index = right;
                        flag = true;
                    } else return;
                }
            } 
            if(flag) continue;
            // if the left child is less than or equal the right
            if(arr[left] < arr[index]) {
                swap(arr[left], arr[index]);
                index = left;
            } else return;
        }
    }

    bool empty() {
        if(this->size == 0) return true;
        return false;
    }

    pair<W, pair<I, I>> top() {
        return this->arr[0];
    }
    
    vector<pair<W, pair<I, I>>> arr;
    ll size = 0;
};

template<typename V, typename D>
class Vertex {
public:
    Vertex(V index) {
        this->index = index;
    }
    V index;
    vector<pair<D, V>> adj;
};

template<typename V, typename D>
class Edge {
public:
    Edge(Vertex<V, D>* src, Vertex<V, D>* destination, D distance) {
        this->src = src;
        this->destination = destination;
        this->distance = distance;
    }
    Vertex<V, D>* src;
    Vertex<V, D>* destination;
    D distance;
};

template <typename V, typename D>
class Graph {
public:
    Graph() = default;
    void add(V index) {
        this->vertices.push_back(new Vertex<V, D>(index));
    }

    void connect(V i, V j, D distance, D bandWidth) {
        Vertex<V, D>* src = vertices[i];
        Vertex<V, D>* destination = vertices[j];
        // push dest. vertex to the adjacency list
        src->adj.push_back({distance, j});
        // push the edge to the edges
        this->edges.push_back(new Edge<V, D>(src, destination, distance));
        checkBandWidth[{i, j}] = bandWidth;
    }

    void find(V src, V target) {
        // TODO: DIJKSTRA'S ALGORITHM
        ll n = vertices.size();
        // Distances from source vertex
        vector<ll> dist(n, INF);
        // Store every vertex's parent 
        vector<ll> parent(n, -1);
        // check if it's reachable from source to the target vertex
        bool isReachable = false;
        // check visited or not
        set<ll> visited;
        // distance from source vertex itself is 0 
        dist[src] = 0;
        // store path
        vector<V> path;
        
        // distance, <vertex1 & vertex2>
        priorityQueue->push({dist[src], {-1, src}});
        while(!priorityQueue->empty()) {
            // temporary Vertex
            V temp = priorityQueue->top().second.second;
            priorityQueue->pop();
            // check if it was visited or not
            if(visited.count(temp)) continue;
            visited.insert(temp);
            // check its adjacent vertices
            for(pair<D, V> edge : vertices[temp]->adj) {
                ll distance = edge.first;
                ll destination = edge.second;
                // check another short path existance
                if(dist[temp]+distance < dist[destination]) {
                    // If there is a path between source and target we should mark it 
                    if(destination == target) isReachable = true;
                    // updating process
                    dist[destination] = dist[temp]+distance;
                    parent[destination] = temp;
                    priorityQueue->push({dist[destination], {temp, destination}});
                }
            }
        }
        
        if(isReachable) {
            // find path and bandWidth
            ll minBandWidth = INF;
            ll temp = target;
            path.push_back(temp);
            // we are in the target vertex
            // TODO: Backtracking until we get src
            while(temp != src) {
                minBandWidth = min(minBandWidth, checkBandWidth[{parent[temp], temp}]);
                temp = parent[temp];
                path.push_back(temp);
            }
            // reverse the path to start from src
            reverse(path.begin(), path.end());
            cout << path.size() << " " << dist[target] << " " << minBandWidth << endl;
            for(ll v : path) cout<<v+1<<" ";
        } else cout<<"IMPOSSIBLE";
        
        return;
    }

    PriorityQueueMIN<D, V> *priorityQueue = new PriorityQueueMIN<D, V>();
    vector<Vertex<V, D>*> vertices; // Vertex
    vector<Edge<V, D>*> edges; // Edges
    map<pair<V, V>, D> checkBandWidth; // find the corresponding bandwidth
};

int main() {
    auto *graph = new Graph<ll, ll>();
    ll n, m, from, to, bandwidth;
    cin >> n >> m;
    struct edge {
        ll i, j, l, b;
    };
    edge init;
    vector<edge> edges(m, init);
    
    rep(i, m) {
        cin>>edges[i].i>>edges[i].j>>edges[i].l>>edges[i].b;
    }
    cin >> from >> to >> bandwidth;
    
    // Create Vertices
    rep(i, n) graph->add(i);
    // Create edges
    for(auto e : edges) {
        if(e.b < bandwidth) continue;
        graph->connect(e.i-1, e.j-1, e.l, e.b);
    }
    
    graph->find(from-1, to-1);
    
    return 0;
}
