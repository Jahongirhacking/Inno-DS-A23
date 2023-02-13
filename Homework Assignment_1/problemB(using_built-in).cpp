// Jahongir Hayitov CS-01 - accepted solution
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)


int main() {
    // to store the receipt number and its cost
    struct Product {
        set<string> codes = {};
        double cost = 0;
    };
    // number of lines
    int n;
    // for $ sign
    char character;
    // Map ADT to manage key & value data
    map<string, Product> manager;
    // Set ADT to implement through the map via key
    set<string> uniqueDate;
    
    cin>>n;
    while(n--) {
        // date - day, month, year
        // clockTime - hours, minutes, seconds
        // code - the receipt number
        // cost - $ how much money
        // name - name of the product
        string date, clockTime, code, name; 
        double cost;
        // input
        cin >> date >> clockTime >> code >> character >> cost;
        getline(cin, name);
        // converting to ADS
        uniqueDate.insert(date);
        // compute
        manager[date].cost += cost;
        manager[date].codes.insert(code);
    }
    
    // Output
    for(string uni : uniqueDate) {
        cout<<uni<<" $"<<manager[uni].cost<<" "<<manager[uni].codes.size()<<endl;
    }
    
    return 0;
}
