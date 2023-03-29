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

template <typename T>
void quickSort(vector<T>& arr, int left, int right) {
    
    int i = left, j = right;
    double pivot = arr[(left + right) / 2].value;

    // partition
    while (i <= j) {
        while (arr[i].value < pivot)
            i++;
        while (arr[j].value > pivot)
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };

    // recursion with partition
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
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
    quickSort<bucketElem>(randNumbers, 0, n-1);
    // Print Median
    cout<<randNumbers[n/2-1].index;
    return 0;
}
