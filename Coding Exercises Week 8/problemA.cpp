// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    Node(int value, int index) {
        this->value = value;
        this->index = index;
    }
    int getValue() {
        return this->value;
    }
    int getIndex() {
        return this->index;
    }
    // Pointers to the left and right children
    Node *left = NULL;
    Node *right = NULL;
private:
    int index;
    int value;
};

void put(Node *parent, Node *child) {
    if(child->getValue() < parent->getValue()) {
        // If child is lesser than the parent then move to the right
        // if parent's left is empty then put
        if(parent->left == NULL) {
            parent->left = child;
            return;
        } else {
            put(parent->left, child);
        }
    } else {
        // If child is greater than or equal to the parent then move to the right
        // if parent's right is empty then put
        if(parent->right == NULL) {
            parent->right = child;
            return;
        } else {
            put(parent->right, child);
        }
    }
}

void displayInfo(Node* node) {
    int leftIndex;
    int rightIndex;
    // Left node's index
    if(node->left==NULL) leftIndex=-1;
    else leftIndex=node->left->getIndex();
    // Right node's index
    if(node->right==NULL) rightIndex=-1;
    else rightIndex=node->right->getIndex();
    // Output
    cout << node->getValue() << " " << leftIndex << " " << rightIndex<< endl;

}

int main() {
    int n, x;
    cin >> n;
    vector<Node*> arr;
    Node *root = NULL;
    Node *elem = NULL;
    for(int i=1; i<=n; i++) {
        cin >> x;
        elem = new Node(x, i);
        if(i==1) {
            // create the root elem
            root = elem;
        } else {
            // put the new element to the BST
            put(root, elem);
        }
        arr.push_back(elem);
    }

    //Output
    cout << n << endl;
    for(Node* node : arr) {
        displayInfo(node);
    }
    cout << root->getIndex();
    return 0;
}
