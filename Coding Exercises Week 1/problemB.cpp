// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct st {
    string player;
    ll score;
};

int main() {
    ll n, k;
    cin>>n>>k;
    // to minimize k
    if(k>n) k=n;
    // array of structed data
    st arr[n], box;
    for(ll i=0; i<n; i++) cin>>arr[i].player>>arr[i].score;
    // the SELECTION SORT algorithm BUT
    // instead of swapping I put -1 for score and ignore it
    // to save the position
    for(ll i=0; i<k; i++) {
        // Find maximums
        // Initial values
        ll max_score = arr[i].score;
        ll max_index = i;
        string max_player = arr[i].player;
        for(ll j=0; j<n; j++) {
            if(arr[j].score != -1 && max_score < arr[j].score) {
                max_score = arr[j].score;
                max_player = arr[j].player;
                max_index = j;
            }
        }
        // Outputs
        cout<<max_player<<" "<<max_score<<endl;
        arr[max_index].score = -1;
    }
    return 0;
}
