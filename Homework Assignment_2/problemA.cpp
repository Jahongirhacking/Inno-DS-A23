// Jahongir Hayitov CS-01
#include<bits/stdc++.h>
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define FOR(i,a,b) for(ll i = a; i < ll(b); i++)
typedef long long int ll;
using namespace std;

// Structure to represent a point
struct Point {
    ll x, y;
};

// Structure to represent a segment
struct Segment {
    Point p1, p2;
};

// Check point p lies on line segment 'AB' point1=a point2=b
bool isPointOnSegment(Point a, Point p, Point b) {
    if (p.y <= max(a.y, b.y) && p.y >= min(a.y, b.y) &&
        p.x <= max(a.x, b.x) && p.x >= min(a.x, b.x))
        return true;
    return false;
}

// Find the property by their slopes
ll direction(Point p, Point q, Point r) {
    ll val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear
    if(val > 0) return 1; // clockwise
    else return 2; // counter-clockwise
}

// Check two lines are intersected or not
bool doIntersect(Segment* s1, Segment* s2) {
    Point p1 = s1->p1, p2 = s1->p2;
    Point q1 = s2->p1, q2 = s2->p2;

    // Find the four orientations needed for general and special cases
    ll d1 = direction(p1, p2, q1);
    ll d2 = direction(p1, p2, q2);
    ll d3 = direction(q1, q2, p1);
    ll d4 = direction(q1, q2, p2);

    // General case
    if (d1 != d2 && d3 != d4)
        return true;

    // Cases
    // p1, q1 and p2 are collinear and q1 lies on segment p1p2
    if (d1 == 0 && isPointOnSegment(p1, q1, p2)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1p2
    if (d2 == 0 && isPointOnSegment(p1, q2, p2)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment q1q2
    if (d3 == 0 && isPointOnSegment(q1, p1, q2)) return true;

    // p2, q2 and q1 are collinear and p2 lies on segment q1q2
    if (d4 == 0 && isPointOnSegment(q1, p2, q2)) return true;

    return false;
}

// Merge two array into one sorted array
template<typename T>
vector<T> merge(vector<T> a, vector<T> b) {
    vector<T> res;
    ll index_a = 0, index_b = 0;
    while(index_a < a.size() || index_b < b.size()) {
        if(index_b >= b.size() || (index_a < a.size() && a[index_a]->p1.x <= b[index_b]->p1.x)) {
            res.push_back(a[index_a++]);
        } else {
            res.push_back(b[index_b++]);
        }
    }
    return res;
}

// Time Complexity: O(n*log(n)) and stable
template<typename T>
vector<T> mergeSort(vector<T> segments) {
    ll n = segments.size();
    // just one elem
    if(n<=1) return segments;
    vector<T> left, right;
    // left and right arrays to divide
    rep(i, n/2) left.push_back(segments[i]);
    FOR(i, n/2, n) right.push_back(segments[i]);
    // a = {7, 4, 8, 3, 6, 5, 1}
    // left = {7, 4, 8}
    // right = {3, 6, 5, 1}
    left = mergeSort(left);
    right = mergeSort(right);
    // merge({4, 7}, {1, 6})
    // result = {1, 4, 6, 7}
    return merge(left, right);
}

template <typename T>
class Node {
public:
    T key;
    ll height;
    Node* left;
    Node* right;

    Node(T key) {
        this->key = key;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class AVLTree {
public:
    Node<T>* root;

    AVLTree() {
        this->root = nullptr;
    }

    vector<Segment*> arr;

    ll height(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    ll max(ll a, ll b) {
        if(a > b) return a;
        return b;
    }

    ll balanceFactor(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node<T>* rightRotate(Node<T>* node) {
        Node<T>* leftChild = node->left;
        Node<T>* rightChildOfLeftChild = leftChild->right;

        // Perform rotation
        leftChild->right = node;
        node->left = rightChildOfLeftChild;

        // Update heights
        node->height = max(height(node->left), height(node->right)) + 1;
        leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

        // Return new root
        return leftChild;
    }

    Node<T>* leftRotate(Node<T>* node) {
        Node<T>* rightChild = node->right;
        Node<T>* leftChildOfRightChild = rightChild->left;

        // Perform rotation
        rightChild->left = node;
        node->right = leftChildOfRightChild;

        // Update heights
        node->height = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

        // Return new root
        return rightChild;
    }

    Node<T>* insert(Node<T>* node, T key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key->p1.x < node->key->p1.x) {
            node->left = insert(node->left, key);
        } else if (key->p1.x >= node->key->p1.x) {
            node->right = insert(node->right, key);
        }

        // Update height of the current node
        node->height = max(height(node->left), height(node->right)) + 1;

        // Get the balance factor of the current node
        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && key->p1.x < node->left->key->p1.x) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && key->p1.x >= node->right->key->p1.x) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key->p1.x > node->left->key->p1.x) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key->p1.x < node->right->key->p1.x) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void travel(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        this->arr.push_back(node->key);
        travel(node->left);
        travel(node->right);
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;

    // Create a vector containing all segments
    vector<Segment*> segments;
    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Point p1 = {x1, y1};
        Point p2 = {x2, y2};
        Segment* s = new Segment{p1, p2};
        segments.push_back(s);
    }

    // Sort segments by x-coordinate of their left endpoint
    // using merge sort O(n*log(n))
    segments = mergeSort<Segment*>(segments);

    // AVL Tree to store active segments (those that intersect with the sweep line)
    AVLTree<Segment*> activeSegments;

    // Sweep line algorithm
    for (ll i = 0; i < n; i++) {
        Segment* s = segments[i];

        // Check if the new segment intersects with any of the active segments
        for (Segment* activeSegment : activeSegments.arr) {
            if (doIntersect(s, activeSegment)) {
                cout << "INTERSECTION\n";
                cout<< s->p1.x <<" "<< s->p1.y<<" "<< s->p2.x<<" "<< s->p2.y << endl;
                cout<< activeSegment->p1.x <<" "<< activeSegment->p1.y<<" "<< activeSegment->p2.x<<" "<< activeSegment->p2.y << endl;
                return 0;
            }
        }

        // Add the new segment to the tree
        activeSegments.root = activeSegments.insert(activeSegments.root, s);
        activeSegments.arr.clear();
        activeSegments.travel(activeSegments.root);

    }

    // No intersections found
    cout << "NO INTERSECTIONS" << endl;

    // Free memory
    for (Segment* s : segments) {
        delete s;
    }

    return 0;
}
