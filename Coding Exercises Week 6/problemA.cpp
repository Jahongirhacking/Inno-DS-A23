// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define FOR(i,a,b) for(ll i = a; i < ll(b); i++)

vector<pair<ll, ll>> merge(vector<pair<ll, ll>> a, vector<pair<ll, ll>> b) {
    vector<pair<ll, ll>> res;
    ll index_a = 0, index_b = 0;
    while(index_a < a.size() || index_b < b.size()) {
        // WARN: focus
        if(index_b >= b.size() || (index_a < a.size() &&
                ( (a[index_a].first < b[index_b].first) ||
                                   (a[index_a].first == b[index_b].first && a[index_a].second < b[index_b].second)) )) {
            res.push_back(a[index_a++]);
        } else {
            res.push_back(b[index_b++]);
        }
    }
    return res;
}

vector<pair<ll, ll>> mergeSort(vector<pair<ll, ll>> a) {
    ll n = a.size();
    // just one elem
    if(n<=1) return a;
    vector<pair<ll, ll>> left, right;
    // left and right arrays to divide
    rep(i, n/2) left.push_back(a[i]);
    FOR(i, n/2, n) right.push_back(a[i]);
    // F-e: a = {7, 4, 8, 3, 6, 5, 1}
    // left = {7, 4, 8}
    // right = {3, 6, 5, 1}
    left = mergeSort(left);
    right = mergeSort(right);
    // merge({4, 7}, {1, 6})
    // result = {1, 4, 6, 7}
    return merge(left, right);
}

struct element {
    vector<pair<ll, ll>> heighers;
};

int main() {
    set<ll> uni;
    vector<element> arr(101);
    arr.clear();
    ll t;
    cin >> t;
    rep(i, t) {
        ll l, h;
        cin >> l >> h;
        uni.insert(l);
        arr[l].heighers.push_back({h, i+1}); // heigher val and position
    }

    vector<ll> lows;
    for(ll low : uni) {
        lows.push_back(low);
    }

    sort(lows.begin(), lows.end());

    string result = "";
    for(ll low : lows) {
        arr[low].heighers = mergeSort(arr[low].heighers);
    }

    // Output
    for(ll j=lows.size()-1; j>=0; j--) {
        for(auto iter : arr[lows[j]].heighers) {
            cout << iter.second << " ";
        }
    }
}
