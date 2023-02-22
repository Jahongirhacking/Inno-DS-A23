// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

int main() {
    // number of elements and knapsack weight
    int n, weight;
    cin >> n >> weight;
    // array for weight and costs for each item
    vector<pair<int, int>> items(n, {0, 0}); // weight and cost
    rep(i, n) cin >> items[i].first;
    rep(i, n) cin >> items[i].second;

    vector<int> empty(weight+1, 0);
    vector<vector<int>> DP(n+1, empty);
    // Maximum cost properties
    int maxCost = -1;
    int maxPosY, maxPosX;
    // Find the maximum by DP
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=weight; j++) {
            // out of bound exception
            if(j-items[i-1].first < 0) {
                DP[i][j] = max(DP[i-1][j], 0);
            }
            else {
                DP[i][j] = max(DP[i-1][j], DP[i-1][j-items[i-1].first]+items[i-1].second);
            }
            // Assign maximum
            if(DP[i][j] > maxCost) {
                maxCost = DP[i][j];
                maxPosX = j;
                maxPosY = i;
            }
        }
    }

    // Find the path via backtracking
    vector<int> result;
    while(DP[maxPosY][maxPosX] != 0) {
        if(DP[maxPosY][maxPosX] != DP[maxPosY-1][maxPosX]) {
            maxPosX -= items[maxPosY-1].first;
            result.push_back(maxPosY);
        }
        maxPosY--;
    }

    // Output
    cout << result.size() << endl;
    for(int i = result.size()-1; i>=0; i--) {
        cout << result[i] << " ";
    }
    return 0;
}
