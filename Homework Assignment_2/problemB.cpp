// Jahongir Hayitov CS-01.
#include<bits/stdc++.h>
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define FOR(i,a,b) for(ll i = a; i < ll(b); i++)
typedef long long int ll;
using namespace std;

// Array Generator for X
vector<ll> arrayGenerator(ll seed, ll a, ll c, ll m, ll n) {
    vector<ll> res = {seed};
    for(ll i=1; i<=n; i++) {
        res.push_back((a%m*(res[i-1]%m)%m+c%m)%m);
    }
    return res;
}

template <typename T>
void printArray(vector<T> arr) {
    for(T t : arr) cout<<t<<", ";
}

// Merge two array into one sorted array
template<typename T>
vector<T> merge(vector<T> a, vector<T> b) {
    vector<T> res;
    ll index_a = 0, index_b = 0;
    while(index_a < a.size() || index_b < b.size()) {
        if(index_b >= b.size() || (index_a < a.size() && a[index_a].value <= b[index_b].value)) {
            res.push_back(a[index_a++]);
        } else {
            res.push_back(b[index_b++]);
        }
    }
    return res;
}

// Time Complexity: O(n*log(n)) and stable
template<typename T>
vector<T> mergeSort(vector<T> bucket) {
    ll n = bucket.size();
    // just one elem
    if(n<=1) return bucket;
    vector<T> left, right;
    // left and right arrays to divide
    rep(i, n/2) left.push_back(bucket[i]);
    FOR(i, n/2, n) right.push_back(bucket[i]);
    // a = {7, 4, 8, 3, 6, 5, 1}
    // left = {7, 4, 8}
    // right = {3, 6, 5, 1}
    left = mergeSort<T>(left);
    right = mergeSort<T>(right);
    // merge({4, 7}, {1, 6})
    // result = {1, 4, 6, 7}
    return merge(left, right);
}

// Bucket Sort implementation
template <typename T>
void bucketSort(vector<T>& arr) {
    int n = arr.size();
    // create n buckets
    vector<vector<T>> buckets(n);

    // push each bucket
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i].value;
        if(bucketIndex>=n) bucketIndex = n-1;
        buckets[bucketIndex].push_back(arr[i]);
    }

    // sort inside the bucket by Merge Sort
    for (int i = 0; i < n; i++) {
        if(buckets[i].size() <= 1) continue;
        buckets[i] = mergeSort<T>(buckets[i]);
    }

    arr.clear();
    for (int i = 0; i < n; i++) {
        if(buckets[i].size() == 0) continue;
        for (int j = 0; j < buckets[i].size(); j++) {
            arr.push_back(buckets[i][j]);
        }
    }
}

struct bucketElem {
    double value;
    ll index;
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll a, c, m, seed, n;
    cin>>a>>c>>m>>seed>>n;
    // Generate array X
    vector<ll> arr = arrayGenerator(seed, a, c, m, n);
    // Generate Random Numbers Y
    vector<bucketElem> randNumbers;
    for(ll i=1; i<=n; i++) {
        double d = abs(2.0*arr[i]/(m*1.0)-1.0);
        bucketElem elem;
        elem.value = d;
        elem.index = i;
        randNumbers.push_back(elem);
    }
    // Sort Random Numbers
    bucketSort<bucketElem>(randNumbers);
    // Print Median
    cout<<randNumbers[n/2-1].index;
    return 0;
}
