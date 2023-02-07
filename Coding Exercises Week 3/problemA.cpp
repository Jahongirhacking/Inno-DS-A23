// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

// struct that holds key and value
// template <typename K, typename V>
struct element {
    string key;
    ll value;
};

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
        
        
        
        // main array HashTable
        vector<list<element>> arr = {};
        
        // to initialize the capacity
        MapArray(ll cap) {
            capacity = cap;
            // initialize empty element
            element elem;
            elem.key = "";
            elem.value = 0;
            list<element> empty = {elem};
            rep(i, capacity) {
                arr.push_back(empty);
            }
        }
        
        // hash functio to manage data
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
            // according to hashfunction's hashcode
            ll hashcode = hashFunction(el.key);
            size++;
            //if element already exists
            for(element &i : arr[hashcode]) {
                if(i.key == k) {
                    i.value++;
                    return;
                }
            }
            // push new element
            arr[hashcode].push_front(el);
            keySet.push_back(el.key);
        }
        
        // get method
        element get(K k) {
            // according to hashfunction's hashcode
            for(element i : arr[hashFunction(k)]) {
                if(i.key == k) return i;
            }
            
            // initialize empty element
            element elem;
            elem.key = "";
            elem.value = 0;
            return elem;
        }
        
        // has method
        bool has(K k) {
            // according to hashfunction's hashcode
            for(element i : arr[hashFunction(k)]) {
                if(i.key == k) return true;
            }
            return false;
        }
        
        bool isEmpty() {
            return !size;
        }
};

// use struct to make it more convenient
struct wordFreq {
    string word = "";
    int frequency = 0;
};

int main() {
    ll n, index = -1;
    // each word stored at a word variable withouat array
    string word;
    // number of words
    cin>>n;
    // wordMap is a manual Map ADT
    MapArray<string, ll>* wordMap = new MapArray<string, ll>(n);
    while(n--) {
        cin>>word;
        wordMap -> put(word, 1);
    }
    
    // create struct element to make sort
    vector<element> arr;
    for(string i: (wordMap -> keySet)) {
        arr.push_back(wordMap -> get(i));
    }
    
    // Sorting algorithm using INSERTION SORT
    for(int i=1; i<arr.size(); i++) {
        int j = i;
        // TODO: first frequency and if equal, next lexicographic
        while(j!=0 && (arr[j-1].value < arr[j].value ||
        arr[j-1].value == arr[j].value && arr[j-1].key > arr[j].key)) {
            swap(arr[j], arr[j-1]);
            j--;
        }
    }
    
    // output
    for(auto i:arr) {
        cout<<i.key<<" "<<i.value<<endl;
    }
    return 0;
}
