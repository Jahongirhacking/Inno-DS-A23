// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, box;
    // enter the size
    cin>>n;
    // enter the array
    ll arr[n];
    for(ll i=0; i<n; i++) cin>>arr[i];
    //bubble sort algorithm
    bool swapped = true;
    while(swapped) {
        swapped = false;
        for(ll i=1; i<n; i++) {
            // take 2 elems, if something is weird then..
            if(arr[i-1]>arr[i]) {
                // make exchange with arr[i-1] and arr[i]
                box = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = box;
                swapped = true;
            }
        }
    }
    // output
    for(ll i : arr) cout<<i<<" ";
    return 0;
}
