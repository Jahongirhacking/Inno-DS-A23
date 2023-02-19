// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

// our case E is struct elemenAndPosition
template<class E>
class Node {
public:
    // constructor
    Node(E value) {
        this->value = value;
        this->next = NULL;
    }
    // get the value of node
    E getValue() {
        return this->value;
    }
    // set node value
    void setValue(E value) {
        this->value = value;
    }
    // return the pointer to the next node
    Node* getNext() {
        return this->next;
    }
    // connect to the next Node
    void setNext(Node* next) {
        this->next = next;
    }
private:
    // value of the node
    E value;
    // pointer to the next node
    Node* next;
};

// in our case V is struct elementAndPosition
template<class V>
class LinkedStack {
public:
    // constructor
    LinkedStack(V elem) {
        data = new Node<V>(elem);
    }
    // push method to push the element to the front
    void push(V elem) {
        Node<V>* addingElement = new Node<V>(elem);
        addingElement->setNext(data);
        // move the data pointer to the top
        data = addingElement;
        // increase size
        size++;
    }
    // pop method to remove first node
    void pop() {
        Node<V>* head = data;
        // move the data pointer to the next
        // TODO: delete head
        data = data->getNext();
        head->setNext(NULL);
        delete head;
        // decrease size
        size--;
    }
    // return the top node value
    V top() {
        return data->getValue();
    }
    // show all info about stack
    void displayAll() {
        Node<V>* head = data;
        while(head != NULL) {
            cout << head->getValue().position << " " << head->getValue().element << endl;
            head = head->getNext();
        }
    }
    // check empty or not
    bool isEmpty() {
        return !(this->size);
    };
private:
    // size of the stack
    int size = 0;
    // main Linked Stack
    Node<V>* data;
};


int main() {
    string closeDelimiters[100], openDelimiters[100];
    int indexOfDelim = 0;

    // struct which holds delimiter and its array position
    struct elementAndPosition {
        string element;
        int position;
    };

    elementAndPosition empty = { element:"", position:-1 };

    // stack for managing delimiters
    LinkedStack<elementAndPosition> *rules = new LinkedStack<elementAndPosition>(empty);

    int n, k;
    string open, close;
    string line;

    // n - number of delimiter pairs
    // k - number of lines
    cin >> n >> k;
    rep(i, n) {
        cin >> open >> close;
        closeDelimiters[indexOfDelim] = close;
        openDelimiters[indexOfDelim++] = open;
    }

    // error handling
    getline(cin, line);

    int index;
    rep(i, k) {
        getline(cin, line);
        // temporary string
        string temp = "";
        // starting index
        index = 1;
        for(int j = 0; j < line.size(); j++) {
            // if whitespace then split
            if(line[j]==' ' || j==line.size()-1) {
                if(j == line.size()-1) {
                    // every iteration change temporary string
                    temp += line[j];
                }
                // check delimiters
                rep(it, indexOfDelim) {
                    if(temp == openDelimiters[it]) {
                        // if open delimiter
                        elementAndPosition elem = {element: temp, position: it};
                        // push to the stack
                        rules->push(elem);
                    } else if(temp == closeDelimiters[it]) {
                        // close delimiter
                        // if this case : ()}
                        if(rules->top().element == "") {
                            cout<<"Error in line "<<i+1<<", column "<<index
                                <<": unexpected closing token "<<temp<<".";
                            return 0;
                        }
                        // if this case: (}
                        if(openDelimiters[it] != rules->top().element) {
                            cout<<"Error in line "<<i+1<<", column "<<index<<": expected "
                                <<closeDelimiters[rules->top().position]<<" but got "<<temp<<".";
                            return 0;
                        }
                        // if there is no error then pop
                        rules->pop();
                    }
                }

                // update the index
                if(j != line.size()-1) {
                    index = j+2;
                }

                // clear the temporary string
                temp = "";
                continue;
            }
            // add to temporary string
            temp += line[j];
        }
    }

    // if this case: ({}
    if(rules->top().element != "") {
        cout<<"Error in line "<<k<<", column "<<line.size()+2<<": expected "
            <<closeDelimiters[rules->top().position]<<" but got end of input.";
        return 0;
    }

    // Everything is fine
    cout<<"The input is properly balanced.";
    return 0;
}
