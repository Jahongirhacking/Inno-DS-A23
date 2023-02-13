
// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)


// generic types
template <typename K>
// Map implementation by class
class SetArray {
    public:
        // capacity of the set
        ll capacity;
        
        // size of the set
        ll size = 0;
        
        // main array HashTable
        vector<list<string>> arr = {};
        
        // to initialize the capacity
        SetArray(ll cap) {
            capacity = cap;
            list<string> empty = {""};
            rep(i, capacity) {
                arr.push_back(empty);
            }
        }
        
        // hash function to manage data
        ll hashFunction(string k) {
            ll sum = 0;
            for(char i : k) {
                sum += i;
            }
            return (sum % capacity);
        }
        
        // put method
        void put(K k) {
            // according to hash-code's value
            arr[hashFunction(k)].push_front(k);
            size++;
        }
        
        // has method
        bool has(K k) {
            // according to hash-code's value
            for(string i : arr[hashFunction(k)]) {
                if(i == k) return true;
            }
            return false;
        }
};


// template <typename K, typename V>
// generic types
template <typename K, typename V>
// Map implementation by class
class MapArray {
    public:
        // capacity of the map
        ll capacity;
        
        // size of the map
        ll size = 0;
        
        // set of keys
        vector<string> keySet;
        
        struct element {
            K key;
            V value;
        };
        
        // main array HashTable
        vector<list<element>> arr = {};
        
        // to initialize the capacity
        MapArray(ll cap) {
            capacity = cap;
            // initialize empty element
            element elem;
            elem.key = "";
            list<element> empty = {elem};
            rep(i, capacity) {
                arr.push_back(empty);
            }
        }
        
        // hash function to manage data
        ll hashFunction(string k) {
            ll sum = 0;
            for(char i : k) {
                sum += i;
            }
            return (sum % capacity);
        }
        
        // put method
        void put(K k, V v) {
            // create element
            element el;
            el.key = k;
            el.value = v;
            // according to hash-function's hashcode
            ll hashcode = hashFunction(el.key);
            //if element already exists
            for(element &i : arr[hashcode]) {
                if(i.key == k) {
                    i.value.cost += el.value.cost;
                    i.value.codes.push_back(v.codes[0]);
                    return;
                }
            }
            size++;
            // push new element
            arr[hashcode].push_front(el);
            keySet.push_back(el.key);
        }
        
        // get method
        element get(K k) {
            // according to hash-function's hashcode
            for(element i : arr[hashFunction(k)]) {
                if(i.key == k) return i;
            }
            
            // initialize empty element
            element elem;
            elem.key = "";
            return elem;
        }
        
        // has method
        bool has(K k) {
            // according to hash-function's hashcode
            for(element i : arr[hashFunction(k)]) {
                if(i.key == k) return true;
            }
            return false;
        }
        
        bool isEmpty() {
            return !size;
        }
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
        vector<string> codes;
        double cost = 0;
    };
    
    // Map ADT to manage key & value data
    MapArray<string, Product>* manager = new MapArray<string, Product>(n);

    // Input
    rep(i, n) {
        // date - day, month, year
        // clockTime - hours, minutes, seconds
        // code - the receipt number
        // cost - $ how much money
        // name - name of the product
        string date, clockTime, code, name; 
        double cost;
        // input main variables
        cin >> date >> clockTime >> code >> character >> cost;
        getline(cin, name);
        // converting to ADS && compute
        Product item;
        item.codes.push_back(code);
        item.cost = cost;
        manager -> put(date, item);
    }
    
    // Output
    for(string uni : manager -> keySet) {
        Product prod = (manager -> get(uni)).value;
        vector<string> arr = prod.codes;
        double cost = prod.cost;
        // to make unique code of receipt
        SetArray<string>* uniqueCode = new SetArray<string>(arr.size());
        // count uniques
        ll count = 0;
        for(string i : arr) {
            if(!(uniqueCode -> has(i))) {
                uniqueCode -> put(i);
                count++;
            }
        }
        cout<<uni<<" $"<<cost<<" "<<count<<endl;
        
    }

    return 0;
}
