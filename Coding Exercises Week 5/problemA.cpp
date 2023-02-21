// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

vector<pair<int, int>> items;
map<pair<int, int>, pair<vector<int>, int>> dp; // index and weight

// Knapsack algorithm that returns
// vector - positions, and int - cost
pair<vector<int>, int> knapsack(int weight, int index) {
    if(index == -1 || weight == 0) return {{}, 0}; // position array and cost
    // check from exist items
    if(dp.count({index, weight}) > 0) {
        return dp[{index, weight}];
    }
    // if item's weight doesn't fit
    // then go to next item
    if(weight < items[index].first) {
        dp[{index, weight}] = knapsack(weight, index-1);
        return dp[{index, weight}];
    }
    // if item's weight fits
    // We have 2 choices: yes or no
    pair<vector<int>, int> temp1 = knapsack(weight, index-1); // no choice
    pair<vector<int>, int> temp2 = knapsack(weight-items[index].first, index-1); // yes choice

    // choose the greatest
    if(temp1.second > temp2.second + items[index].second) {
        dp[{index, weight}] = temp1;
        return temp1;
    } else {
        temp2.first.push_back(index);
        temp2.second += items[index].second;
        dp[{index, weight}] = temp2;
        return temp2;
    }
}

int main() {
    // number of elements and knapsack weight
    int n, w;
    cin >> n >> w;
    // array for weight and costs
    items.resize(n, {0, 0});
    rep(i, n) cin >> items[i].first;
    rep(i, n) cin >> items[i].second;

    int index = n-1;
    pair<vector<int>, int> pos;
    // find the positions
    pos = knapsack(w, index);

    // output
    cout << pos.first.size() << endl;
    for(int i : pos.first) cout<<i+1<<" ";
    return 0;
}

// 0.5 s
// Time Limit Test 54
