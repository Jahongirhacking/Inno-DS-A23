// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

int main() {
    map<string, string> closeDelimiters, openDelimiters;
    stack<string> rules;
    rules.push("");
    int n, k;
    string open, close;
    string line;
    
    cin >> n >> k;
    rep(i, n) {
        cin >> open >> close;
        closeDelimiters[close] = open;
        openDelimiters[open] = close;
    }
    
    // error handling
    getline(cin, line);
    
    int index;
    rep(i, k) {
        getline(cin, line);
        string temp = "";
        index = 1;
        for(int j = 0; j < line.size(); j++) {
            // if whitespace then split
            if(line[j]==' ' || j==line.size()-1) {
                if(j == line.size()-1) {
                    temp += line[j];
                }
                // check delimiters
                if(openDelimiters[temp].size() > 0) {
                    rules.push(temp);
                } else if(closeDelimiters[temp].size() > 0) {
                    if(rules.top() == "") {
                        cout<<"Error in line "<<i+1<<", column "<<index
                        <<": unexpected closing token "<<temp<<".";
                        return 0;
                    }
                    if(closeDelimiters[temp] != rules.top()) {
                        cout<<"Error in line "<<i+1<<", column "<<index<<": expected "
                        <<openDelimiters[rules.top()]<<" but got "<<temp<<".";
                        return 0;
                    }
                    
                    rules.pop();
                }
                
                if(j != line.size()-1) {
                    index = j+2;
                }
                
                temp = "";
                continue;
            }
            temp += line[j];
        }
    }
    
    if(rules.top() != "") {
        cout<<"Error in line "<<k<<", column "<<line.size()+2<<": expected "
        <<openDelimiters[rules.top()]<<" but got end of input.";
        return 0;
    }
    
    // Everything is fine
    cout<<"The input is properly balanced.";
    return 0;
}
