// Jahongir Hayitov CS-01
// Manually created Map ADT
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// generic types
template <typename K, typename V>
// Map implementation by class
class MapArray {
    public:
        // size of the map
        ll size = 0;
        
        // the main map array
        vector<pair<K, V>> arr;
        
        // the unique key set pair<key, index of the key>
        vector<pair<K, ll>> keySet;
        
        // check if there already exists a key O(N)
        bool has(K k, ll& index) {
            for(ll i = 0; i<arr.size(); i++) {
                if(arr[i].first == k) {
                    index = i;
                    return true;
                }
            }
            return false;
        }
        
        // put method
        void put(pair<K, V> e, ll index) {
            // first check if there already exists a key
            if(index != -1){
                // update the value
                arr[index].second = e.second;
            } else {
                // create new element
                arr.push_back(e);
                keySet.push_back({ e.first, arr.size()-1 });
                size++;
            } 
        }
        
        // get method
        V get(K k, ll index) {
            return arr[index].second;
        }
        
        // remove the element by its key
        void removeElem(K k) {
            // extra vector to hold data
            vector<pair<K, V>> temp;
            for(auto i : arr) {
                if(i.first != k) temp.push_back(i);
            }
            // exchange values
            arr = temp;
            temp.clear();
        }
        
        // for printing all values
        void all() {
            for(pair<K, V> i : arr) cout<<i.first<<" "<<i.second<<endl;
        }
        
        // is empty or not
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
    MapArray<string, ll>* wordMap = new MapArray<string, ll>();
    while(n--) {
        cin>>word;
        if(wordMap -> has(word, index)) {
            // if we already have key, then increment value 
            wordMap -> put({ word, (wordMap -> get(word, index)) + 1 }, index);
        } else {
            // if we don't create new pair
            wordMap -> put({ word, 1 }, -1);
        }
    }
    
    // create struct element to make sort
    vector<wordFreq> arr;
    for(pair<string, ll> i : wordMap -> keySet) {
        wordFreq wordObj;
        // word value
        wordObj.word = (wordMap -> arr)[i.second].first;
        // word frequency count
        wordObj.frequency = (wordMap -> arr)[i.second].second;
        // push to the vector
        arr.push_back(wordObj);
    }
    
    // Sorting algorithm using INSERTION SORT
    for(int i=1; i<arr.size(); i++) {
        int j = i;
        // TODO: first frequency and if equal, next lexicographic
        while(j!=0 && (arr[j-1].frequency < arr[j].frequency ||
        arr[j-1].frequency == arr[j].frequency && arr[j-1].word > arr[j].word)) {
            swap(arr[j], arr[j-1]);
            j--;
        }
    }
    
    // output
    for(auto i:arr) {
        cout<<i.word<<" "<<i.frequency<<endl;
    }
    return 0;
}
