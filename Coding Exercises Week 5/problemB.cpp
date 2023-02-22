// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

// Dictionary check
map<string, bool> dictionary;
// Check whether we already check it
vector<bool> DP;
stack<string> result;

bool checkWordFromDict(string& str, int index) {
    // If the whole string exists in Dictionary
    if(str.length() <= index) return true;
    // If we took it already
    if(DP[index]) return false;
    // We take it
    DP[index] = true;
    for (int i = 1; index+i <= str.length(); i++) {
        string prefixOfString = str.substr(index, i);
        // first check prefix, if it exists in dictionary
        if(dictionary.count(prefixOfString)>0 && checkWordFromDict(str, index+i)) {
            // If we find the path we need to push all prefix
            result.push(prefixOfString);
            return true;
        }
    }
    // the prefix is not in Dictionary
    return false;
}

int main() {
    // n - number of dictionary words
    // k - characters
    int n;
    int k;
    string word;
    cin >> n >> k;
    // input dictionary words
    rep(i, n) {
        cin >> word;
        dictionary[word] = true;
    }
    cin >> word;
    
    DP.resize(k, false);
    // check and store until you find path
    checkWordFromDict(word, 0);
    // Output the words
    while(!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
    return 0;
}
