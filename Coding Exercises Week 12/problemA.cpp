#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e18

template<typename S, typename P>
class Vertex {
public:
    Vertex(S name, P penalty) {
        this->name = name;
        this->penalty = penalty;
    }
    S name;
    P penalty;
};

class Edge {
public:
    Edge() = default;
    Edge(ll toCityIndex, double weight) {
        this->toCityIndex = toCityIndex;
        this->weight = weight;
    }
    ll toCityIndex;
    double weight;
};

template <class V, class E, typename S, typename P, typename D>
class UndirectedGraph {
public:
    UndirectedGraph() = default;
    void ADD(S name, P penalty) {
        if(getIndex.find(name) == getIndex.end()) {
            getIndex[name] = numberOfVertex++;
            this->vertices.emplace_back(new V(name, penalty));
        }
    }

    void CONNECT(S name1, S name2, D distance) {
        ll index1 = getIndex[name1];
        ll index2 = getIndex[name2];
        double weight = double(distance) / double(vertices[index1]->penalty + vertices[index2]->penalty);
        this->adj[index1].push_back(new E(index2, weight));
        this->adj[index2].push_back(new E(index1, weight));
    }

    void PRINT_MIN() {
        // TODO: PRIM'S ALGORITHM
        vector<double> costs(numberOfVertex, double(INF));
        vector<bool> processed(numberOfVertex, false);
        // start building from 0 index
        for(ll start=0; start < numberOfVertex; start++){
            if(processed[start]) continue;
            costs[start] = 0;
            this->PriorityQueue.push(make_pair(costs[start], make_pair(-1, start)));
            // Check its adjacent vertices
            while (!PriorityQueue.empty()) {
                pair<double, pair<ll, ll>> TOP = PriorityQueue.top();
                ll fromCityIndex = TOP.second.second;
                PriorityQueue.pop();
                if (processed[fromCityIndex]) continue;
                processed[fromCityIndex] = true;
                if (TOP.second.first != -1)
                    cout << vertices[TOP.second.first]->name
                         << ":" << vertices[TOP.second.second]->name << " ";
                for (auto toCity: adj[fromCityIndex]) {
                    ll toCityIndex = toCity->toCityIndex;
                    double weight = toCity->weight;
                    if (!processed[toCityIndex] && weight < costs[toCityIndex]) {
                        costs[toCityIndex] = weight;
                        PriorityQueue.push({-weight, make_pair(fromCityIndex, toCityIndex)});
                    }
                }
            }
        }
        cout<<endl;
    }

    priority_queue<pair<double,pair<ll,ll>>> PriorityQueue; // weight
    map<S, ll> getIndex; // name, index of vertex
    vector<V*> vertices; // name, penalty
    map<ll, vector<E*>> adj; // index, edge
    ll numberOfVertex = 0;
};

int main() {
    auto *graph = new UndirectedGraph<Vertex<string, ll>, Edge, string, ll, ll>();
    ll t;
    string operation, name1, name2;
    ll distance, penalty;
    cin >> t;
    while(t--) {
        cin >> operation;
        if(operation == "ADD") {
            cin >> name1 >> penalty;
            graph->ADD(name1, penalty);
        } else if(operation == "CONNECT") {
            cin >> name1 >> name2 >> distance;
            graph->CONNECT(name1, name2, distance);
        } else if(operation == "PRINT_MIN") {
            graph->PRINT_MIN();
        }
    }
    return 0;
}
