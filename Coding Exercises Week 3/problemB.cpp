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
        
        // hash functio to manage data
        ll hashFunction(string k) {
            ll sum = 0;
            for(char i : k) {
                sum += i;
            }
            return (sum % capacity);
        }
        
        // put method
        put(K k) {
            // according to hashcode's value
            arr[hashFunction(k)].push_front(k);
            size++;
        }
        
        // has method
        has(K k) {
            // according to hashcode's value
            for(string i : arr[hashFunction(k)]) {
                if(i == k) return true;
            }
            return false;
        }
};
 

int main() {
    // number of words in a sentence
    ll n, index = -1;
    // each word be saved i a word variable
    string word;
    // to count unique words
    ll counter = 0;
    // resulting array contains unique words
    vector<string> result;
    
    // first text input
    cin>>n;
    
    // creating Object
    SetArray<string>* check = new SetArray<string>(n);
    
    while(n--) {
        cin>>word;
        // change the word value to true, so it exists
        check -> put(word);
    }
    
    // second text input
    cin>>n;
    while(n--) {
        cin>>word;
        if(!(check -> has(word))) {
            // push to result vector
            result.push_back(word);
            counter++;
            // not to get duplicate, put it to map
            check -> put(word);
        }
    }
    
    // Output
    cout<<counter<<endl;
    for(string i:result) cout<<i<<endl;
    return 0;
}
