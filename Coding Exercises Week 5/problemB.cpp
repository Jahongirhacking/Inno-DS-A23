// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

map<string, bool> DP;


void findWord(string s, vector<string> arr) {
    string temp = "";
    for(int i=0; i<s.size(); i++) {
        temp += s[i];
        if(DP[temp]) {
            arr.push_back(temp);
            if(i == s.size()-1) {
                for(string str:arr) if(str!="") cout<<str<<" ";
                exit(0);
            }
            findWord(s.substr(i+1), arr);
            arr.pop_back();
        }
    }
}

int main() {
    int n, k;
    string str;
    cin >> n >> k;
    // store dictionary words
    for(int i=0; i<n; i++) {
        cin >> str;
        DP[str] = true;
    }
    cin >> str;
    findWord(str, {});
    return 0;
}
