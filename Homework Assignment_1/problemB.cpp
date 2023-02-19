// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

template<class V>
class Node {
public:
    // constructor
    Node(V value) {
        this->value = value;
        this->next = NULL;
    }
    // get the value of node
    V getValue() {
        return this->value;
    }
    // set node value
    void setValue(V value) {
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
    V value;
    // pointer to the next node
    Node* next;
};

template<class K, class V>
class HashMap {
public:
    HashMap(int capacity) {
        this->capacity = capacity;
        hashTable.resize(capacity);
        V empty = { date: "" };
        Node<V>* nullNode = new Node<V>(empty);
        rep(i, capacity) {
            hashTable[i] = nullNode;
        }
    }
    // put method
    void put(K key, V value) {
        ll hashcode = hashFunction(key);
        // check existence
        Node<V>* head = hashTable[hashcode];
        while(head != NULL) {
            if(head->getValue().date == value.date) {
                V valueOfProduct = head->getValue();
                valueOfProduct.cost += value.cost;
                // check if code is unique
                bool isUnique = true;
                for(string code : valueOfProduct.codes) {
                    if(code == value.codes[0]) {
                        isUnique = false;
                        break;
                    }
                }
                if(isUnique) {
                    valueOfProduct.codes.push_back(value.codes[0]);
                }
                // update
                head->setValue(valueOfProduct);
                return;
            }
            head = head->getNext();
        }
        // create a new and put the Node to the front
        Node<V>* node = new Node<V>(value);
        node->setNext(hashTable[hashcode]);
        hashTable[hashcode] = node;
        this->keySet.push_back(value.date);
        this->size++;
        // WARN: need some improvement with size
        // if the capacity exceeded then call rehashing
        if(this->size > this->capacity) {
            this->rehashing();
        }
    }

    void remove(K key) {
        ll hashcode = hashFunction(key);
        // head node
        Node<V>* head = hashTable[hashcode];
        // previous node of head
        V empty = { date: "" };
        Node<V>* prev = new Node<V>(empty);
        // checking
        while(head != NULL) {
            if(head->getValue().date == key) {
                if(prev->getValue().date != "") {
                    // if the removable node is in the middle
                    // TODO: merge previous and next node
                    prev->setNext(head->getNext());
                    delete head;
                    return;
                } else {
                    // if front node is removable
                    // TODO: next node is head
                    hashTable[hashcode] = head->getNext();
                    delete head;
                    return;
                }
            }
            // update pointers
            prev = head;
            head = head->getNext();
        }
    }

    // rehashing method
    void rehashing() {
        vector<Node<V>*>copyHashTable = this->hashTable;
        // Double the capacity
        this->capacity *= 2;
        this->hashTable.clear();
        V val = { date: "" };
        Node<V>* empty = new Node<V>(val);
        this->hashTable.resize(this->capacity, empty);
        // move every element inside copy to original
        // TODO: new capacity means new hashcode
        rep(i, copyHashTable.size()) {
            Node<V>* head = copyHashTable[i];
            // connect every element it's appropriate next
            while(head != NULL && head->getValue().date != "") {
                Node<V>* next = head->getNext();
                ll hashcode = hashFunction(head->getValue().date);
                head->setNext(this->hashTable[hashcode]);
                this->hashTable[hashcode] = head;
                head = next;
            }
        }
    }

    // hash function to manage data
    ll hashFunction(K k) {
        ll sum = 0;
        for(char i : k) {
            sum += i;
        }
        return (sum % this->capacity);
    }

    vector<K> getKeySet() {
        return this->keySet;
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    // for testing
    void displayAll() {
        rep(i, this->capacity) {
            Node<V>* head = hashTable[i];
            while(head != NULL) {
                cout << head->getValue().date << " cost: " << head->getValue().cost << " ";
                head = head->getNext();
            }
            cout<<endl;
        }
    };

    // Print the answer
    void showResult() {
        rep(i, this->capacity) {
            Node<V>* head = hashTable[i];
            while(head != NULL && head->getValue().date != "") {
                cout << head->getValue().date << " $" << head->getValue().cost
                     << " " << head->getValue().codes.size() << endl;
                head = head->getNext();
            }
        }
    };

private:
    // size of the hashmap
    int size = 0;
    // capacity of the hashmap
    int capacity;
    // hashtable for hashing
    vector<Node<V>*> hashTable;
    // set of keys
    vector<K> keySet;
};


int main() {
    // number of lines
    int n;
    // for $ sign
    char character;
    // number of lines
    cin>>n;

    // to store the receipt number and its cost
    struct Product {
        string date;
        vector<string> codes;
        double cost = 0;
        string name = "";
        string clockTime = "";
    };

    // Map ADT to manage key & value data
    HashMap<string, Product>* manager = new HashMap<string, Product>(70);

    // Input
    rep(i, n) {
        /**
         * date - day, month, year
         * clockTime - hours, minutes, seconds
         * code - the receipt number
         * cost - $ how much money
         * name - name of the product
        **/
        string date, clockTime, code, name;
        double cost;
        // input main variables
        cin >> date >> clockTime >> code >> character >> cost;
        getline(cin, name);
        // converting to ADS && compute
        Product item;
        item.date = date;
        item.codes.push_back(code);
        item.cost = cost;
        item.name = name;
        item.clockTime = clockTime;
        // put the data to the HashMap
        manager -> put(date, item);
    }

    manager->showResult();

    return 0;
}
